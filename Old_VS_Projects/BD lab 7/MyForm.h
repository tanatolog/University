#include <iostream>
#include <string>
#include <Windows.h>

using namespace System;
using namespace System::ComponentModel;
using namespace System::Data;
using namespace System::Drawing;
using namespace System::Windows::Forms;
using namespace Npgsql;
using namespace Mono;

namespace WindowsFormsAppDataBase {

    public ref class Form1 : public Form
    {
    public:
        Form1()
        {
            InitializeComponent();
        }

    protected:
        ~Form1()
        {
            if (components)
            {
                delete components;
            }
        }

    private:
        IContainer^ components;
        DataGridView^ dataGridView;
        TabControl^ tabControl1;
        TabPage^ tabPage1;
        TabPage^ tabPage2;
        Label^ label1;
        Label^ label2;
        Label^ label3;
        Label^ label4;
        Button^ button1;
        TextBox^ textBox1;
        TextBox^ textBox2;
        TextBox^ textBox3;
        TextBox^ textBox4;
        Button^ buttonDelete;
        Button^ buttonAdd;
        Label^ label6;
        Label^ label5;
        TextBox^ textBoxId;
        TextBox^ textBoxName;
        NpgsqlConnection^ connect;

        void InitializeComponent(void)
        {
            this->dataGridView = (gcnew System::Windows::Forms::DataGridView());
            this->tabControl1 = (gcnew System::Windows::Forms::TabControl());
            this->tabPage1 = (gcnew System::Windows::Forms::TabPage());
            this->button1 = (gcnew System::Windows::Forms::Button());
            this->textBox4 = (gcnew System::Windows::Forms::TextBox());
            this->label3 = (gcnew System::Windows::Forms::Label());
            this->textBox3 = (gcnew System::Windows::Forms::TextBox());
            this->label4 = (gcnew System::Windows::Forms::Label());
            this->textBox2 = (gcnew System::Windows::Forms::TextBox());
            this->label2 = (gcnew System::Windows::Forms::Label());
            this->textBox1 = (gcnew System::Windows::Forms::TextBox());
            this->label1 = (gcnew System::Windows::Forms::Label());
            this->tabPage2 = (gcnew System::Windows::Forms::TabPage());
            this->buttonDelete = (gcnew System::Windows::Forms::Button());
            this->buttonAdd = (gcnew System::Windows::Forms::Button());
            this->label6 = (gcnew System::Windows::Forms::Label());
            this->label5 = (gcnew System::Windows::Forms::Label());
            this->textBoxId = (gcnew System::Windows::Forms::TextBox());
            this->textBoxName = (gcnew System::Windows::Forms::TextBox());

            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView))->BeginInit();
            this->tabControl1->SuspendLayout();
            this->tabPage1->SuspendLayout();
            this->tabPage2->SuspendLayout();
            this->SuspendLayout();

