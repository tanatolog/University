#include "MyForm.h"

using namespace System;
using namespace System::Windows::Forms;
using namespace Npgsql;
using namespace Mono;


[STAThread]
void main(array<String^>^ arg) {
    Application::EnableVisualStyles();
    Application::SetCompatibleTextRenderingDefault(false);

    WindowsFormsAppDataBase::Form1 Form1; //WinFormsTest - имя вашего проекта
    Application::Run(% Form1);
}