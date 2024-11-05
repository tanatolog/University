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
const FIRST_SPEED: u64 = 150;
const SECOND_SPEED: u64 = 200;

/**Структура приложения */
pub struct App {
    first_speed: usize,
    second_speed: usize,

    /*buffer_mutex_ref1: Arc<(Mutex<LimitedVec<f64>>, Condvar)>,
    buffer_mutex_ref2: Arc<(Mutex<LimitedVec<f64>>, Condvar)>,

    output_mutex_ref1: Arc<Mutex<()>>,
    output_mutex_ref2: Arc<Mutex<()>>,*/

    first_handle: Option<JoinHandle<()>>,
    second_handle: Option<JoinHandle<()>>,

    exit: Arc<AtomicUsize>,
}

/**Деструктор приложения */
impl Drop for App {
    fn drop(&mut self) {
        self.exit.store(1, Ordering::SeqCst);            // сигнал для потокам завершить работу

        // Ожидаем завершения потоков
        if let Some(handle) = self.first_handle.take() {
            handle.join().unwrap();
        }
        if let Some(handle) = self.second_handle.take() {
            handle.join().unwrap();
        }
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
            ui.label("Частота первого потока:");
            ui.add(egui::Slider::new(&mut self.first_speed, 0..=100));
            ui.label("Частота второго потока:");
            ui.add(egui::Slider::new(&mut self.second_speed, 0..=100));
        });

        egui::CentralPanel::default().show(ctx, |_| {  // центральная панель

            egui::TopBottomPanel::top("central")  // побочная верхняя панель
            .resizable(false)
            .show(ctx, |ui| {
                ui.label(TASK_TEXT);
            });

            egui::SidePanel::left("table1")            // побочная левая панель
                .resizable(false)
                .show(ctx, |ui| {
                    self.first_table(ui, "table1", "Первый поток");
                });

            egui::SidePanel::right("table2")            // побочная правая панель
                .resizable(false)
                .show(ctx, |ui| {
                    self.second_table(ui, "table2", "Второй поток");
                });
        });
    }
}

/**Функция потока 1*/
fn first_thread(buffer_mutex: Arc<(Mutex<LimitedVec<f64>>, Condvar)>, output_mutex: Arc<Mutex<()>>) {
    let mut counter = 1;
    for i in 9..=14 {
        for j in 9..=14 {

            let area = calculate_triangle_area(4.0, 3.0, 8.0, 12.0, i as f64, j as f64);
            let pyramid_surface = calculate_pyramid_surface(area, (i + j) as f64);

            thread::sleep(Duration::from_millis(FIRST_SPEED));

            {
                let (lock, cvar) = &*buffer_mutex;  // разыменоваем arc и получаем ссылку на кортеж (Mutex<LimitedVec<f64>>, Condvar)
                let mut buffer = lock.lock().unwrap();  // ожидание освобождения мьютекса и его захват

                while buffer.len() == BUFFER_SIZE {                                    // если в буфере нет места, то освобождаем мьютекс и ждем
                    buffer = cvar.wait(buffer).unwrap();
                }

                buffer.push(area).unwrap();
                println!("Thread 1:{counter} bufflen = {}", buffer.len());
                cvar.notify_one();
                // Освобождение мьютекса
            }

            {
                let _non = output_mutex.lock().unwrap();            // ожидание освобождения мьютекса и его захват
                println!("Thread 1:{counter} i = {i}, j = {j}, S = {area}, G = {pyramid_surface}");
                // Освобождение мьютекса
            }
            counter += 1;
        }
    }
}

/**Функция для потока 2*/
fn second_thread(buffer_mutex: Arc<(Mutex<LimitedVec<f64>>, Condvar)>, output_mutex: Arc<Mutex<()>>) {
    let mut counter = 1;

    while counter <= 36 {
        let area: f64;

        thread::sleep(Duration::from_millis(SECOND_SPEED));

        {
            let (lock, cvar) = &*buffer_mutex;  // разыменоваем arc и получаем ссылку на кортеж (Mutex<LimitedVec<f64>>, Condvar)
            let mut buffer = lock.lock().unwrap();  // ожидание освобождения мьютекса и его захват

            while buffer.is_empty() {                                              // если в буфере нет места, то освобождаем мьютекс и ждем
                buffer = cvar.wait(buffer).unwrap();
            }

            area = buffer.remove(0).unwrap();
            println!("Thread 2:{counter} bufflen = {}", buffer.len());
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

        {
            let _non = output_mutex.lock().unwrap();
            println!("Thread 2:{counter} S = {area}, Volume = {volume:?}, Third Vertexes = ({x3_1:.2}; {y3_1:.2}), ({x3_2:.2}; {y3_2:.2})");
        }
        counter += 1;
    }
}

/**Методы класса приложения */
impl App {
    /**Конструктор приложения */
    pub fn new() -> Self {
        let mut slf = Self { // создаем поля
            first_speed: 0,
            second_speed: 0,
            exit: Arc::new(AtomicUsize::new(0)),

            /*// Клонируем указатели на мьютексы для передачи в потоки
            buffer_mutex_ref1:buffer_mutex.clone(),
            buffer_mutex_ref2:buffer_mutex.clone(),

            output_mutex_ref1:output_mutex.clone(),
            output_mutex_ref2:output_mutex.clone(),*/

            first_handle: None,
            second_handle: None,
        };

        // Создаем мьютексы, оборачиваем в arc для разделения доступа к ним
        let buffer_mutex_ref = Arc::new((Mutex::new(LimitedVec::new(BUFFER_SIZE)), Condvar::new()));
        let output_mutex_ref = Arc::new(Mutex::new(()));

        // Клонируем указатели на мьютексы для передачи и создаем потоки
        slf.first_handle = Some(thread::spawn({
            let buffer_mutex = buffer_mutex_ref.clone();
            let output_mutex = output_mutex_ref.clone();
            move || {
                first_thread(buffer_mutex, output_mutex);
            }
        }));

        slf.second_handle = Some(thread::spawn({
            let buffer_mutex = buffer_mutex_ref.clone();
            let output_mutex = output_mutex_ref.clone();
            move || {
                second_thread(buffer_mutex, output_mutex);
            }
        }));

        slf                       // возвращаем ссылку на созданный экземпляр приложения
    }

    fn first_table(&self, ui: &mut egui::Ui, table_name: &str, title: &str) {
        ui.vertical(|ui| {
            ui.label(title);
            egui::Frame::none()
                .stroke(egui::Stroke::new(2.0, egui::Color32::GRAY))
                .inner_margin(egui::style::Margin::same(5.0))
                .show(ui, |ui| {
                    egui::ScrollArea::new([false, true]).show(ui, |ui| {
                        egui::Grid::new(table_name).show(ui, |ui| {
                          
                        });
                    });
                });
        });
    }

    fn second_table(&self, ui: &mut egui::Ui, table_name: &str, title: &str) {
        ui.vertical(|ui| {
            ui.label(title);
            egui::Frame::none()
                .stroke(egui::Stroke::new(2.0, egui::Color32::GRAY))
                .inner_margin(egui::style::Margin::same(5.0))
                .show(ui, |ui| {
                    egui::ScrollArea::new([false, true]).show(ui, |ui| {
                        egui::Grid::new(table_name).show(ui, |ui| {

                        });
                    });
                });
        });
    }
}
