
namespace CGlaba1
{
    partial class Form1
    {
        /// <summary>
        /// Обязательная переменная конструктора.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Освободить все используемые ресурсы.
        /// </summary>
        /// <param name="disposing">истинно, если управляемый ресурс должен быть удален; иначе ложно.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Код, автоматически созданный конструктором форм Windows

        /// <summary>
        /// Требуемый метод для поддержки конструктора — не изменяйте 
        /// содержимое этого метода с помощью редактора кода.
        /// </summary>
        private void InitializeComponent()
        {
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(Form1));
            this.toolStrip1 = new System.Windows.Forms.ToolStrip();
            this.DownButton1 = new System.Windows.Forms.ToolStripDropDownButton();
            this.простойАлгоритмToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.Item1 = new System.Windows.Forms.ToolStripMenuItem();
            this.Item2 = new System.Windows.Forms.ToolStripMenuItem();
            this.алгоритмыБрезенхемаToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.четырехИВосьмисвязнойРToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.Item3 = new System.Windows.Forms.ToolStripMenuItem();
            this.Item4 = new System.Windows.Forms.ToolStripMenuItem();
            this.Item5 = new System.Windows.Forms.ToolStripMenuItem();
            this.анимацияToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.Item6 = new System.Windows.Forms.ToolStripMenuItem();
            this.Item7 = new System.Windows.Forms.ToolStripMenuItem();
            this.выходToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripSeparator1 = new System.Windows.Forms.ToolStripSeparator();
            this.DownButton2 = new System.Windows.Forms.ToolStripDropDownButton();
            this.черныйItem = new System.Windows.Forms.ToolStripMenuItem();
            this.красныйItem = new System.Windows.Forms.ToolStripMenuItem();
            this.синийItem = new System.Windows.Forms.ToolStripMenuItem();
            this.желтыйItem = new System.Windows.Forms.ToolStripMenuItem();
            this.зеленыйItem = new System.Windows.Forms.ToolStripMenuItem();
            this.TextBox3 = new System.Windows.Forms.MaskedTextBox();
            this.TextBox4 = new System.Windows.Forms.MaskedTextBox();
            this.label2 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.pictureBox1 = new System.Windows.Forms.PictureBox();
            this.panel1 = new System.Windows.Forms.Panel();
            this.button2 = new System.Windows.Forms.Button();
            this.button1 = new System.Windows.Forms.Button();
            this.TextBox1 = new System.Windows.Forms.MaskedTextBox();
            this.label4 = new System.Windows.Forms.Label();
            this.label5 = new System.Windows.Forms.Label();
            this.TextBox2 = new System.Windows.Forms.MaskedTextBox();
            this.CheckBox1 = new System.Windows.Forms.CheckBox();
            this.saveFileDialog1 = new System.Windows.Forms.SaveFileDialog();
            this.button3 = new System.Windows.Forms.Button();
            this.toolStrip1.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).BeginInit();
            this.panel1.SuspendLayout();
            this.SuspendLayout();
            // 
            // toolStrip1
            // 
            this.toolStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.DownButton1,
            this.toolStripSeparator1,
            this.DownButton2});
            this.toolStrip1.Location = new System.Drawing.Point(0, 0);
            this.toolStrip1.Name = "toolStrip1";
            this.toolStrip1.Size = new System.Drawing.Size(994, 25);
            this.toolStrip1.TabIndex = 0;
            this.toolStrip1.Text = "toolStrip1";
            // 
            // DownButton1
            // 
            this.DownButton1.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Text;
            this.DownButton1.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.простойАлгоритмToolStripMenuItem,
            this.алгоритмыБрезенхемаToolStripMenuItem,
            this.анимацияToolStripMenuItem,
            this.выходToolStripMenuItem});
            this.DownButton1.Image = ((System.Drawing.Image)(resources.GetObject("DownButton1.Image")));
            this.DownButton1.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.DownButton1.Name = "DownButton1";
            this.DownButton1.Size = new System.Drawing.Size(58, 22);
            this.DownButton1.Text = "Режим";
            // 
            // простойАлгоритмToolStripMenuItem
            // 
            this.простойАлгоритмToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.Item1,
            this.Item2});
            this.простойАлгоритмToolStripMenuItem.Name = "простойАлгоритмToolStripMenuItem";
            this.простойАлгоритмToolStripMenuItem.Size = new System.Drawing.Size(206, 22);
            this.простойАлгоритмToolStripMenuItem.Text = "Простые алгоритмы";
            // 
            // Item1
            // 
            this.Item1.Checked = true;
            this.Item1.CheckState = System.Windows.Forms.CheckState.Checked;
            this.Item1.Name = "Item1";
            this.Item1.Size = new System.Drawing.Size(142, 22);
            this.Item1.Text = "Прямая";
            this.Item1.Click += new System.EventHandler(this.Item1_Click);
            // 
            // Item2
            // 
            this.Item2.Name = "Item2";
            this.Item2.Size = new System.Drawing.Size(142, 22);
            this.Item2.Text = "Окружность";
            this.Item2.Click += new System.EventHandler(this.Item2_Click);
            // 
            // алгоритмыБрезенхемаToolStripMenuItem
            // 
            this.алгоритмыБрезенхемаToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.четырехИВосьмисвязнойРToolStripMenuItem,
            this.Item5});
            this.алгоритмыБрезенхемаToolStripMenuItem.Name = "алгоритмыБрезенхемаToolStripMenuItem";
            this.алгоритмыБрезенхемаToolStripMenuItem.Size = new System.Drawing.Size(206, 22);
            this.алгоритмыБрезенхемаToolStripMenuItem.Text = "Алгоритмы Брезенхема";
            // 
            // четырехИВосьмисвязнойРToolStripMenuItem
            // 
            this.четырехИВосьмисвязнойРToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.Item3,
            this.Item4});
            this.четырехИВосьмисвязнойРToolStripMenuItem.Name = "четырехИВосьмисвязнойРToolStripMenuItem";
            this.четырехИВосьмисвязнойРToolStripMenuItem.Size = new System.Drawing.Size(142, 22);
            this.четырехИВосьмисвязнойРToolStripMenuItem.Text = "Прямая";
            // 
            // Item3
            // 
            this.Item3.Name = "Item3";
            this.Item3.Size = new System.Drawing.Size(220, 22);
            this.Item3.Text = "Четырехсвязная развертка";
            this.Item3.Click += new System.EventHandler(this.Item3_Click);
            // 
            // Item4
            // 
            this.Item4.Name = "Item4";
            this.Item4.Size = new System.Drawing.Size(220, 22);
            this.Item4.Text = "Восьмисвязная развертка";
            this.Item4.Click += new System.EventHandler(this.Item4_Click);
            // 
            // Item5
            // 
            this.Item5.Name = "Item5";
            this.Item5.Size = new System.Drawing.Size(142, 22);
            this.Item5.Text = "Окружность";
            this.Item5.Click += new System.EventHandler(this.Item5_Click);
            // 
            // анимацияToolStripMenuItem
            // 
            this.анимацияToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.Item6,
            this.Item7});
            this.анимацияToolStripMenuItem.Name = "анимацияToolStripMenuItem";
            this.анимацияToolStripMenuItem.Size = new System.Drawing.Size(206, 22);
            this.анимацияToolStripMenuItem.Text = "Анимация";
            // 
            // Item6
            // 
            this.Item6.Name = "Item6";
            this.Item6.Size = new System.Drawing.Size(193, 22);
            this.Item6.Text = "Движение по кругу";
            this.Item6.Click += new System.EventHandler(this.Item6_Click);
            // 
            // Item7
            // 
            this.Item7.Name = "Item7";
            this.Item7.Size = new System.Drawing.Size(193, 22);
            this.Item7.Text = "Движение по прямой";
            this.Item7.Click += new System.EventHandler(this.Item7_Click);
            // 
            // выходToolStripMenuItem
            // 
            this.выходToolStripMenuItem.Name = "выходToolStripMenuItem";
            this.выходToolStripMenuItem.Size = new System.Drawing.Size(206, 22);
            this.выходToolStripMenuItem.Text = "Выход";
            this.выходToolStripMenuItem.Click += new System.EventHandler(this.ВыходToolStripMenuItem_Click);
            // 
            // toolStripSeparator1
            // 
            this.toolStripSeparator1.Name = "toolStripSeparator1";
            this.toolStripSeparator1.Size = new System.Drawing.Size(6, 25);
            // 
            // DownButton2
            // 
            this.DownButton2.BackColor = System.Drawing.Color.Black;
            this.DownButton2.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.None;
            this.DownButton2.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.черныйItem,
            this.красныйItem,
            this.синийItem,
            this.желтыйItem,
            this.зеленыйItem});
            this.DownButton2.ForeColor = System.Drawing.Color.Black;
            this.DownButton2.Image = ((System.Drawing.Image)(resources.GetObject("DownButton2.Image")));
            this.DownButton2.ImageTransparentColor = System.Drawing.Color.Black;
            this.DownButton2.Name = "DownButton2";
            this.DownButton2.Size = new System.Drawing.Size(13, 22);
            this.DownButton2.Text = "     ";
            this.DownButton2.ToolTipText = "Цвет";
            // 
            // черныйItem
            // 
            this.черныйItem.Checked = true;
            this.черныйItem.CheckState = System.Windows.Forms.CheckState.Checked;
            this.черныйItem.ImageAlign = System.Drawing.ContentAlignment.TopLeft;
            this.черныйItem.Name = "черныйItem";
            this.черныйItem.Size = new System.Drawing.Size(123, 22);
            this.черныйItem.Text = "Черный";
            this.черныйItem.Click += new System.EventHandler(this.черныйToolStripMenuItem_Click);
            // 
            // красныйItem
            // 
            this.красныйItem.Name = "красныйItem";
            this.красныйItem.Size = new System.Drawing.Size(123, 22);
            this.красныйItem.Text = "Красный";
            this.красныйItem.Click += new System.EventHandler(this.красныйToolStripMenuItem_Click);
            // 
            // синийItem
            // 
            this.синийItem.Name = "синийItem";
            this.синийItem.Size = new System.Drawing.Size(123, 22);
            this.синийItem.Text = "Синий";
            this.синийItem.Click += new System.EventHandler(this.синийToolStripMenuItem_Click);
            // 
            // желтыйItem
            // 
            this.желтыйItem.Name = "желтыйItem";
            this.желтыйItem.Size = new System.Drawing.Size(123, 22);
            this.желтыйItem.Text = "Желтый";
            this.желтыйItem.Click += new System.EventHandler(this.желтыйToolStripMenuItem_Click);
            // 
            // зеленыйItem
            // 
            this.зеленыйItem.Name = "зеленыйItem";
            this.зеленыйItem.Size = new System.Drawing.Size(123, 22);
            this.зеленыйItem.Text = "Зеленый";
            this.зеленыйItem.Click += new System.EventHandler(this.зеленыйToolStripMenuItem_Click);
            // 
            // TextBox3
            // 
            this.TextBox3.HidePromptOnLeave = true;
            this.TextBox3.InsertKeyMode = System.Windows.Forms.InsertKeyMode.Overwrite;
            this.TextBox3.Location = new System.Drawing.Point(158, 15);
            this.TextBox3.Mask = "000";
            this.TextBox3.Name = "TextBox3";
            this.TextBox3.PromptChar = ' ';
            this.TextBox3.ResetOnPrompt = false;
            this.TextBox3.ResetOnSpace = false;
            this.TextBox3.RightToLeft = System.Windows.Forms.RightToLeft.No;
            this.TextBox3.Size = new System.Drawing.Size(77, 20);
            this.TextBox3.TabIndex = 1;
            this.TextBox3.Text = "0";
            this.TextBox3.ValidatingType = typeof(int);
            // 
            // TextBox4
            // 
            this.TextBox4.HidePromptOnLeave = true;
            this.TextBox4.InsertKeyMode = System.Windows.Forms.InsertKeyMode.Overwrite;
            this.TextBox4.Location = new System.Drawing.Point(295, 15);
            this.TextBox4.Mask = "000";
            this.TextBox4.Name = "TextBox4";
            this.TextBox4.PromptChar = ' ';
            this.TextBox4.ResetOnPrompt = false;
            this.TextBox4.ResetOnSpace = false;
            this.TextBox4.RightToLeft = System.Windows.Forms.RightToLeft.No;
            this.TextBox4.Size = new System.Drawing.Size(77, 20);
            this.TextBox4.TabIndex = 2;
            this.TextBox4.Text = "0";
            this.TextBox4.ValidatingType = typeof(int);
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.label2.Location = new System.Drawing.Point(259, 16);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(36, 16);
            this.label2.TabIndex = 5;
            this.label2.Text = "    Y2";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.label3.Location = new System.Drawing.Point(121, 15);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(38, 16);
            this.label3.TabIndex = 6;
            this.label3.Text = "    X2 ";
            // 
            // pictureBox1
            // 
            this.pictureBox1.BackColor = System.Drawing.Color.White;
            this.pictureBox1.Dock = System.Windows.Forms.DockStyle.Bottom;
            this.pictureBox1.Location = new System.Drawing.Point(0, 82);
            this.pictureBox1.Name = "pictureBox1";
            this.pictureBox1.Size = new System.Drawing.Size(994, 458);
            this.pictureBox1.TabIndex = 7;
            this.pictureBox1.TabStop = false;
            // 
            // panel1
            // 
            this.panel1.Controls.Add(this.button2);
            this.panel1.Controls.Add(this.button1);
            this.panel1.Controls.Add(this.TextBox3);
            this.panel1.Controls.Add(this.label3);
            this.panel1.Controls.Add(this.label2);
            this.panel1.Controls.Add(this.TextBox4);
            this.panel1.Dock = System.Windows.Forms.DockStyle.Top;
            this.panel1.Location = new System.Drawing.Point(0, 25);
            this.panel1.Name = "panel1";
            this.panel1.Size = new System.Drawing.Size(994, 51);
            this.panel1.TabIndex = 8;
            // 
            // button2
            // 
            this.button2.Location = new System.Drawing.Point(895, 15);
            this.button2.Name = "button2";
            this.button2.Size = new System.Drawing.Size(87, 23);
            this.button2.TabIndex = 12;
            this.button2.Text = " Очистить";
            this.button2.UseVisualStyleBackColor = true;
            this.button2.Click += new System.EventHandler(this.button2_Click);
            // 
            // button1
            // 
            this.button1.Location = new System.Drawing.Point(12, 13);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(87, 23);
            this.button1.TabIndex = 11;
            this.button1.Text = "Нарисовать";
            this.button1.UseVisualStyleBackColor = true;
            this.button1.Click += new System.EventHandler(this.button1_Click);
            // 
            // TextBox1
            // 
            this.TextBox1.HidePromptOnLeave = true;
            this.TextBox1.InsertKeyMode = System.Windows.Forms.InsertKeyMode.Overwrite;
            this.TextBox1.Location = new System.Drawing.Point(158, 4);
            this.TextBox1.Mask = "000";
            this.TextBox1.Name = "TextBox1";
            this.TextBox1.PromptChar = ' ';
            this.TextBox1.ResetOnPrompt = false;
            this.TextBox1.ResetOnSpace = false;
            this.TextBox1.RightToLeft = System.Windows.Forms.RightToLeft.No;
            this.TextBox1.Size = new System.Drawing.Size(77, 20);
            this.TextBox1.TabIndex = 7;
            this.TextBox1.Text = "0";
            this.TextBox1.ValidatingType = typeof(int);
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.label4.Location = new System.Drawing.Point(121, 5);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(38, 16);
            this.label4.TabIndex = 10;
            this.label4.Text = "    X1 ";
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.label5.Location = new System.Drawing.Point(259, 5);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(36, 16);
            this.label5.TabIndex = 9;
            this.label5.Text = "    Y1";
            // 
            // TextBox2
            // 
            this.TextBox2.HidePromptOnLeave = true;
            this.TextBox2.InsertKeyMode = System.Windows.Forms.InsertKeyMode.Overwrite;
            this.TextBox2.Location = new System.Drawing.Point(295, 4);
            this.TextBox2.Mask = "000";
            this.TextBox2.Name = "TextBox2";
            this.TextBox2.PromptChar = ' ';
            this.TextBox2.ResetOnPrompt = false;
            this.TextBox2.ResetOnSpace = false;
            this.TextBox2.RightToLeft = System.Windows.Forms.RightToLeft.No;
            this.TextBox2.Size = new System.Drawing.Size(77, 20);
            this.TextBox2.TabIndex = 8;
            this.TextBox2.Text = "0";
            this.TextBox2.ValidatingType = typeof(int);
            // 
            // CheckBox1
            // 
            this.CheckBox1.AutoSize = true;
            this.CheckBox1.Location = new System.Drawing.Point(398, 6);
            this.CheckBox1.Name = "CheckBox1";
            this.CheckBox1.Size = new System.Drawing.Size(98, 17);
            this.CheckBox1.TabIndex = 13;
            this.CheckBox1.Text = "Пучок прямых";
            this.CheckBox1.UseVisualStyleBackColor = true;
            this.CheckBox1.CheckedChanged += new System.EventHandler(this.CheckBox1_CheckedChanged);
            // 
            // button3
            // 
            this.button3.Location = new System.Drawing.Point(895, 11);
            this.button3.Name = "button3";
            this.button3.Size = new System.Drawing.Size(87, 23);
            this.button3.TabIndex = 13;
            this.button3.Text = "Сохранить";
            this.button3.UseVisualStyleBackColor = true;
            this.button3.Click += new System.EventHandler(this.button3_Click_1);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(994, 540);
            this.Controls.Add(this.button3);
            this.Controls.Add(this.CheckBox1);
            this.Controls.Add(this.TextBox1);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.panel1);
            this.Controls.Add(this.label5);
            this.Controls.Add(this.pictureBox1);
            this.Controls.Add(this.TextBox2);
            this.Controls.Add(this.toolStrip1);
            this.ForeColor = System.Drawing.Color.Black;
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog;
            this.Location = new System.Drawing.Point(450, 120);
            this.MaximizeBox = false;
            this.MinimizeBox = false;
            this.Name = "Form1";
            this.ShowIcon = false;
            this.StartPosition = System.Windows.Forms.FormStartPosition.Manual;
            this.Text = "Лабораторная работа №1";
            this.toolStrip1.ResumeLayout(false);
            this.toolStrip1.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).EndInit();
            this.panel1.ResumeLayout(false);
            this.panel1.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.ToolStrip toolStrip1;
        private System.Windows.Forms.ToolStripDropDownButton DownButton1;
        private System.Windows.Forms.ToolStripMenuItem простойАлгоритмToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem Item1;
        private System.Windows.Forms.ToolStripMenuItem Item2;
        private System.Windows.Forms.ToolStripMenuItem алгоритмыБрезенхемаToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem четырехИВосьмисвязнойРToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem Item3;
        private System.Windows.Forms.ToolStripMenuItem Item4;
        private System.Windows.Forms.ToolStripMenuItem Item5;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator1;
        private System.Windows.Forms.ToolStripDropDownButton DownButton2;
        private System.Windows.Forms.ToolStripMenuItem черныйItem;
        private System.Windows.Forms.ToolStripMenuItem красныйItem;
        private System.Windows.Forms.ToolStripMenuItem синийItem;
        private System.Windows.Forms.ToolStripMenuItem желтыйItem;
        private System.Windows.Forms.ToolStripMenuItem зеленыйItem;
        private System.Windows.Forms.MaskedTextBox TextBox3;
        private System.Windows.Forms.MaskedTextBox TextBox4;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.ToolStripMenuItem выходToolStripMenuItem;
        private System.Windows.Forms.PictureBox pictureBox1;
        private System.Windows.Forms.Panel panel1;
        private System.Windows.Forms.MaskedTextBox TextBox1;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.MaskedTextBox TextBox2;
        private System.Windows.Forms.Button button1;
        private System.Windows.Forms.Button button2;
        private System.Windows.Forms.CheckBox CheckBox1;
        private System.Windows.Forms.ToolStripMenuItem анимацияToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem Item6;
        private System.Windows.Forms.ToolStripMenuItem Item7;
        private System.Windows.Forms.SaveFileDialog saveFileDialog1;
        private System.Windows.Forms.Button button3;
    }
}

