using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using Npgsql;

namespace WindowsFormsAppDataBase
{
    public partial class Form1 : Form
    {
        NpgsqlConnection connect;

        public Form1()
        {
            InitializeComponent();
        }

        bool ConnectOpen()
        {
            string sql = $"Host={textBox1.Text};Username={textBox2.Text};Password={textBox3.Text};Database={textBox4.Text}";
            connect = new NpgsqlConnection(sql);
            try
            {
                connect.Open();
                return true;
            } catch(Exception ex)
            {
                return false;
            }
        }

        bool LoadTable()
        {
            if (!ConnectOpen()) return false;
            NpgsqlCommand cmd = new NpgsqlCommand(
                "select e.first_name as Имя, e.second_name as Фамилия, e.middle_name as Отчество, v.model as Модель, v.kind as Gear, v.id as Номер\n" +
                "from examinee e, vehicle v\n" +
                "where v.id = e.id_vehicle;",
            connect);
            DataTable dt = new DataTable();
            dt.Load(cmd.ExecuteReader());
            dataGridView.DataSource = dt;
            connect.Close();
            return true;
        }

        private void button1_MouseClick(object sender, MouseEventArgs e)
        {
            if (LoadTable())
            {
                MessageBox.Show("Соеденение установлено");
                buttonAdd.Enabled = true;
                buttonDelete.Enabled = true;
                button1.Enabled = false;
                textBox1.Enabled = false;
                textBox2.Enabled = false;
                textBox3.Enabled = false;
                textBox4.Enabled = false;
            }
            else
            {
                MessageBox.Show("Ошибка.\nСоеденение не установлено");
            }
        }

        private void buttonAdd_MouseClick(object sender, MouseEventArgs e)
        {
            if (textBoxName.Text.Length > 0)
            {
                ConnectOpen();
                int id;
                Int32.TryParse(textBoxId.Text, out id);
                string[] NameArr = textBoxName.Text.Split(' ');
                try
                {
                    NpgsqlCommand cmd = new NpgsqlCommand($"insert into examinee(first_name, second_name, middle_name, id_vehicle) values('{NameArr[0]}', '{NameArr[1]}', '{NameArr[2]}', {id});",
                    connect);
                    NpgsqlDataReader reader = cmd.ExecuteReader();
                }
                catch(Exception ex)
                {
                    MessageBox.Show("Ошибка.\nВведены неверные данные");
                }
                connect.Close();
                LoadTable();
            }
        }

        private void buttonDelete_MouseClick(object sender, MouseEventArgs e)
        {
            ConnectOpen();
            int id;
            Int32.TryParse(textBoxId.Text, out id);
            string[] NameArr = textBoxName.Text.Split(' ');
            try
            {
                NpgsqlCommand cmd = new NpgsqlCommand($"DELETE FROM examinee WHERE first_name = '{NameArr[0]}' and second_name = '{NameArr[1]}' and middle_name = '{NameArr[2]}' and id_vehicle = {id}; ",
                connect);
                NpgsqlDataReader reader = cmd.ExecuteReader();
            }
            catch (Exception ex)
            {
                MessageBox.Show("Ошибка.\nВведены неверные данные");
            }
            connect.Close();
            LoadTable();
        }
    }
}
