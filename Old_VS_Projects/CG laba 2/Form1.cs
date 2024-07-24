using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace CG_laba_2
{
    public partial class Form1 : Form
    {
        private readonly Bitmap pic, pixel, square, whitesquare;
        readonly Graphics graph;
        short x1, y1, x2, y2, x3, y3, x4, y4, x5, y5;
        bool flag = false;

        public Form1()
        {
            InitializeComponent();
            whitesquare = new Bitmap(10, 10);
            square = new Bitmap(10, 10);
            pic = new Bitmap(1000, 450);
            graph = Graphics.FromImage(pic);
            for (int i = 0; i <= 9; i++)
            {
                for (int j = 0; j <= 9; j++)
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

        void fill()
        {
            if (Int16.TryParse(BoxX1.Text, out x1) == false) { x1 = 0; }
            if (Int16.TryParse(BoxY1.Text, out y1) == false) { y1 = 0; }
            if (Int16.TryParse(BoxX2.Text, out x2) == false) { x2 = 0; }
            if (Int16.TryParse(BoxY2.Text, out y2) == false) { y2 = 0; }
            if (Int16.TryParse(BoxX3.Text, out x3) == false) { x3 = 0; }
            if (Int16.TryParse(BoxY3.Text, out y3) == false) { y3 = 0; }
            if (Int16.TryParse(BoxX4.Text, out x4) == false) { x4 = 0; }
            if (Int16.TryParse(BoxY4.Text, out y4) == false) { y4 = 0; }
            if (Int16.TryParse(BoxX5.Text, out x5) == false) { x5 = 0; }
            if (Int16.TryParse(BoxY5.Text, out y5) == false) { y5 = 0; }
            if ((y1 > 450) || (y2 > 450) || (y3 > 450) || (y4 > 450) || (y5 > 450))
            {
                MessageBox.Show("Координата х не может превышать 1000, у не может превышать 450");
                flag = true;
            }
            else { flag = false; }
        }

        private void button4_Click(object sender, EventArgs e)
        {
            Point[] P = new Point[5];
            Point[] R = new Point[5];
            Pen pip = new Pen(Color.Black);
            Pen pop = new Pen(Color.Red);
            int m = 5;

            sbyte sign(int a)
            {
                if (a >= 0) { return 1; }
                else { return -1; }
            }

            async void Anistright(int x1, int y1, int x2, int y2)
            {
                int x, y, dx, dy, s1, s2, act;
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

            async void bezier()
            {
                int xn = P[0].X;
                int yn = P[0].Y;
                int n = 0;
                double t = 0;
                double step = 0.01;
                Point[] result = new Point[101];
                do
                {
                    R = P;
                    for (int j = m; j >= 2; j--)
                    {
                        for (int i = 1; i <= (j - 1); i++)
                        {
                            R[i - 1].X = R[i - 1].X + (int)Math.Round(t * (R[i].X - R[i - 1].X));
                            R[i - 1].Y = R[i - 1].Y + (int)Math.Round(t * (R[i].Y - R[i - 1].Y));
                        }

                    }
                    graph.DrawLine(pop, xn, yn, R[0].X, R[0].Y);
                    result[n] = new Point(R[0].X, R[0].Y);
                    n++;
                    pictureBox1.Image = pic;
                    t = t + step;
                    xn = R[0].X;
                    yn = R[0].Y;
                } while (t <= 1);
                for (int i = 1; i <= result.Length; i++) 
                { 
                    Anistright(result[i - 1].X, result[i - 1].Y, result[i + 1].X, result[i + 1].Y); 
                    await Task.Delay(700);
                }
            }
            fill();
            if (flag) { return; }
            P[0].X = x1;
            P[0].Y = y1;
            P[1].X = x2;
            P[1].Y = y2;
            P[2].X = x3;
            P[2].Y = y3;
            P[3].X = x4;
            P[3].Y = y4;
            P[4].X = x5;
            P[4].Y = y5;
            bezier();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            Point[] P = new Point[5];
            Point[] R = new Point[5];
            Pen pip = new Pen(Color.Black);
            Pen pop = new Pen(Color.Red);
            int m = 5;

            async void bezier() 
            {
                int xn = P[0].X;
                int yn = P[0].Y;
                double t = 0;
                double step = 0.01;
                do
                {
                    R = P;
                    for (int j = m; j >= 2; j--)
                    {
                        for (int i = 1; i <= (j - 1); i++)
                        {
                            R[i - 1].X = R[i - 1].X + (int)Math.Round(t * (R[i].X - R[i - 1].X));
                            R[i - 1].Y = R[i - 1].Y + (int)Math.Round(t * (R[i].Y - R[i - 1].Y));
                            if (checkBox1.Checked) { graph.DrawLine(pip, xn, yn, R[i - 1].X, R[i - 1].Y); }
                            await Task.Delay(10);
                        }

                    }
                    graph.DrawLine(pop, xn, yn, R[0].X, R[0].Y);
                    await Task.Delay(10);
                    pictureBox1.Image = pic;
                    t = t + step;
                    xn = R[0].X;
                    yn = R[0].Y;
                } while (t <= 1);
            }

            fill();
            if (flag) { return; }
            P[0].X = x1;
            P[0].Y = y1;
            P[1].X = x2;
            P[1].Y = y2;
            P[2].X = x3;
            P[2].Y = y3;
            P[3].X = x4;
            P[3].Y = y4;
            P[4].X = x5;
            P[4].Y = y5;
            if (checkBox1.Checked) { graph.DrawLines(pip, P); }
            bezier();
        }

        private void button2_Click(object sender, EventArgs e)
        {
            graph.Clear(Color.White);
            pictureBox1.Image = pic;
        }

        private void button3_Click(object sender, EventArgs e)
        {
            if (saveFileDialog1.ShowDialog() == DialogResult.OK)
            {
                if (saveFileDialog1.FileName != "") { pic.Save(saveFileDialog1.FileName); }
            }
        }
    }
}
