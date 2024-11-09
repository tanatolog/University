use eframe::egui;
use std::thread::{self, JoinHandle};
use std::sync::atomic::{AtomicUsize, Ordering};
use std::sync::{Arc, Mutex};
use std::time::Duration;

use crate::limeted_vec::LimitedVec;
use crate::shared_container::SharedContainer;

const TASK_TEXT: &str = "Задание: Задачу о производителе и потребителе с кольцевым буфером решить с помощью алгоритма Деккера.";

const BUFFER_SIZE: usize = 6;
const TASK_SIZE: usize = 100;

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
            ui.label("Скорость производителя:");
            ui.add(egui::Slider::new(&mut *self.first_speed_ref.lock().unwrap(), 0..=100));
            ui.label("Скорость потребителя:");
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
                .min_width(300.0)
                .resizable(false)
                .show(ctx, |ui| {
                    self.first_table(ui, "table1", "Производитель");
                });

            egui::SidePanel::right("table2")            // побочная правая панель
                .min_width(300.0)
                .resizable(false)
                .show(ctx, |ui| {
                    self.second_table(ui, "table2", "Потребитель");
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
fn first_thread(shared_buffer: Arc<SharedContainer<LimitedVec<usize>>>, output_mutex: Arc<Mutex<Vec<String>>>, speed: Arc<Mutex<usize>>) {
    for i in 1..=TASK_SIZE {
        let length: usize;
        delay(speed.clone());

        {
            let lock = &*shared_buffer;  // разыменоваем arc и получаем ссылку на кортеж SharedContainer<LimitedVec<f64>>
            let mut buffer = lock.get_first();    // ожидание освобождения ресурса и его захват

            while buffer.len() == BUFFER_SIZE {                           // если в буфере нет места, то освобождаем рес и ждем
                lock.unlock_first();
                thread::sleep(Duration::from_millis(100));
                buffer = lock.get_first();
            }

            buffer.push(i).unwrap();
            length = buffer.len();
            lock.unlock_first();                                          // Освобождение реса
        }                                       

        let entry = format!("Положил продукт №{i}, в буфере {length}");
        {
            output_mutex.lock().unwrap().push(entry);                     // ожидание освобождения мьютекса и его захват
            // Освобождение мьютекса
        }
    }
}

/**Функция для потока 2*/
fn second_thread(shared_buffer: Arc<SharedContainer<LimitedVec<usize>>>, output_mutex: Arc<Mutex<Vec<String>>>, speed: Arc<Mutex<usize>>) {
    for _i in 1..=TASK_SIZE {
        let product: usize;
        let length: usize;
        delay(speed.clone());

        {
            let lock = &*shared_buffer;  // разыменоваем arc и получаем ссылку на кортеж SharedContainer<LimitedVec<f64>>
            let mut buffer = lock.get_second();   // ожидание освобождения ресурса и его захват
    
            while buffer.is_empty() {                                     // если буфер пуст, то освобождаем рес и ждем
                    lock.unlock_second();
                    thread::sleep(Duration::from_millis(100));
                    buffer = lock.get_second();
            }

            product = buffer.remove(0).unwrap();
            length = buffer.len();
            lock.unlock_second();                                         // Освобождение реса
        }

        let entry = format!("Получил продукт №{product}, в буфере {length}");
        {
            output_mutex.lock().unwrap().push(entry);
            // Освобождение мьютекса
        }
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
        let buffer_mutex_ref = Arc::new(SharedContainer::new(LimitedVec::new(BUFFER_SIZE)));
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