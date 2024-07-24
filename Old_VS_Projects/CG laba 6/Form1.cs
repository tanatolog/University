using System;
using System.Drawing;
using System.Windows.Forms;

namespace CGlaba1
{
    public partial class Form1 : Form
    {
        private readonly Bitmap pic;
        readonly Graphics graph;
        readonly TXYZ[] V = new TXYZ[8];
        readonly Tcrd[] crd = new Tcrd[8];

        void Strbrez8(long x1, long y1, long x2, long y2)
        {

            sbyte sign(long par)
            {
                if (par >= 0) { return 1; }
                else { return -1; }
            }
            long x, y, dx, dy, s1, s2, act;
            bool f;
            x = x1;
            y = y1;
            dx = Math.Abs(x2 - x1);
            dy = Math.Abs(y2 - y1);
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
            long eact = 2 * dy - dx;
            for (int i = 1; i <= dx; i++)
            {
                pic.SetPixel((int)x, (int)y, Color.Blue);
                while (eact >= 0)
                {
                    if (f) { x += s1; }
                    else { y += s2; }
                    eact -= 2 * dx;
                }
                if (f) { y += s2; }
                else { x += s1; }
                eact += 2 * dy;
                pic.SetPixel((int)x, (int)y, Color.Blue);
            }
        }

        void Purify()
        {
            graph.Clear(Color.White);
            pictureBox1.Image = pic;
        }

        struct TXYZ
        {
            public double x;
            public double y;
            public double z;
        };

        struct Tcrd
        {
            public long x;
            public long y;
        };

        public Form1()
        {
            InitializeComponent();
            pic = new Bitmap(1005, 468);
            graph = Graphics.FromImage(pic);
            saveFileDialog1.DefaultExt = "png";
            Purify(); 
            V[0].x = -100; V[0].y = 50;  V[0].z = -35;
            V[1].x = -100; V[1].y = -50; V[1].z = -35;
            V[2].x = 100;  V[2].y = -50; V[2].z = -35;
            V[3].x = 100;  V[3].y = 50;  V[3].z = -35;
            V[4].x = 100;  V[4].y = 50;  V[4].z = 35;
            V[5].x = 100;  V[5].y = -50; V[5].z = 35;
            V[6].x = -100; V[6].y = -50; V[6].z = 35;
            V[7].x = -100; V[7].y = 50;  V[7].z = 35;
        }

        void Draw(int x, int y)
        {
            for (int i = 0; i <= 6; i++) { 
                Strbrez8(x + crd[i].x, y + crd[i].y, x + crd[i+1].x, y + crd[i+1].y);
               // MessageBox.Show(Convert.ToString(x + crd[i].x) + " " + Convert.ToString(y + crd[i].y) + " " + Convert.ToString(x + crd[i + 1].x) + " " + Convert.ToString(y + crd[i + 1].y));
            }
            Strbrez8(x + crd[0].x, y + crd[0].y, x + crd[3].x, y + crd[3].y);
         //   MessageBox.Show(Convert.ToString(x + crd[0].x) + " " + Convert.ToString(y + crd[0].y) + " " + Convert.ToString(x + crd[3].x) + " " + Convert.ToString(y + crd[3].y));
            Strbrez8(x + crd[0].x, y + crd[0].y, x + crd[7].x, y + crd[7].y);
         //   MessageBox.Show(Convert.ToString(x + crd[0].x) + " " + Convert.ToString(y + crd[0].y) + " " + Convert.ToString(x + crd[7].x) + " " + Convert.ToString(y + crd[7].y));
            Strbrez8(x + crd[1].x, y + crd[1].y, x + crd[6].x, y + crd[6].y);
         //   MessageBox.Show(Convert.ToString(x + crd[1].x) + " " + Convert.ToString(y + crd[1].y) + " " + Convert.ToString(x + crd[6].x) + " " + Convert.ToString(y + crd[6].y));
            Strbrez8(x + crd[2].x, y + crd[2].y, x + crd[5].x, y + crd[5].y);
        //    MessageBox.Show(Convert.ToString(x + crd[2].x) + " " + Convert.ToString(y + crd[2].y) + " " + Convert.ToString(x + crd[5].x) + " " + Convert.ToString(y + crd[5].y));
            Strbrez8(x + crd[4].x, y + crd[4].y, x + crd[7].x, y + crd[7].y);
         //   MessageBox.Show(Convert.ToString(x + crd[4].x) + " " + Convert.ToString(y + crd[4].y) + " " + Convert.ToString(x + crd[7].x) + " " + Convert.ToString(y + crd[7].y));
            pictureBox1.Image = pic;
        }

