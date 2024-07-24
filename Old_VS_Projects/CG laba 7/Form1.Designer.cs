
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
            this.pictureBox1 = new System.Windows.Forms.PictureBox();
            this.saveFileDialog1 = new System.Windows.Forms.SaveFileDialog();
            this.button2 = new System.Windows.Forms.Button();
            this.button3 = new System.Windows.Forms.Button();
            this.panel1 = new System.Windows.Forms.Panel();
            this.button1 = new System.Windows.Forms.Button();
            this.TextBox3 = new System.Windows.Forms.MaskedTextBox();
            this.label3 = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            this.TextBox4 = new System.Windows.Forms.MaskedTextBox();
            this.TextBox1 = new System.Windows.Forms.MaskedTextBox();
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.TextBox2 = new System.Windows.Forms.MaskedTextBox();
            this.toolStrip1 = new System.Windows.Forms.ToolStrip();
            this.DownButton1 = new System.Windows.Forms.ToolStripDropDownButton();
            this.Item1 = new System.Windows.Forms.ToolStripMenuItem();
            this.алгоритмыБрезенхемаToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.Item2 = new System.Windows.Forms.ToolStripMenuItem();
            this.Item3 = new System.Windows.Forms.ToolStripMenuItem();
            this.Item4 = new System.Windows.Forms.ToolStripMenuItem();
            this.Item6 = new System.Windows.Forms.ToolStripMenuItem();
            this.анимацияToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.Item7 = new System.Windows.Forms.ToolStripMenuItem();
            this.Item8 = new System.Windows.Forms.ToolStripMenuItem();
            this.Item9 = new System.Windows.Forms.ToolStripMenuItem();
            this.Item10 = new System.Windows.Forms.ToolStripMenuItem();
            this.Item11 = new System.Windows.Forms.ToolStripMenuItem();
            this.Item12 = new System.Windows.Forms.ToolStripMenuItem();
            this.Item5 = new System.Windows.Forms.ToolStripMenuItem();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).BeginInit();
            this.panel1.SuspendLayout();
            this.toolStrip1.SuspendLayout();
            this.SuspendLayout();
            // 
            // pictureBox1
            // 
            this.pictureBox1.BackColor = System.Drawing.Color.White;
            this.pictureBox1.Dock = System.Windows.Forms.DockStyle.Bottom;
            this.pictureBox1.Location = new System.Drawing.Point(0, 61);
            this.pictureBox1.Name = "pictureBox1";
            this.pictureBox1.Size = new System.Drawing.Size(1005, 490);
            this.pictureBox1.TabIndex = 7;
            this.pictureBox1.TabStop = false;
            // 
            // button2
            // 
            this.button2.Location = new System.Drawing.Point(895, 3);
            this.button2.Name = "button2";
            this.button2.Size = new System.Drawing.Size(87, 23);
            this.button2.TabIndex = 12;
            this.button2.Text = " Очистить";
            this.button2.UseVisualStyleBackColor = true;
            this.button2.Click += new System.EventHandler(this.button2_Click);
            // 
            // button3
            // 
            this.button3.Location = new System.Drawing.Point(895, 32);
            this.button3.Name = "button3";
            this.button3.Size = new System.Drawing.Size(87, 23);
            this.button3.TabIndex = 13;
            this.button3.Text = "Сохранить";
            this.button3.UseVisualStyleBackColor = true;
            this.button3.Click += new System.EventHandler(this.button3_Click_1);
            // 
            // panel1
            // 
            this.panel1.Controls.Add(this.button1);
            this.panel1.Controls.Add(this.button2);
            this.panel1.Controls.Add(this.TextBox3);
            this.panel1.Controls.Add(this.label3);
            this.panel1.Controls.Add(this.label4);
            this.panel1.Controls.Add(this.TextBox4);
            this.panel1.Controls.Add(this.TextBox1);
            this.panel1.Controls.Add(this.label1);
            this.panel1.Controls.Add(this.label2);
            this.panel1.Controls.Add(this.TextBox2);
            this.panel1.Controls.Add(this.toolStrip1);
            this.panel1.Controls.Add(this.button3);
            this.panel1.Dock = System.Windows.Forms.DockStyle.Top;
            this.panel1.Location = new System.Drawing.Point(0, 0);
            this.panel1.Name = "panel1";
            this.panel1.Size = new System.Drawing.Size(1005, 62);
            this.panel1.TabIndex = 8;
            // 
            // button1
            // 
            this.button1.Location = new System.Drawing.Point(12, 29);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(87, 23);
            this.button1.TabIndex = 23;
            this.button1.Text = "Применить";
            this.button1.UseVisualStyleBackColor = true;
            this.button1.Click += new System.EventHandler(this.button1_Click);
            // 
            // TextBox3
            // 
            this.TextBox3.HidePromptOnLeave = true;
            this.TextBox3.InsertKeyMode = System.Windows.Forms.InsertKeyMode.Overwrite;
            this.TextBox3.Location = new System.Drawing.Point(528, 28);
            this.TextBox3.Mask = "#000";
            this.TextBox3.Name = "TextBox3";
            this.TextBox3.PromptChar = ' ';
            this.TextBox3.ResetOnPrompt = false;
            this.TextBox3.ResetOnSpace = false;
            this.TextBox3.RightToLeft = System.Windows.Forms.RightToLeft.No;
            this.TextBox3.Size = new System.Drawing.Size(77, 20);
            this.TextBox3.TabIndex = 19;
            this.TextBox3.Text = "0";
            this.TextBox3.ValidatingType = typeof(int);
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.label3.Location = new System.Drawing.Point(484, 30);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(38, 16);
            this.label3.TabIndex = 22;
            this.label3.Text = "    X2 ";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.label4.Location = new System.Drawing.Point(624, 30);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(36, 16);
            this.label4.TabIndex = 21;
            this.label4.Text = "    Y2";
            // 
            // TextBox4
            // 
            this.TextBox4.HidePromptOnLeave = true;
            this.TextBox4.InsertKeyMode = System.Windows.Forms.InsertKeyMode.Overwrite;
            this.TextBox4.Location = new System.Drawing.Point(666, 29);
            this.TextBox4.Mask = "#000";
            this.TextBox4.Name = "TextBox4";
            this.TextBox4.PromptChar = ' ';
            this.TextBox4.ResetOnPrompt = false;
            this.TextBox4.ResetOnSpace = false;
            this.TextBox4.RightToLeft = System.Windows.Forms.RightToLeft.No;
            this.TextBox4.Size = new System.Drawing.Size(77, 20);
            this.TextBox4.TabIndex = 20;
            this.TextBox4.Text = "0";
            this.TextBox4.ValidatingType = typeof(int);
            // 
            // TextBox1
            // 
            this.TextBox1.HidePromptOnLeave = true;
            this.TextBox1.InsertKeyMode = System.Windows.Forms.InsertKeyMode.Overwrite;
            this.TextBox1.Location = new System.Drawing.Point(265, 28);
            this.TextBox1.Mask = "#000";
            this.TextBox1.Name = "TextBox1";
            this.TextBox1.PromptChar = ' ';
            this.TextBox1.ResetOnPrompt = false;
            this.TextBox1.ResetOnSpace = false;
            this.TextBox1.RightToLeft = System.Windows.Forms.RightToLeft.No;
            this.TextBox1.Size = new System.Drawing.Size(77, 20);
            this.TextBox1.TabIndex = 15;
            this.TextBox1.Text = "0";
            this.TextBox1.ValidatingType = typeof(int);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.label1.Location = new System.Drawing.Point(221, 30);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(38, 16);
            this.label1.TabIndex = 18;
            this.label1.Text = "    X2 ";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.label2.Location = new System.Drawing.Point(348, 30);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(36, 16);
            this.label2.TabIndex = 17;
            this.label2.Text = "    Y2";
            // 
            // TextBox2
            // 
            this.TextBox2.HidePromptOnLeave = true;
            this.TextBox2.InsertKeyMode = System.Windows.Forms.InsertKeyMode.Overwrite;
            this.TextBox2.Location = new System.Drawing.Point(390, 28);
            this.TextBox2.Mask = "#000";
            this.TextBox2.Name = "TextBox2";
            this.TextBox2.PromptChar = ' ';
            this.TextBox2.ResetOnPrompt = false;
            this.TextBox2.ResetOnSpace = false;
            this.TextBox2.RightToLeft = System.Windows.Forms.RightToLeft.No;
            this.TextBox2.Size = new System.Drawing.Size(77, 20);
            this.TextBox2.TabIndex = 16;
            this.TextBox2.Text = "0";
            this.TextBox2.ValidatingType = typeof(int);
            // 
            // toolStrip1
            // 
            this.toolStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.DownButton1});
            this.toolStrip1.Location = new System.Drawing.Point(0, 0);
            this.toolStrip1.Name = "toolStrip1";
            this.toolStrip1.Size = new System.Drawing.Size(1005, 25);
            this.toolStrip1.TabIndex = 14;
            this.toolStrip1.Text = "toolStrip1";
            // 
            // DownButton1
            // 
            this.DownButton1.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Text;
            this.DownButton1.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.Item1,
            this.алгоритмыБрезенхемаToolStripMenuItem,
            this.Item6,
            this.анимацияToolStripMenuItem,
            this.Item9,
            this.Item5,
            this.Item10});
            this.DownButton1.Image = ((System.Drawing.Image)(resources.GetObject("DownButton1.Image")));
            this.DownButton1.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.DownButton1.Name = "DownButton1";
            this.DownButton1.Size = new System.Drawing.Size(58, 22);
            this.DownButton1.Text = "Режим";
            // 
            // Item1
            // 
            this.Item1.Name = "Item1";
            this.Item1.Size = new System.Drawing.Size(180, 22);
            this.Item1.Text = "Смещение";
            this.Item1.Click += new System.EventHandler(this.Item1_Click);
            // 
            // алгоритмыБрезенхемаToolStripMenuItem
            // 
            this.алгоритмыБрезенхемаToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.Item2,
            this.Item3,
            this.Item4});
            this.алгоритмыБрезенхемаToolStripMenuItem.Name = "алгоритмыБрезенхемаToolStripMenuItem";
            this.алгоритмыБрезенхемаToolStripMenuItem.Size = new System.Drawing.Size(180, 22);
            this.алгоритмыБрезенхемаToolStripMenuItem.Text = "Отражение";
            // 
            // Item2
            // 
            this.Item2.Name = "Item2";
            this.Item2.Size = new System.Drawing.Size(172, 22);
            this.Item2.Text = "Относительно ОХ";
            this.Item2.Click += new System.EventHandler(this.Item2_Click);
            // 
            // Item3
            // 
            this.Item3.Name = "Item3";
            this.Item3.Size = new System.Drawing.Size(172, 22);
            this.Item3.Text = "Относительно ОY";
            this.Item3.Click += new System.EventHandler(this.Item3_Click);
            // 
            // Item4
            // 
            this.Item4.Name = "Item4";
            this.Item4.Size = new System.Drawing.Size(172, 22);
            this.Item4.Text = "Относительно OZ";
            this.Item4.Click += new System.EventHandler(this.Item4_Click);
            // 
            // Item6
            // 
            this.Item6.Name = "Item6";
            this.Item6.Size = new System.Drawing.Size(180, 22);
            this.Item6.Text = "Масштабирование";
            this.Item6.Click += new System.EventHandler(this.Item6_Click);
            // 
            // анимацияToolStripMenuItem
            // 
            this.анимацияToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.Item7,
            this.Item11,
            this.Item12,
            this.Item8});
            this.анимацияToolStripMenuItem.Name = "анимацияToolStripMenuItem";
            this.анимацияToolStripMenuItem.Size = new System.Drawing.Size(180, 22);
            this.анимацияToolStripMenuItem.Text = "Вращение";
            // 
            // Item7
            // 
            this.Item7.Name = "Item7";
            this.Item7.Size = new System.Drawing.Size(180, 22);
            this.Item7.Text = "Во круг оси OX";
            this.Item7.Click += new System.EventHandler(this.Item7_Click);
            // 
            // Item8
            // 
            this.Item8.Name = "Item8";
            this.Item8.Size = new System.Drawing.Size(180, 22);
            this.Item8.Text = "Во круг вершины";
            this.Item8.Click += new System.EventHandler(this.Item8_Click);
            // 
            // Item9
            // 
            this.Item9.Name = "Item9";
            this.Item9.Size = new System.Drawing.Size(180, 22);
            this.Item9.Text = "Сброс";
            this.Item9.Click += new System.EventHandler(this.Item9_Click);
            // 
            // Item10
            // 
            this.Item10.Name = "Item10";
            this.Item10.Size = new System.Drawing.Size(180, 22);
            this.Item10.Text = "Выход";
            this.Item10.Click += new System.EventHandler(this.Item10_Click);
            // 
            // Item11
            // 
            this.Item11.Name = "Item11";
            this.Item11.Size = new System.Drawing.Size(180, 22);
            this.Item11.Text = "Во круг оси OY";
            this.Item11.Click += new System.EventHandler(this.Item11_Click);
            // 
            // Item12
            // 
            this.Item12.Name = "Item12";
            this.Item12.Size = new System.Drawing.Size(180, 22);
            this.Item12.Text = "Во круг оси OZ";
            this.Item12.Click += new System.EventHandler(this.Item12_Click);
            // 
            // Item5
            // 
            this.Item5.Name = "Item5";
            this.Item5.Size = new System.Drawing.Size(180, 22);
            this.Item5.Text = "Анимация";
            this.Item5.Click += new System.EventHandler(this.Item5_Click);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(1005, 551);
            this.Controls.Add(this.panel1);
            this.Controls.Add(this.pictureBox1);
            this.ForeColor = System.Drawing.Color.Black;
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog;
            this.Location = new System.Drawing.Point(450, 120);
            this.MaximizeBox = false;
            this.MinimizeBox = false;
            this.Name = "Form1";
            this.ShowIcon = false;
            this.StartPosition = System.Windows.Forms.FormStartPosition.Manual;
            this.Text = "Лабораторная работа №7";
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).EndInit();
            this.panel1.ResumeLayout(false);
            this.panel1.PerformLayout();
            this.toolStrip1.ResumeLayout(false);
            this.toolStrip1.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion
        private System.Windows.Forms.PictureBox pictureBox1;
        private System.Windows.Forms.SaveFileDialog saveFileDialog1;
        private System.Windows.Forms.Button button2;
        private System.Windows.Forms.Button button3;
        private System.Windows.Forms.Panel panel1;
        private System.Windows.Forms.ToolStrip toolStrip1;
        private System.Windows.Forms.ToolStripDropDownButton DownButton1;
        private System.Windows.Forms.ToolStripMenuItem Item1;
        private System.Windows.Forms.ToolStripMenuItem алгоритмыБрезенхемаToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem Item2;
        private System.Windows.Forms.ToolStripMenuItem Item3;
        private System.Windows.Forms.ToolStripMenuItem Item4;
        private System.Windows.Forms.ToolStripMenuItem Item6;
        private System.Windows.Forms.ToolStripMenuItem анимацияToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem Item7;
        private System.Windows.Forms.ToolStripMenuItem Item8;
        private System.Windows.Forms.ToolStripMenuItem Item9;
        private System.Windows.Forms.ToolStripMenuItem Item10;
        private System.Windows.Forms.MaskedTextBox TextBox1;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.MaskedTextBox TextBox2;
        private System.Windows.Forms.MaskedTextBox TextBox3;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.MaskedTextBox TextBox4;
        private System.Windows.Forms.Button button1;
        private System.Windows.Forms.ToolStripMenuItem Item11;
        private System.Windows.Forms.ToolStripMenuItem Item12;
        private System.Windows.Forms.ToolStripMenuItem Item5;
    }
}

