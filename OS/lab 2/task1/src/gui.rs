use eframe::egui;
use std::thread::{self, JoinHandle};
use std::sync::atomic::{AtomicUsize, Ordering};
use std::sync::{Arc, Mutex, Condvar};
use std::time::Duration;

use crate::limeted_vec::LimitedVec;
use crate::model::{calculate_pyramid_surface, calculate_triangle_area, find_third_vertex};

const TASK_TEXT: &str = "Задание: С помощью мьютексов организовать работу параллельных вычислительных потоков.
Первый поток считает площадь треугольника S, координаты вершин которого (4; 3), (8; 12), (i; j), где i, j = [9; 14], шаг 1, затем считает площадь поверхности пирамиды G с высотой равной (i+j). 
Второй поток считает координаты третьей вершины треугольника с координатами (–2; 6), (2; –4), (x; y) по координатам двух известных вершин и его площади S (определенной первым потоком), далее считает объем пирамиды с высотой h = [4; 10], шаг 1.";

const BUFFER_SIZE: usize = 36;

/**Структура приложения */
pub struct App {
    first_speed_ref: Arc<Mutex<usize>>,
    second_speed_ref: Arc<Mutex<usize>>,

    first_table_mutex_ref: Arc<Mutex<Vec<String>>>,
    second_table_mutex_ref: Arc<Mutex<Vec<String>>>,

    first_handle: Option<JoinHandle<()>>,
    second_handle: Option<JoinHandle<()>>,

    exit: Arc<AtomicUsize>,
}

/**Деструктор приложения */
impl Drop for App {
    fn drop(&mut self) {
        self.execute_threads();
    }
}

/**Реализация интерфейса формы */
impl eframe::App for App {
    /**Функция обновления окна */
    fn update(&mut self, ctx: &egui::Context, _frame: &mut eframe::Frame) { 
        ctx.request_repaint();                                      // перерисовать интерфейс

        egui::SidePanel::right("right")                // правая боковая панель
        .resizable(false)
        .show(ctx, |ui| {
            ui.label("Скорость первого потока:");
            ui.add(egui::Slider::new(&mut *self.first_speed_ref.lock().unwrap(), 0..=100));
            ui.label("Скорость второго потока:");
            ui.add(egui::Slider::new(&mut *self.second_speed_ref.lock().unwrap(), 0..=100));

            if ui.button("Сброс").clicked() {
                self.reset_threads();
            }
        });

        egui::CentralPanel::default()                   // центральная панель
        .show(ctx, |_| {

            egui::TopBottomPanel::top("central")  // побочная верхняя панель
            .resizable(false)
            .show(ctx, |ui| {
                ui.label(TASK_TEXT);
            });

            egui::SidePanel::left("table1")            // побочная левая панель
                .min_width(150.0)
                .resizable(false)
                .show(ctx, |ui| {
                    self.first_table(ui, "table1", "Первый поток");
                });

            egui::SidePanel::right("table2")            // побочная правая панель
                .min_width(680.0)
                .resizable(false)
                .show(ctx, |ui| {
                    self.second_table(ui, "table2", "Второй поток");
                });
        });
    }
}

/**Функция управления скоростью потоков*/
fn delay(speed: Arc<Mutex<usize>>) {
    let time;
    if *speed.lock().unwrap() == 0 {
        loop {
            thread::sleep(Duration::from_millis(500));
            if *speed.lock().unwrap() != 0 {
                break;
            }
        }
        time = 2000 - (*speed.lock().unwrap() as u64 * 20);
    } else {
        time = 2000 - (*speed.lock().unwrap() as u64 * 20);
    }
    thread::sleep(Duration::from_millis(time));
}

/**Функция потока 1*/
fn first_thread(buffer_mutex: Arc<(Mutex<LimitedVec<f64>>, Condvar)>, output_mutex: Arc<Mutex<Vec<String>>>, speed: Arc<Mutex<usize>>) {
    let mut counter = 1;
    for i in 9..=14 {
        for j in 9..=14 {

            let area = calculate_triangle_area(4.0, 3.0, 8.0, 12.0, i as f64, j as f64);
            let pyramid_surface = calculate_pyramid_surface(area, (i + j) as f64);
            let entry = format!("{counter}: S = {area}, G = {pyramid_surface}");

            delay(speed.clone());

            {
                let (lock, cvar) = &*buffer_mutex;  // разыменоваем arc и получаем ссылку на кортеж (Mutex<LimitedVec<f64>>, Condvar)
                let mut buffer = lock.lock().unwrap();  // ожидание освобождения мьютекса и его захват

                while buffer.len() == BUFFER_SIZE {                                    // если в буфере нет места, то освобождаем мьютекс и ждем
                    buffer = cvar.wait(buffer).unwrap();
                }

                buffer.push(area).unwrap();
                cvar.notify_one();
                // Освобождение мьютекса
            }

            {
                output_mutex.lock().unwrap().push(entry);                              // ожидание освобождения мьютекса и его захват
                // Освобождение мьютекса
            }
            counter += 1;
        }
    }
}