            // 
            // dataGridView
            // 
            this->dataGridView->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
            this->dataGridView->Location = System::Drawing::Point(27, 9);
            this->dataGridView->Margin = System::Windows::Forms::Padding(4, 5, 4, 5);
            this->dataGridView->Name = L"dataGridView";
            this->dataGridView->RowHeadersWidth = 62;
            this->dataGridView->Size = System::Drawing::Size(1019, 300);
            this->dataGridView->TabIndex = 0;
            // 
            // tabControl1
            // 
            this->tabControl1->Controls->Add(this->tabPage1);
            this->tabControl1->Controls->Add(this->tabPage2);
            this->tabControl1->Location = System::Drawing::Point(18, 18);
            this->tabControl1->Margin = System::Windows::Forms::Padding(4, 5, 4, 5);
            this->tabControl1->Name = L"tabControl1";
            this->tabControl1->SelectedIndex = 0;
            this->tabControl1->Size = System::Drawing::Size(1075, 506);
            this->tabControl1->TabIndex = 1;
            // 
            // tabPage1
            // 
            this->tabPage1->BackColor = System::Drawing::Color::Transparent;
            this->tabPage1->Controls->Add(this->button1);
            this->tabPage1->Controls->Add(this->textBox4);
            this->tabPage1->Controls->Add(this->label3);
            this->tabPage1->Controls->Add(this->textBox3);
            this->tabPage1->Controls->Add(this->label4);
            this->tabPage1->Controls->Add(this->textBox2);
            this->tabPage1->Controls->Add(this->label2);
            this->tabPage1->Controls->Add(this->textBox1);
            this->tabPage1->Controls->Add(this->label1);
            this->tabPage1->Location = System::Drawing::Point(4, 29);
            this->tabPage1->Margin = System::Windows::Forms::Padding(4, 5, 4, 5);
            this->tabPage1->Name = L"tabPage1";
            this->tabPage1->Padding = System::Windows::Forms::Padding(4, 5, 4, 5);
            this->tabPage1->Size = System::Drawing::Size(1067, 473);
            this->tabPage1->TabIndex = 0;
            this->tabPage1->Text = L"Sign";
            // 
            // button1
            // 
            this->button1->Location = System::Drawing::Point(444, 330);
            this->button1->Margin = System::Windows::Forms::Padding(4, 5, 4, 5);
            this->button1->Name = L"button1";
            this->button1->Size = System::Drawing::Size(141, 57);
            this->button1->TabIndex = 8;
            this->button1->Text = L"Connect";
            this->button1->UseVisualStyleBackColor = true;
            this->button1->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::button1_MouseClick);
            // 
            // textBox4
            // 
            this->textBox4->Location = System::Drawing::Point(552, 239);
            this->textBox4->Margin = System::Windows::Forms::Padding(4, 5, 4, 5);
            this->textBox4->Name = L"textBox4";
            this->textBox4->Size = System::Drawing::Size(154, 26);
            this->textBox4->TabIndex = 7;
            this->textBox4->Text = L"lab";
            // 
            // label3
            // 
            this->label3->AutoSize = true;
            this->label3->Font = (gcnew System::Drawing::Font(L"Arial", 16.5F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
            this->label3->Location = System::Drawing::Point(544, 194);
            this->label3->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
            this->label3->Name = L"label3";
            this->label3->Size = System::Drawing::Size(171, 38);
            this->label3->TabIndex = 6;
            this->label3->Text = L"DB Name:";
            // 
            // textBox3
            // 
            this->textBox3->Location = System::Drawing::Point(328, 239);
            this->textBox3->Margin = System::Windows::Forms::Padding(4, 5, 4, 5);
            this->textBox3->Name = L"textBox3";
            this->textBox3->PasswordChar = '*';
            this->textBox3->Size = System::Drawing::Size(154, 26);
            this->textBox3->TabIndex = 5;
            this->textBox3->Text = L"db_user";
            // 
            // label4
            // 
            this->label4->AutoSize = true;
            this->label4->Font = (gcnew System::Drawing::Font(L"Arial", 16.5F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
            this->label4->Location = System::Drawing::Point(320, 194);
            this->label4->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
            this->label4->Name = L"label4";
            this->label4->Size = System::Drawing::Size(181, 38);
            this->label4->TabIndex = 4;
            this->label4->Text = L"Password:";
            // 
            // textBox2
            // 
            this->textBox2->Location = System::Drawing::Point(552, 116);
            this->textBox2->Margin = System::Windows::Forms::Padding(4, 5, 4, 5);
            this->textBox2->Name = L"textBox2";
            this->textBox2->Size = System::Drawing::Size(154, 26);
            this->textBox2->TabIndex = 3;
            this->textBox2->Text = L"db_user";
            // 
            // label2
            // 
            this->label2->AutoSize = true;
            this->label2->Font = (gcnew System::Drawing::Font(L"Arial", 16.5F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
            this->label2->Location = System::Drawing::Point(570, 71);
            this->label2->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
            this->label2->Name = L"label2";
            this->label2->Size = System::Drawing::Size(116, 38);
            this->label2->TabIndex = 2;
            this->label2->Text = L"Name:";
            // 
            // textBox1
            // 
            this->textBox1->Location = System::Drawing::Point(328, 116);
            this->textBox1->Margin = System::Windows::Forms::Padding(4, 5, 4, 5);
            this->textBox1->Name = L"textBox1";
            this->textBox1->Size = System::Drawing::Size(154, 26);
            this->textBox1->TabIndex = 1;
            this->textBox1->Text = L"localhost:5432";
            // 
            // label1
            // 
            this->label1->AutoSize = true;
            this->label1->Font = (gcnew System::Drawing::Font(L"Arial", 16.5F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
            this->label1->Location = System::Drawing::Point(378, 71);
            this->label1->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
            this->label1->Name = L"label1";
            this->label1->Size = System::Drawing::Size(58, 38);
            this->label1->TabIndex = 0;
            this->label1->Text = L"IP:";
            // 
            // tabPage2
            // 
            this->tabPage2->Controls->Add(this->buttonDelete);
            this->tabPage2->Controls->Add(this->buttonAdd);
            this->tabPage2->Controls->Add(this->label6);
            this->tabPage2->Controls->Add(this->label5);
            this->tabPage2->Controls->Add(this->textBoxId);
            this->tabPage2->Controls->Add(this->textBoxName);
            this->tabPage2->Controls->Add(this->dataGridView);
            this->tabPage2->Location = System::Drawing::Point(4, 29);
            this->tabPage2->Margin = System::Windows::Forms::Padding(4, 5, 4, 5);
            this->tabPage2->Name = L"tabPage2";
            this->tabPage2->Padding = System::Windows::Forms::Padding(4, 5, 4, 5);
            this->tabPage2->Size = System::Drawing::Size(1067, 473);
            this->tabPage2->TabIndex = 1;
            this->tabPage2->Text = L"Table";
            this->tabPage2->UseVisualStyleBackColor = true;
            // 
            // buttonDelete
            // 
            this->buttonDelete->Enabled = false;
            this->buttonDelete->Location = System::Drawing::Point(385, 392);
            this->buttonDelete->Margin = System::Windows::Forms::Padding(4, 5, 4, 5);
            this->buttonDelete->Name = L"buttonDelete";
            this->buttonDelete->Size = System::Drawing::Size(98, 51);
            this->buttonDelete->TabIndex = 7;
            this->buttonDelete->Text = L"DELETE";
            this->buttonDelete->UseVisualStyleBackColor = true;
            this->buttonDelete->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::buttonDelete_MouseClick);
            // 
            // buttonAdd
            // 
            this->buttonAdd->Enabled = false;
            this->buttonAdd->Location = System::Drawing::Point(385, 323);
            this->buttonAdd->Margin = System::Windows::Forms::Padding(4, 5, 4, 5);
            this->buttonAdd->Name = L"buttonAdd";
            this->buttonAdd->Size = System::Drawing::Size(98, 51);
            this->buttonAdd->TabIndex = 5;
            this->buttonAdd->Text = L"ADD";
            this->buttonAdd->UseVisualStyleBackColor = true;
            this->buttonAdd->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::buttonAdd_MouseClick);
            // 
            // label6
            // 
            this->label6->AutoSize = true;
            this->label6->Location = System::Drawing::Point(23, 392);
            this->label6->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
            this->label6->Name = L"label6";
            this->label6->Size = System::Drawing::Size(246, 20);
            this->label6->TabIndex = 4;
            this->label6->Text = L"Номер существующей машины:";
            // 
            // label5
            // 
            this->label5->AutoSize = true;
            this->label5->Location = System::Drawing::Point(23, 323);
            this->label5->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
            this->label5->Name = L"label5";
            this->label5->Size = System::Drawing::Size(170, 20);
            this->label5->TabIndex = 3;
            this->label5->Text = L"ФИО экзаменуемого:";
            // 
            // textBoxId
            // 
            this->textBoxId->Location = System::Drawing::Point(27, 417);
            this->textBoxId->Margin = System::Windows::Forms::Padding(4, 5, 4, 5);
            this->textBoxId->Name = L"textBoxId";
            this->textBoxId->Size = System::Drawing::Size(115, 26);
            this->textBoxId->TabIndex = 2;
            // 
            // textBoxName
            // 
            this->textBoxName->Location = System::Drawing::Point(27, 348);
            this->textBoxName->Margin = System::Windows::Forms::Padding(4, 5, 4, 5);
            this->textBoxName->Name = L"textBoxName";
            this->textBoxName->Size = System::Drawing::Size(326, 26);
            this->textBoxName->TabIndex = 1;
            // 
            // Form1
            // 
            this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
            this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
            this->BackColor = System::Drawing::SystemColors::Window;
            this->ClientSize = System::Drawing::Size(1103, 538);
            this->Controls->Add(this->tabControl1);
            this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
            this->Margin = System::Windows::Forms::Padding(4, 5, 4, 5);
            this->Name = L"Form1";
            this->Text = L"BD Editor";
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView))->EndInit();
            this->tabControl1->ResumeLayout(false);
            this->tabPage1->ResumeLayout(false);
            this->tabPage1->PerformLayout();
            this->tabPage2->ResumeLayout(false);
            this->tabPage2->PerformLayout();
            this->ResumeLayout(false);
        }

        bool ConnectOpen()
        {
            String^ sql = String::Format("Host={0};Username={1};Password={2};Database={3}",
                textBox1->Text, textBox2->Text, textBox3->Text, textBox4->Text);
            connect = gcnew NpgsqlConnection(sql);
            try
            {
                connect->Open();
                return true;
            }
            catch (Exception^ ex)
            {
                return false;
            }
        }

        bool LoadTable()
        {
            if (!ConnectOpen()) return false;

            NpgsqlCommand^ cmd = gcnew NpgsqlCommand(
                "select e.first_name as Имя, e.second_name as Фамилия, e.middle_name as Отчество, v.model as Модель, v.kind as Gear, v.id as Номер\n" +
                "from examinee e, vehicle v\n" +
                "where v.id = e.id_vehicle;", connect);
            DataTable^ dt = gcnew DataTable();
            dt->Load(cmd->ExecuteReader());
            dataGridView->DataSource = dt;
            connect->Close();
            return true;
        }

        void button1_MouseClick(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e)
        {
            if (LoadTable())
            {
                MessageBox::Show("Соединение установлено");
                buttonAdd->Enabled = true;
                buttonDelete->Enabled = true;
                button1->Enabled = false;
                textBox1->Enabled = false;
                textBox2->Enabled = false;
                textBox3->Enabled = false;
                textBox4->Enabled = false;
            }
            else
            {
                MessageBox::Show("Ошибка.\nСоединение не установлено");
            }
        }

        void buttonDelete_MouseClick(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e)
        {
            ConnectOpen();
            int id;
            Int32::TryParse(textBoxId->Text, id);
            array<String^>^ NameArr = textBoxName->Text->Split(' ');
            try
            {
                NpgsqlCommand^ cmd = gcnew NpgsqlCommand(
                    String::Format("DELETE FROM examinee WHERE first_name = '{0}' and second_name = '{1}' and middle_name = '{2}' and id_vehicle = {3};",
                        NameArr[0], NameArr[1], NameArr[2], id), connect);
                System::Data::Common::DbDataReader^ reader = cmd->ExecuteReader();
            }
            catch (Exception^ ex)
            {
                MessageBox::Show("Ошибка.\nВведены неверные данные");
            }
            connect->Close();
            LoadTable();
        }

        void buttonAdd_MouseClick(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e)
        {
            if (textBoxName->Text->Length > 0)
            {
                ConnectOpen();
                int id;
                Int32::TryParse(textBoxId->Text, id);
                array<String^>^ NameArr = textBoxName->Text->Split(' ');
                try
                {
                    NpgsqlCommand^ cmd = gcnew NpgsqlCommand(
                        String::Format("insert into examinee(first_name, second_name, middle_name, id_vehicle) values('{0}', '{1}', '{2}', {3});",
                            NameArr[0], NameArr[1], NameArr[2], id), connect);
                    System::Data::Common::DbDataReader^ reader = cmd->ExecuteReader();
                }
                catch (Exception^ ex)
                {
                    MessageBox::Show("Ошибка.\nВведены неверные данные");
                }
                connect->Close();
                LoadTable();
            }
        }

#pragma endregion
    };
}