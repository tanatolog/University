using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

internal delegate void Func();
internal delegate void Star(Func a);

namespace CGlaba1           
{
    public partial class Form1 : Form
    {
        private readonly Bitmap pic, pixel, square, whitesquare;
        readonly Graphics graph;

        public Form1()
        {
            InitializeComponent();
            pixel = new Bitmap(1, 1);
            whitesquare = new Bitmap(10, 10);
            square = new Bitmap(10, 10);
            pic = new Bitmap(1000, 450);
            graph = Graphics.FromImage(pic);
            pixel.SetPixel(0, 0, Color.Black);
            for (int i = 0; i <= 9; i ++)
            {
                for (int j = 0; j <= 9; j ++) 
                {
                    if ((i + j) % 2 == 0) 
                    { 
                        square.SetPixel(i, j, Color.Black);
                        whitesquare.SetPixel(i, j, Color.White);
                    }
                }
            }
            saveFileDialog1.DefaultExt = "png";
        }

        private void ВыходToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Application.Exit();
        }

        public void Checker (ToolStripMenuItem Mitem)
        {
            CheckBox1.Checked = false;
            Item1.Checked = false;
            Item2.Checked = false;
            Item3.Checked = false;
            Item4.Checked = false;
            Item5.Checked = false;
            Item6.Checked = false;
            Item7.Checked = false;
            Mitem.Checked = true;
        }

        public void ActStar(bool b)
        {
            CheckBox1.Visible = b;
            CheckBox1.Enabled = b;
        }

        public void RadiusMode(bool b)
        {
            if (b) { label3.Text = "    R"; }
            else { label3.Text = "    X2"; }
            label2.Visible = !b;
            TextBox4.Visible = !b;
            TextBox4.Enabled = !b;
        }

        private void Item1_Click(object sender, EventArgs e) 
        {
            Checker(Item1);
            ActStar(true);
            RadiusMode(false);
        }

        private void Item2_Click(object sender, EventArgs e) 
        { 
            Checker(Item2);
            ActStar(false);
            RadiusMode(true);

        }

        private void Item3_Click(object sender, EventArgs e) 
        { 
            Checker(Item3);
            ActStar(true);
            RadiusMode(false);
        }

        private void Item4_Click(object sender, EventArgs e) 
        { 
            Checker(Item4);
            ActStar(true);
            RadiusMode(false);
        }

        private void Item5_Click(object sender, EventArgs e) 
        { 
            Checker(Item5);
            ActStar(false);
            RadiusMode(true);
        }

        private void Item6_Click(object sender, EventArgs e)
        {
            Checker(Item6);
            ActStar(false);
            RadiusMode(true);
        }

        private void Item7_Click(object sender, EventArgs e)
        {
            Checker(Item7);
            ActStar(false);
            RadiusMode(false);
        }

        private void button2_Click(object sender, EventArgs e)
        {
            graph.Clear(Color.White);
            pictureBox1.Image = pic;
        }

        private void CheckBox1_CheckedChanged(object sender, EventArgs e)
        {
            if (CheckBox1.Checked)
            {
                RadiusMode(true);
            }
            else
            {
                RadiusMode(false);
            }
        }

        public void ColorCheck(ToolStripMenuItem Mitem)
        {
            черныйItem.Checked = false;
            красныйItem.Checked = false;
            синийItem.Checked = false;
            желтыйItem.Checked = false;
            зеленыйItem.Checked = false;
            Mitem.Checked = true;
        }

        private void черныйToolStripMenuItem_Click(object sender, EventArgs e)
        {
            pixel.SetPixel(0, 0, Color.Black);
            DownButton2.BackColor = Color.Black;
            ColorCheck(черныйItem);
        }

        private void красныйToolStripMenuItem_Click(object sender, EventArgs e)
        {
            pixel.SetPixel(0, 0, Color.Red);
            DownButton2.BackColor = Color.Red;
            ColorCheck(красныйItem);
        }

        private void синийToolStripMenuItem_Click(object sender, EventArgs e)
        {
            pixel.SetPixel(0, 0, Color.Blue);
            DownButton2.BackColor = Color.Blue;
            ColorCheck(синийItem);
        }

        private void желтыйToolStripMenuItem_Click(object sender, EventArgs e)
        {
            pixel.SetPixel(0, 0, Color.Yellow);
            DownButton2.BackColor = Color.Yellow;
            ColorCheck(желтыйItem);
        }

        private void button3_Click_1(object sender, EventArgs e)
        {
            if (saveFileDialog1.ShowDialog() == DialogResult.OK)
            {
                if (saveFileDialog1.FileName != "") { pic.Save(saveFileDialog1.FileName); }
            }
        }

        async private void button3_Click(object sender, EventArgs e)
        {
            float x = 500;
            float y = 200;
            float r = 100;
            float dn = 1 / r;
            float n = 0;
            while (n < 4 * Math.PI)
            {
                int x1 = (int)Math.Round(x + r * Math.Cos(n));
                int y1 = (int)Math.Round(y + r * Math.Sin(n));
                graph.DrawImageUnscaled(square, x1, y1);
                pictureBox1.Image = pic;
                await Task.Delay(10);
                graph.DrawImageUnscaled(whitesquare, x1, y1);
                pictureBox1.Image = pic;
                n = n + dn;
            }
        }