/**Функция для потока 2*/
fn second_thread(buffer_mutex: Arc<(Mutex<LimitedVec<f64>>, Condvar)>, output_mutex: Arc<Mutex<Vec<String>>>, speed: Arc<Mutex<usize>>) {
    let mut counter = 1;
    while counter <= 36 {
        let area: f64;

        delay(speed.clone());

        {
            let (lock, cvar) = &*buffer_mutex;  // разыменоваем arc и получаем ссылку на кортеж (Mutex<LimitedVec<f64>>, Condvar)
            let mut buffer = lock.lock().unwrap();  // ожидание освобождения мьютекса и его захват

            while buffer.is_empty() {                                              // если в буфере нет места, то освобождаем мьютекс и ждем
                buffer = cvar.wait(buffer).unwrap();
            }

            area = buffer.remove(0).unwrap();
            cvar.notify_one();
            // Освобождение мьютекса
        }

        // Нахождение координаты третьей вершины (x3, y3) для треугольника с вершинами (-2, 6), (2, -4) и площадью area.
        let ((x3_1, y3_1), (x3_2, y3_2)) = find_third_vertex(-2.0, 6.0, 2.0, -4.0, area);

        // Рассчитываем объем пирамиды
        let mut volume = Vec::new();
        for h in 4..=10 {
            volume.push(area * h as f64);
        }

        let entry = format!("{counter}: S = {area:.2}, Volume = {volume:?}, Third Vertexes = ({x3_1:.2}; {y3_1:.2}), ({x3_2:.2}; {y3_2:.2})");
        {
            output_mutex.lock().unwrap().push(entry);
            // Освобождение мьютекса
        }
        counter += 1;
    }
}

/**Методы класса приложения */
impl App {
    /**Конструктор приложения */
    pub fn new() -> Self {
        // Создаем мьютексы, оборачиваем в arc для разделения доступа к ним
        let first_table_mutex_ref = Arc::new(Mutex::new(Vec::new()));
        let second_table_mutex_ref = Arc::new(Mutex::new(Vec::new()));
        let first_speed_ref = Arc::new(Mutex::new(0));
        let second_speed_ref = Arc::new(Mutex::new(0));

        let mut slf = Self { // создаем поля
            first_speed_ref,
            second_speed_ref,

            exit: Arc::new(AtomicUsize::new(0)),

            first_handle: None,
            second_handle: None,

            first_table_mutex_ref,
            second_table_mutex_ref,
        };

        slf.birth_threads();
        slf                       // возвращаем ссылку на созданный экземпляр приложения
    }

    fn first_table(&self, ui: &mut egui::Ui, _table_name: &str, title: &str) {
        let data = self.first_table_mutex_ref.lock().unwrap();
        ui.vertical(|ui| {
            ui.label(title);
            egui::Frame::none()
                .stroke(egui::Stroke::new(2.0, egui::Color32::GRAY))
                .inner_margin(egui::style::Margin::same(5.0))
                .show(ui, |ui| {
                    egui::ScrollArea::new([false, true]).show(ui, |ui| {
                        for entry in data.iter() {
                            ui.label(entry);
                        }
                    });
                });
        });
    }

    fn second_table(&self, ui: &mut egui::Ui, _table_name: &str, title: &str) {
        let data = self.second_table_mutex_ref.lock().unwrap();
        ui.vertical(|ui| {
            ui.label(title);
            egui::Frame::none()
                .stroke(egui::Stroke::new(2.0, egui::Color32::GRAY))
                .inner_margin(egui::style::Margin::same(5.0))
                .show(ui, |ui| {
                    egui::ScrollArea::new([false, true]).show(ui, |ui| {
                        for entry in data.iter() {
                            ui.label(entry);
                        }
                    });
                });
        });
    }

    /**Инициализация и запуск потоков */
    fn birth_threads(&mut self) {
        let buffer_mutex_ref = Arc::new((Mutex::new(LimitedVec::new(BUFFER_SIZE)), Condvar::new()));
        let first_output_mutex = self.first_table_mutex_ref.clone();
        let second_output_mutex = self.second_table_mutex_ref.clone();
        let first_speed_mutex = self.first_speed_ref.clone();
        let second_speed_mutex = self.second_speed_ref.clone();
        // скорость = 0
        *self.first_speed_ref.lock().unwrap() = 0;
        *self.second_speed_ref.lock().unwrap() = 0;

        // Клонируем указатели на мьютексы для передачи и создаем потоки
        self.first_handle = Some(thread::spawn({
            let buffer_mutex = buffer_mutex_ref.clone();
            move || {
                first_thread(buffer_mutex, first_output_mutex, first_speed_mutex);
            }
        }));

        self.second_handle = Some(thread::spawn({
            let buffer_mutex = buffer_mutex_ref;
            move || {
                second_thread(buffer_mutex, second_output_mutex, second_speed_mutex);
            }
        }));

    }

    /**Остановка потоков */
    fn execute_threads(&mut self) {
        *self.first_speed_ref.lock().unwrap() = 100;
        *self.second_speed_ref.lock().unwrap() = 100;
        self.exit.store(1, Ordering::SeqCst);            // сигнал потокам завершить работу

        // Ожидаем завершения потоков
        if let Some(handle) = self.first_handle.take() {
            handle.join().unwrap();
        }
        if let Some(handle) = self.second_handle.take() {
            handle.join().unwrap();
        }
    }

    /**Перезапуск потоков и очистка таблиц*/
    fn reset_threads(&mut self) {
        self.execute_threads();

        self.first_table_mutex_ref.lock().unwrap().clear();         // Очистка таблиц
        self.second_table_mutex_ref.lock().unwrap().clear();

        self.exit.store(0, Ordering::SeqCst);            // Сброс флага завершения

        self.birth_threads();
    }
}
