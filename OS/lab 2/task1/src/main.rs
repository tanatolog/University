use eframe::egui;

mod gui;
mod limeted_vec;
mod model;

use gui::App;

fn main() -> Result<(), eframe::Error> {

    let options = eframe::NativeOptions {             // настройки окна приложения
        default_theme: eframe::Theme::Light,
        initial_window_size: Some(egui::vec2(1030.0, 720.0)),   // Устанавливаем начальный размер
        ..Default::default()                                         // остальные настройки беруться по умолчанию
    };

    eframe::run_native(                                              // запуск приложения
        "Синхронизация потоков 1",
        options,
        Box::new(|_| { Box::new(App::new()) }),         // приложение будет иметь вид App
    )
}