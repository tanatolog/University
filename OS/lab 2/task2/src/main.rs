use eframe::egui;

mod gui;
mod limeted_vec;
mod dekker;
mod shared_container;

use gui::App;

fn main() -> Result<(), eframe::Error> {

    let options = eframe::NativeOptions {             // настройки окна приложения
        default_theme: eframe::Theme::Light,
        initial_window_size: Some(egui::vec2(800.0, 500.0)),    // Устанавливаем начальный размер
        ..Default::default()                                         // остальные настройки беруться по умолчанию
    };

    eframe::run_native(                                              // запуск приложения
        "Синхронизация потоков 2",
        options,
        Box::new(|_| { Box::new(App::new()) }),         // приложение будет иметь вид App
    )
}