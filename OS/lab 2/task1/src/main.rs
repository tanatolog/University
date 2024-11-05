mod gui;
mod limeted_vec;
mod model;

use gui::App;

fn main() -> Result<(), eframe::Error> {

    let options = eframe::NativeOptions { // настройки окна приложения
        default_theme: eframe::Theme::Light,
        maximized: false,
        ..Default::default() // остальные настройки беруться по умолчанию
    };

    eframe::run_native( // запуск приложения
        "Синхронизация потоков",
        options,
        Box::new(|_| { Box::new(App::new()) }), // приложение будет иметь вид App
    )
}