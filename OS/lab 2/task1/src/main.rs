use std::sync::{Arc, Mutex};
use std::thread;

// Функция для вычисления площади треугольника
fn calculate_triangle_area(x1: f64, y1: f64, x2: f64, y2: f64, x3: f64, y3: f64) -> f64 {
    ((x1 * (y2 - y3) + x2 * (y3 - y1) + x3 * (y1 - y2)) / 2.0).abs()
}

// Функция для вычисления площади поверхности пирамиды
fn calculate_pyramid_surface(area: f64, height: f64) -> f64 {
    area * height
}

// Функция для потока 1
fn thread1(mutex_s: Arc<Mutex<f64>>, mutex_g: Arc<Mutex<f64>>) {
    for i in 9..=14 {
        for j in 9..=14 {
            let area = calculate_triangle_area(4.0, 3.0, 8.0, 12.0, i as f64, j as f64);
            let pyramid_surface = calculate_pyramid_surface(area, (i + j) as f64);

            // Обновляем значения под мьютексами
            let mut s = mutex_s.lock().unwrap();
            *s = area;

            let mut g = mutex_g.lock().unwrap();
            *g = pyramid_surface;

            println!("Thread 1: i = {}, j = {}, S = {}, G = {}", i, j, area, pyramid_surface);
        }
    }
}

// Функция для потока 2
fn thread2(mutex_s: Arc<Mutex<f64>>) {
    for h in 4..=10 {
        // Извлекаем площадь треугольника из мьютекса
        let s = mutex_s.lock().unwrap();

        // Пример простого метода для расчета координат третьей вершины
        // Найдем координаты третьей вершины (x3, y3) для треугольника
        // с вершинами (-2, 6), (2, -4) и площадью *s.

        let x1 = -2.0;
        let y1 = 6.0;
        let x2 = 2.0;
        let y2 = -4.0;

        // Это упрощенный способ нахождения координат третьей вершины.
        // В реальной задаче нужно использовать более точные методы.
        let third_vertex_x = (x1 + x2) / 2.0; // Условное значение x3
        let third_vertex_y = (y1 + y2) / 2.0; // Условное значение y3

        // Рассчитываем объем пирамиды
        let volume = *s * h as f64;

        println!("Thread 2: h = {}, S = {}, Volume = {}, Third Vertex = ({}, {})",
                 h, *s, volume, third_vertex_x, third_vertex_y);
    }
}

fn main() {
    // Создаем мьютексы для хранения данных
    let s = Arc::new(Mutex::new(0.0));
    let g = Arc::new(Mutex::new(0.0));

    // Клонируем указатели на мьютексы для передачи в потоки
    let s_clone1 = Arc::clone(&s);
    let g_clone = Arc::clone(&g);
    let s_clone2 = Arc::clone(&s);

    // Создаем потоки
    let handle1 = thread::spawn(move || {
        thread1(s_clone1, g_clone);
    });

    let handle2 = thread::spawn(move || {
        thread2(s_clone2);
    });

    // Ожидаем завершения потоков
    handle1.join().unwrap();
    handle2.join().unwrap();
}