        void Axonometric(double p1, double f1)
        {
            double p = p1 * Math.PI / 180;
            double f = f1 * Math.PI / 180;
            for (int i = 0; i <= 7; i++)
            {
                crd[i].x = (long)Math.Round(V[i].x * Math.Cos(p) + V[i].z * Math.Sin(p));
                crd[i].y = (long)Math.Round(V[i].x * Math.Sin(p) * Math.Sin(f) +V[i].y * Math.Cos(f) - V[i].z * Math.Sin(f) * Math.Cos(p));
            }
            Draw(500, 200);
        }

        void ObliqueParallelAxonometry(double l)
        {
            for (int i = 0; i <= 7; i++)
            {
                crd[i].x = (long)Math.Round(V[i].x + V[i].z * l * Math.Cos(Math.PI / 4));
                crd[i].y = (long)Math.Round(V[i].y + V[i].z * l * Math.Sin(Math.PI / 4));
            }
            Draw(500, 200);
        }

        private void button2_Click(object sender, EventArgs e)
        {
            Purify();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            Purify();
            for (int i = 0; i <= 7; i++) {
                crd[i].x = (long)Math.Round(V[i].x);
                crd[i].y = (long)Math.Round(V[i].y);
            }
            Draw(500, 200);
        }

        private void button4_Click(object sender, EventArgs e)
        {
            Purify();
            for (int i = 0; i <= 7; i++)
            {
                crd[i].x = (long)Math.Round(V[i].x);
                crd[i].y = (long)Math.Round(V[i].z);
            }
            Draw(500, 200);
        }

        private void button5_Click(object sender, EventArgs e)
        {
            Purify();
            for (int i = 0; i <= 7; i++)
            {
                crd[i].x = (long)Math.Round(V[i].z);
                crd[i].y = (long)Math.Round(V[i].y);
            }
            Draw(500, 200);
        }

        private void button7_Click(object sender, EventArgs e)
        {
            Purify();
            Axonometric(45, 35.264);
        }

        private void button6_Click(object sender, EventArgs e)
        {
            Purify();
            Axonometric(22.208, 20.705);
        }

        private void button8_Click(object sender, EventArgs e)
        {
            Purify();
            Axonometric(150, 70);
        }

        private void button10_Click(object sender, EventArgs e)
        {
            Purify();
            ObliqueParallelAxonometry(1);
        }

        private void button9_Click(object sender, EventArgs e)
        {
            Purify();
            ObliqueParallelAxonometry(0.5);
        }

        private void button11_Click(object sender, EventArgs e)
        {
            Purify();
            for (int i = 0; i <= 7; i++) {
                crd[i].x = (long)Math.Round(V[i].x / (V[i].z / 150 + 1));
                crd[i].y = (long)Math.Round(V[i].y / (V[i].z / 150 + 1));
            }
            Draw(500, 200);
        }

        private void button3_Click_1(object sender, EventArgs e)
        {
            if (saveFileDialog1.ShowDialog() == DialogResult.OK)
            {
                if (saveFileDialog1.FileName != "") { pic.Save(saveFileDialog1.FileName); }
            }
        }

    }

}