        private void зеленыйToolStripMenuItem_Click(object sender, EventArgs e)
        {
            pixel.SetPixel(0, 0, Color.Green);
            DownButton2.BackColor = Color.Green;
            ColorCheck(зеленыйItem);
        }

        private void button1_Click(object sender, EventArgs e)
        {
            short R = 0;
            if (Int16.TryParse(TextBox1.Text, out short x1) == false) { x1 = 0; }
            if (Int16.TryParse(TextBox2.Text, out short y1) == false) { y1 = 0; }
            if (Int16.TryParse(TextBox3.Text, out short x2) == false) { x2 = 0; }
            if (Int16.TryParse(TextBox4.Text, out short y2) == false) { y1 = 0; }
            if (CheckBox1.Checked || Item2.Checked || Item5.Checked || Item6.Checked)
            {
                if (Int16.TryParse(TextBox3.Text, out R) == false) { R = 0; }
            }
            if ((y1 > 450) || (y2 > 450) || (R > 225))
            {
                MessageBox.Show("Координата х не может превышать 999, у не может превышать 450, R не может превышать 225");
                return;
            }

            void stright()           // //MessageBox.Show(Convert.ToString(y)); <-----------------------
            {
                if (x1 != x2)
                {
                    float y;
                    float m = (float)(y2 - y1) / (x2 - x1);
                    if (x1 < x2)
                    {
                        y = y1;
                        for (int x = x1; x <= x2; x++)
                        {
                            graph.DrawImageUnscaled(pixel, x, Convert.ToInt32(y));
                            y += m;
                        }
                    }
                    else if (x1 > x2)
                    {
                        y = y2;
                        for (int x = x2; x <= x1; x++)
                        {
                            graph.DrawImageUnscaled(pixel, x, (int)Math.Round(y));
                           y += m;
                        }
                    }
                }
                else if (y1 == y2)
                {
                    graph.DrawImageUnscaled(pixel, x1, y1);
                }
                else
                {
                    for (int y = Math.Min(y1, y2); y <= Math.Max(y1, y2); y++)
                    {
                        graph.DrawImageUnscaled(pixel, x1, y);
                    }
                }
            }

            sbyte sign(int a)
            {
                if (a >= 0) { return 1; }
                else { return -1; }
            }

            void strbrez8()
            {
                short x, y, dx, dy, s1, s2, act;
                bool f;
                x = x1;
                y = y1;
                dx = (short)Math.Abs(x2 - x1);
                dy = (short)Math.Abs(y2 - y1);
                s1 = sign(x2 - x1);
                s2 = sign(y2 - y1);
                if (dy > dx)
                {
                    act = dx;
                    dx = dy;
                    dy = act;
                    f = true;
                }
                else { f = false; }
                int eact = 2 * dy - dx;
                for (int i = 1; i <= dx; i++)
                {
                    graph.DrawImageUnscaled(pixel, x, y);
                    while (eact >= 0)
                    {
                        if (f) { x += s1; }
                        else { y += s2; }
                        eact -= 2 * dx;
                    }
                    if (f) { y += s2; }
                    else { x += s1; }
                    eact += 2 * dy;
                    graph.DrawImageUnscaled(pixel, x, y);
                }
            }

            void strbrez4()                       // <------------------------
            {
                short x, y, dx, dy, s1, s2, act;
                bool f;
                x = x1;
                y = y1;
                dx = (short)Math.Abs(x2 - x1);
                dy = (short)Math.Abs(y2 - y1);
                s1 = sign(x2 - x1);
                s2 = sign(y2 - y1);
                if (dy >= dx)
                {
                    act = dx;
                    dx = dy;
                    dy = act;
                    f = true;
                }
                else { f = false; }
                int eact = 2 * dy - dx;
                for (int i = 1; i <= dx + dy; i++)
                {
                    graph.DrawImageUnscaled(pixel, x, y);
                    if (eact < 0)
                    {
                        if (f) { y += s2; }
                        else { x += s1; }
                        eact += 2 * dy;
                    }
                    else
                    {
                        if (f) { x += s1; }
                        else { y += s2; }
                        eact -= 2 * dx;
                    }
                }
                graph.DrawImageUnscaled(pixel, x, y);
            }

            void drawstar(Func alg)
            {
                double step = 3.141592653589793 / 12;
                for (int i = 1; i <= 24; i++)
                {
                    double angle = i * step;
                    double x = Math.Cos(angle) * R + x1;
                    double y = Math.Sin(angle) * R + y1;
                    x2 = (short)Math.Round(x);
                    y2 = (short)Math.Round(y);
                    alg();
                    pictureBox1.Image = pic;
                }
            }

            void Warmode(Func alg, Star star)
            {
                if (CheckBox1.Checked) { star(alg); }
                else { alg(); }
            }

            void Circle()
            {
                for (int i = 0; i <= R; i++)
                {
                    float j = (float)Math.Sqrt(R * R - i * i);
                    int xI = i + x1;
                    float yI = j + y1;
                    int xII = - i + x1;
                    float yII = - j + y1;
                    int xIII = i + x1;
                    float yIII = -j + y1;
                    int xIV = - i + x1;
                    float yIV = j + y1;
                    graph.DrawImageUnscaled(pixel, xI, (int)Math.Round(yI));
                    graph.DrawImageUnscaled(pixel, xII, (int)Math.Round(yII));
                    graph.DrawImageUnscaled(pixel, xIII, (int)Math.Round(yIII));
                    graph.DrawImageUnscaled(pixel, xIV, (int)Math.Round(yIV));
                }
            }

            void Circlebrez()
            {
                int x = 0;
                int y = R;
                int ee = (3 - 2 * R);
                while (x < y)
                {
                    graph.DrawImageUnscaled(pixel, x1 + x, y1 + y);
                    graph.DrawImageUnscaled(pixel, x1 + y, y1 + x);
                    graph.DrawImageUnscaled(pixel, x1 + y, y1 - x);
                    graph.DrawImageUnscaled(pixel, x1 + x, y1 - y);
                    graph.DrawImageUnscaled(pixel, x1 - x, y1 - y);
                    graph.DrawImageUnscaled(pixel, x1 - y, y1 - x);
                    graph.DrawImageUnscaled(pixel, x1 - y, y1 + x);
                    graph.DrawImageUnscaled(pixel, x1 - x, y1 + y);
                    if (ee < 0) { ee = ee + 4 * x + 6; }
                    else
                    {
                        ee = ee + 4 * (x - y) + 10;
                        y = y - 1;
                    }
                    x = x + 1;
                }
                if (x == y)
                {
                    graph.DrawImageUnscaled(pixel, x1 + x, y1 + y);
                    graph.DrawImageUnscaled(pixel, x1 + y, y1 + x);
                    graph.DrawImageUnscaled(pixel, x1 + y, y1 - x);
                    graph.DrawImageUnscaled(pixel, x1 + x, y1 - y);
                    graph.DrawImageUnscaled(pixel, x1 - x, y1 - y);
                    graph.DrawImageUnscaled(pixel, x1 - y, y1 - x);
                    graph.DrawImageUnscaled(pixel, x1 - y, y1 + x);
                    graph.DrawImageUnscaled(pixel, x1 - x, y1 + y);
                }
            }

            async void Anicircle()
            {
                float dn = (1 / (float)R);
                float n = 0;
                while (n < Math.PI)
                {
                    int x = (int)Math.Round(x1 + R * Math.Cos(n));
                    int y = (int)Math.Round(y1 + R * Math.Sin(n));
                    graph.DrawImageUnscaled(square, x, y);
                    pictureBox1.Image = pic;
                    await Task.Delay(10);
                    graph.DrawImageUnscaled(whitesquare, x, y);
                    pictureBox1.Image = pic;
                    n = n + dn;
                }
            }

            async void Anistright()
            {
                short x, y, dx, dy, s1, s2, act;
                bool f;
                x = x1;
                y = y1;
                dx = (short)Math.Abs(x2 - x1);
                dy = (short)Math.Abs(y2 - y1);
                s1 = sign(x2 - x1);
                s2 = sign(y2 - y1);
                if (dy > dx)
                {
                    act = dx;
                    dx = dy;
                    dy = act;
                    f = true;
                }
                else { f = false; }
                int eact = 2 * dy - dx;
                for (int i = 1; i <= dx; i++)
                {
                    graph.DrawImageUnscaled(square, x, y);
                    pictureBox1.Image = pic;
                    await Task.Delay(10);
                    graph.DrawImageUnscaled(whitesquare, x, y);
                    pictureBox1.Image = pic;
                    while (eact >= 0)
                    {
                        if (f) { x += s1; }
                        else { y += s2; }
                        eact -= 2 * dx;
                    }
                    if (f) { y += s2; }
                    else { x += s1; }
                    eact += 2 * dy;
                    graph.DrawImageUnscaled(square, x, y);
                    pictureBox1.Image = pic;
                    await Task.Delay(10);
                    graph.DrawImageUnscaled(whitesquare, x, y);
                    pictureBox1.Image = pic;
                }
            }

            if (Item1.Checked) { Warmode(stright, drawstar); }           // прям
            else if (Item2.Checked) { Circle(); }                        // круг
            else if (Item3.Checked) { Warmode(strbrez4, drawstar); }     // 4 Брез
            else if (Item4.Checked) { Warmode(strbrez8, drawstar); }     // 8 Брез
            else if (Item5.Checked) { Circlebrez(); }                    // Брез круг
            else if (Item6.Checked) { Anicircle(); }                     // анимация круг
            else if (Item7.Checked) { Anistright(); }                                  // анимация прямая

            pictureBox1.Image = pic;
        }

    }

}

