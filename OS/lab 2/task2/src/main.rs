use std::sync::{Arc, Mutex, Condvar};
use std::thread;
use std::time::Duration;

mod limeted_vec;
use limeted_vec::LimitedVec;

const BUFFER_SIZE: usize = 36;
const T1_SPEED: u64 = 150;
const T2_SPEED: u64 = 200;

/**Функция для вычисления площади треугольника*/
fn calculate_triangle_area(x1: f64, y1: f64, x2: f64, y2: f64, x3: f64, y3: f64) -> f64 {
    ((x1 * (y2 - y3) + x2 * (y3 - y1) + x3 * (y1 - y2)) / 2.0).abs()
}

/**Функция для вычисления площади поверхности пирамиды*/
fn calculate_pyramid_surface(area: f64, height: f64) -> f64 {
    area * height
}

/**Функция потока 1*/
fn thread1(buffer_mutex: Arc<(Mutex<LimitedVec<f64>>, Condvar)>, output_mutex: Arc<Mutex<()>>) {
    let mut counter = 1;
    for i in 9..=14 {
        for j in 9..=14 {

            let area = calculate_triangle_area(4.0, 3.0, 8.0, 12.0, i as f64, j as f64);
            let pyramid_surface = calculate_pyramid_surface(area, (i + j) as f64);

            thread::sleep(Duration::from_millis(T1_SPEED));

            {
                let (lock, cvar) = &*buffer_mutex;  // разыменоваем arc и получаем ссылку на кортеж (Mutex<LimitedVec<f64>>, Condvar)
                let mut buffer = lock.lock().unwrap();  // ожидание освобождения мьютекса и его захват

                while buffer.len() == BUFFER_SIZE {                                     // если в буфере нет места, то освобождаем мьютекс и ждем
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

/**Функция для расчета координат третьих точек треугольника по координатам двух других точек и площади*/
fn find_third_vertex(x1: f64, y1: f64, x2: f64, y2: f64, area: f64) -> ((f64, f64), (f64, f64)) {
    // Вычисляем разницу по координатам
    let delta_x = x2 - x1;
    let delta_y = y2 - y1;
    
    // Вычисляем возможные значения для координат третьей точки (x3, y3)
    let factor = (2.0 * area) / (delta_x.powi(2) + delta_y.powi(2)).sqrt();

    // Два возможных решения для y3
    let x3_1 = x1 + delta_y * factor;
    let y3_1 = y1 - delta_x * factor;

    let x3_2 = x1 - delta_y * factor;
    let y3_2 = y1 + delta_x * factor;

    // Возвращаем два возможных варианта координат
    ((x3_1, y3_1), (x3_2, y3_2))
}

/**Функция для потока 2*/
fn thread2(buffer_mutex: Arc<(Mutex<LimitedVec<f64>>, Condvar)>, output_mutex: Arc<Mutex<()>>) {
    let mut counter = 1;

    while counter <= 36 {
        let area: f64;

        thread::sleep(Duration::from_millis(T2_SPEED));

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

fn main() {
    // Создаем мьютексы, оборачиваем в arc для разделения доступа к ним
    let buffer_mutex_ref1 = Arc::new((Mutex::new(LimitedVec::new(BUFFER_SIZE)), Condvar::new()));
    let output_mutex_ref1 = Arc::new(Mutex::new(()));

    // Клонируем указатель на мьютексы для передачи в поток 2
    let buffer_mutex_ref2 = Arc::clone(&buffer_mutex_ref1);
    let output_mutex_ref2 = Arc::clone(&output_mutex_ref1);

    // Создаем потоки
    let handle1 = thread::spawn(move || {
        thread1(buffer_mutex_ref1, output_mutex_ref1);
    });

    let handle2 = thread::spawn(move || {
        thread2(buffer_mutex_ref2, output_mutex_ref2);
    });

    // Ожидаем завершения потоков
    handle1.join().unwrap();
    handle2.join().unwrap();
}

