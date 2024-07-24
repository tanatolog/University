using System;
using System.Collections.Generic;
using System.Drawing;
using System.Drawing.Imaging;
using System.Runtime.InteropServices;
using System.Windows.Forms;
using System.Threading.Tasks;

namespace CGlaba1
{
    public partial class Form1 : Form
    {
        private readonly Bitmap pic;
        readonly Graphics graph;
        readonly TXYZ[] V = new TXYZ[8];
        readonly TXYZ[] A = new TXYZ[8];
        readonly TXYZ[] b = new TXYZ[8];
        readonly Tcrd[] crd = new Tcrd[8];
        readonly TXYZ[] Axis = new TXYZ[4];
        double q = 40, w = 20, kI = 0, kII = 0, kIII = 0;
        long O1 = 500, O2 = 300;
        Color color;
        int xI = 0, yI = 0, zI = 0, ang = 0;

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

        void Strbrez8(long x1, long y1, long x2, long y2, Color C)
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
                if ((x < 1000) && (y < 485) && (x >= 0) && (y >= 0)) { pic.SetPixel((int)x, (int)y, C); }
                while (eact >= 0)
                {
                    if (f) { x += s1; }
                    else { y += s2; }
                    eact -= 2 * dx;
                }
                if (f) { y += s2; }
                else { x += s1; }
                eact += 2 * dy;
                if ((x < 1000) && (y < 485) && (x >= 0) && (y >= 0)) { pic.SetPixel((int)x, (int)y, C); }
            }
        }

        void Purify()
        {
            graph.Clear(Color.Black);
            pictureBox1.Image = pic;
        }

        public Form1()
        {
            InitializeComponent();
            pic = new Bitmap(1005, 490);
            graph = Graphics.FromImage(pic);
            saveFileDialog1.DefaultExt = "png";
            Purify();
            V[0].x = 0; V[0].y = 150; V[0].z = 0;
            V[1].x = 0; V[1].y = 0; V[1].z = 0;
            V[2].x = 100; V[2].y = 0; V[2].z = 0;
            V[3].x = 100; V[3].y = 150; V[3].z = 0;
            V[4].x = 100; V[4].y = 150; V[4].z = 100;
            V[5].x = 100; V[5].y = 0; V[5].z = 100;
            V[6].x = 0; V[6].y = 0; V[6].z = 100;
            V[7].x = 0; V[7].y = 150; V[7].z = 100;

            A[0].x = 0; A[0].y = 150; A[0].z = 0;
            A[1].x = 0; A[1].y = 0; A[1].z = 0;
            A[2].x = 100; A[2].y = 0; A[2].z = 0;
            A[3].x = 100; A[3].y = 150; A[3].z = 0;
            A[4].x = 100; A[4].y = 150; A[4].z = 100;
            A[5].x = 100; A[5].y = 0; A[5].z = 100;
            A[6].x = 0; A[6].y = 0; A[6].z = 100;
            A[7].x = 0; A[7].y = 150; A[7].z = 100;

            Axis[0].x = 0; Axis[0].y = 0; Axis[0].z = 0;
            Axis[1].x = 1000; Axis[1].y = 0; Axis[1].z = 0;
            Axis[2].x = 0; Axis[2].y = -1000; Axis[2].z = 0;
            Axis[3].x = 0; Axis[3].y = 0; Axis[3].z = -1000;

            DrawAxis(O1, O2, q, w);
            Reset();
        }

        void DrawAxis(long x, long y, double p1, double f1)
        {
            color = Color.Red;
            double p = p1 * Math.PI / 180;
            double f = f1 * Math.PI / 180;
            for (int i = 0; i <= 3; i++)
            {
                A[i].x = Math.Round(Axis[i].x * Math.Cos(p) + Axis[i].z * Math.Sin(p));
                A[i].y = Math.Round(Axis[i].x * Math.Sin(p) * Math.Sin(f) + Axis[i].y * Math.Cos(f) - Axis[i].z * Math.Sin(f) * Math.Cos(p));
            }
            Strbrez8((long)(x + A[0].x), (long)(y + A[0].y), (long)(x + A[1].x), (long)(y + A[1].y), color);
            Strbrez8((long)(x + A[0].x), (long)(y + A[0].y), (long)(x + A[2].x), (long)(y + A[2].y), color);
            Strbrez8((long)(x + A[0].x), (long)(y + A[0].y), (long)(x + A[3].x), (long)(y + A[3].y), color);
        }

        void Draw(long x, long y)
        {
            DrawAxis(x, y, q, w);
            color = Color.Aqua;
            for (int i = 0; i <= 6; i++)
            {
                Strbrez8(x + crd[i].x, y + crd[i].y, x + crd[i + 1].x, y + crd[i + 1].y, color);
                // MessageBox.Show(Convert.ToString(x + crd[i].x) + " " + Convert.ToString(y + crd[i].y) + " " + Convert.ToString(x + crd[i + 1].x) + " " + Convert.ToString(y + crd[i + 1].y));
            }
            Strbrez8(x + crd[0].x, y + crd[0].y, x + crd[3].x, y + crd[3].y, color);
            //   MessageBox.Show(Convert.ToString(x + crd[0].x) + " " + Convert.ToString(y + crd[0].y) + " " + Convert.ToString(x + crd[3].x) + " " + Convert.ToString(y + crd[3].y));
            Strbrez8(x + crd[0].x, y + crd[0].y, x + crd[7].x, y + crd[7].y, color);
            //   MessageBox.Show(Convert.ToString(x + crd[0].x) + " " + Convert.ToString(y + crd[0].y) + " " + Convert.ToString(x + crd[7].x) + " " + Convert.ToString(y + crd[7].y));
            Strbrez8(x + crd[1].x, y + crd[1].y, x + crd[6].x, y + crd[6].y, color);
            //   MessageBox.Show(Convert.ToString(x + crd[1].x) + " " + Convert.ToString(y + crd[1].y) + " " + Convert.ToString(x + crd[6].x) + " " + Convert.ToString(y + crd[6].y));
            Strbrez8(x + crd[2].x, y + crd[2].y, x + crd[5].x, y + crd[5].y, color);
            //    MessageBox.Show(Convert.ToString(x + crd[2].x) + " " + Convert.ToString(y + crd[2].y) + " " + Convert.ToString(x + crd[5].x) + " " + Convert.ToString(y + crd[5].y));
            Strbrez8(x + crd[4].x, y + crd[4].y, x + crd[7].x, y + crd[7].y, color);
            //   MessageBox.Show(Convert.ToString(x + crd[4].x) + " " + Convert.ToString(y + crd[4].y) + " " + Convert.ToString(x + crd[7].x) + " " + Convert.ToString(y + crd[7].y));
            pictureBox1.Image = pic;
        }

        void Axonometric(double p1, double f1)
        {
            Purify();
            double p = p1 * Math.PI / 180;
            double f = f1 * Math.PI / 180;
            for (int i = 0; i <= 7; i++)
            {
                crd[i].x = (long)(V[i].x * Math.Cos(p) + V[i].z * Math.Sin(p));
                crd[i].y = (long)(V[i].x * Math.Sin(p) * Math.Sin(f) + V[i].y * Math.Cos(f) - V[i].z * Math.Sin(f) * Math.Cos(p));
            }
            Draw(O1, O2);
        }

        private void Item10_Click(object sender, EventArgs e)
        {
            Application.Exit();
        }

        private void button3_Click_1(object sender, EventArgs e)
        {
            if (saveFileDialog1.ShowDialog() == DialogResult.OK)
            {
                if (saveFileDialog1.FileName != "") { pic.Save(saveFileDialog1.FileName); }
            }
        }

        private void button2_Click(object sender, EventArgs e)
        {
            Purify();
        }

        private void Item1_Click(object sender, EventArgs e)
        {
            Checker(Item1);
            Varible(1);
        }

        private void Item2_Click(object sender, EventArgs e)
        {
            Checker(Item2);
            Varible(0);
        }

        private void Item3_Click(object sender, EventArgs e)
        {
            Checker(Item3);
            Varible(0);
        }

        private void Item4_Click(object sender, EventArgs e)
        {
            Checker(Item4);
            Varible(0);
        }

        private void Item6_Click(object sender, EventArgs e)
        {
            Checker(Item6);
            Varible(2);
        }

        private void Item7_Click(object sender, EventArgs e)
        {
            Checker(Item7);
            Varible(4);
        }

        private void Item8_Click(object sender, EventArgs e)
        {
            Checker(Item8);
            Varible(3);
        }

        private void Item9_Click(object sender, EventArgs e)
        {
            Checker(Item9);
            Varible(0);
        }

        private void Item11_Click(object sender, EventArgs e)
        {
            Checker(Item11);
            Varible(4);
        }

        private void Item12_Click(object sender, EventArgs e)
        {
            Checker(Item12);
            Varible(4);
        }

        private void Item5_Click(object sender, EventArgs e)
        {
            Checker(Item5);
            Varible(0);
        }

        public void Checker(ToolStripMenuItem Mitem)
        {
            Item1.Checked = false;
            Item2.Checked = false;
            Item3.Checked = false;
            Item4.Checked = false;
            Item6.Checked = false;
            Item7.Checked = false;
            Item8.Checked = false;
            Item9.Checked = false;
            Item11.Checked = false;
            Item12.Checked = false;
            Item5.Checked = false;
            Mitem.Checked = true;
        }

        public void Varible(int mod)
        {
            if (mod == 4)
            {
                TextBox4.Visible = false;
                TextBox3.Visible = false;
                TextBox2.Visible = true;
                TextBox1.Visible = false;
                label4.Visible = false;
                label3.Visible = false;
                label2.Visible = true;
                label1.Visible = false;
                label2.Text = "    r ";
                TextBox2.Mask = "#000";
            }
            if (mod == 3)
            {
                TextBox4.Visible = false;
                TextBox3.Visible = false;
                TextBox2.Visible = true;
                TextBox1.Visible = true;
                label4.Visible = false;
                label3.Visible = false;
                label2.Visible = true;
                label1.Visible = true;
                label1.Text = "    n ";
                label2.Text = "    r ";
                TextBox1.Mask = "#000";
                TextBox2.Mask = "#000";
            }
            if (mod == 2)
            {
                TextBox4.Visible = false;
                TextBox3.Visible = true;
                TextBox2.Visible = true;
                TextBox1.Visible = true;
                label4.Visible = false;
                label3.Visible = true;
                label2.Visible = true;
                label1.Visible = true;
                label1.Text = "   k1 ";
                label2.Text = "   k2 ";
                label3.Text = "   k3 ";
                TextBox1.Mask = "0.00";
                TextBox2.Mask = "0.00";
                TextBox3.Mask = "0.00";
            }
            if (mod == 1)
            {
                TextBox4.Visible = false;
                label4.Visible = false;
                TextBox3.Visible = true;
                TextBox2.Visible = true;
                TextBox1.Visible = true;
                label3.Visible = true;
                label2.Visible = true;
                label1.Visible = true;
                label1.Text = "    X ";
                label2.Text = "    Y ";
                label3.Text = "    Z ";
                TextBox1.Mask = "#000";
                TextBox2.Mask = "#000";
                TextBox3.Mask = "#000";
            }
            if (mod == 0)
            {
                TextBox3.Visible = false;
                TextBox4.Visible = false;
                label3.Visible = false;
                label4.Visible = false;
                TextBox2.Visible = false;
                TextBox1.Visible = false;
                label2.Visible = false;
                label1.Visible = false;
            }
        }

        void Move(int m, int n, int l)
        {
            for (int i = 0; i <= 7; i++) {
                V[i].x = V[i].x + m;
                V[i].y = V[i].y + n;
                V[i].z = V[i].z + l;
            }
            Axonometric(q, w);
        }

        void Symmetry(int m, int n, int l)
        {
            for (int i = 0; i <= 7; i++)
            {
                V[i].x = V[i].x *m;
                V[i].y = V[i].y *n;
                V[i].z = V[i].z *l;
            }
            Axonometric(q, w);
        }

        void Scaling(double k1, double k2, double k3, TXYZ p)
        {
            double m = p.x;
            double n = p.y;
            double l = p.z;
            for (int i = 0; i <= 7; i++)
            {
                V[i].x = (long)Math.Round(k1 * V[i].x - m * k1 + m);
                V[i].y = (long)Math.Round(k2 * V[i].y - n * k2 + n);
                V[i].z = (long)Math.Round(k3 * V[i].z - l * k3 + l);
            }
            Axonometric(q, w);
        }

        void Rotation(double n1, double n2, double n3, int angle)
        {
            // MessageBox.Show(Convert.ToString(n1) + " " + Convert.ToString(n2) + " " + Convert.ToString(n3) + " " + Convert.ToString(angle));
            for (int i = 0; i <= 7; i++) {
                b[i].x = V[i].x;
                b[i].y = V[i].y;
                b[i].z = V[i].z;
            }
            double r = angle * Math.PI / 180;
            for (int i = 0; i <= 7; i++)
            {
                V[i].x = Math.Round(
                    b[i].x * (n1 * n1 + (1 - n1 * n1) * Math.Cos(r)) +
                    b[i].y * (n1 * n2 * (1 - Math.Cos(r)) - n3 * Math.Sin(r)) +
                    b[i].z * (n1 * n3 * (1 - Math.Cos(r)) + n2 * Math.Sin(r))
                );
                V[i].y = Math.Round(
                    b[i].x * (n1 * n2 * (1 - Math.Cos(r)) + n3 * Math.Sin(r)) +
                    b[i].y * (n2 * n2 + (1 - n2 * n2) * Math.Cos(r)) +
                    b[i].z * (n2 * n3 * (1 - Math.Cos(r)) - n1 * Math.Sin(r))
                );
                V[i].z = Math.Round(
                    b[i].x * (n1 * n3 * (1 - Math.Cos(r)) - n2 * Math.Sin(r)) +
                    b[i].y * (n2 * n3 * (1 - Math.Cos(r)) + n1 * Math.Sin(r)) +
                    b[i].z * (n3 * n3 + (1 - n3 * n3) * Math.Cos(r))

                );
            }
            Axonometric(q, w);
        }

        void RotationDiagonal(int n, int angle)
        {
            if (n == 1) { n = 4; }
            Rotation(V[n].x / Math.Sqrt((V[n].x * V[n].x) + (V[n].y * V[n].y) + (V[n].z * V[n].z)),
               V[n].y / Math.Sqrt((V[n].x * V[n].x) + (V[n].y * V[n].y) + (V[n].z * V[n].z)),
               V[n].z / Math.Sqrt((V[n].x * V[n].x) + (V[n].y * V[n].y) + (V[n].z * V[n].z)),
               angle);
        }

        void RotationX(int angle)
        {
            for (int i = 0; i <= 7; i++)
            {
                b[i].x = V[i].x;
                b[i].y = V[i].y;
                b[i].z = V[i].z;
            }
            double r = angle * Math.PI / 180;
            for (int i = 0; i <= 7; i++)
            {
                V[i].y = Math.Round(b[i].y * Math.Cos(r) - b[i].z * Math.Sin(r));
                V[i].z = Math.Round(b[i].y * Math.Sin(r) + b[i].z * Math.Cos(r));
            }
            Axonometric(q, w);
        }

        void RotationY(int angle)
        {
            for (int i = 0; i <= 7; i++)
            {
                b[i].x = V[i].x;
                b[i].y = V[i].y;
                b[i].z = V[i].z;
            }
            double r = angle * Math.PI / 180;
            for (int i = 0; i <= 7; i++)
            {
                V[i].x = Math.Round(b[i].x * Math.Cos(r) + b[i].z * Math.Sin(r));
                V[i].z = Math.Round(-b[i].x * Math.Sin(r) + b[i].z * Math.Cos(r));
            }
            Axonometric(q, w);
        }

        void RotationZ(int angle)
        {
            for (int i = 0; i <= 7; i++)
            {
                b[i].x = V[i].x;
                b[i].y = V[i].y;
                b[i].z = V[i].z;
            }
            double r = angle * Math.PI / 180;
            for (int i = 0; i <= 7; i++)
            {
                V[i].x = Math.Round(b[i].x * Math.Cos(r) - b[i].y * Math.Sin(r));
                V[i].y = Math.Round(b[i].x * Math.Sin(r) + b[i].y * Math.Cos(r));
            }
            Axonometric(q, w);
        }

        void Reset()
        {
            for (int i = 0; i <= 7; i++)
            {
                V[0].x = 0; V[0].y = 150; V[0].z = 0;
                V[1].x = 0; V[1].y = 0; V[1].z = 0;
                V[2].x = 100; V[2].y = 0; V[2].z = 0;
                V[3].x = 100; V[3].y = 150; V[3].z = 0;
                V[4].x = 100; V[4].y = 150; V[4].z = 100;
                V[5].x = 100; V[5].y = 0; V[5].z = 100;
                V[6].x = 0; V[6].y = 0; V[6].z = 100;
                V[7].x = 0; V[7].y = 150; V[7].z = 100;
            }
            Axonometric(q, w);
        }

        async private void button1_Click(object sender, EventArgs e)
        {
            if (Item1.Checked)
            {
                if (int.TryParse(TextBox1.Text, out xI) == false) { xI = 0; }
                if (int.TryParse(TextBox2.Text, out yI) == false) { yI = 0; }
                if (int.TryParse(TextBox3.Text, out zI) == false) { zI = 0; }
            }
            if (Item6.Checked)
            {
                if (double.TryParse(TextBox1.Text, out kI) == false) { kI = 0; }
                if (double.TryParse(TextBox2.Text, out kII) == false) { kII = 0; }
                if (double.TryParse(TextBox3.Text, out kIII) == false) { kIII = 0; }
            }
            if (Item8.Checked)
            {
                if (int.TryParse(TextBox1.Text, out xI) == false) { xI = 0; }
                if (int.TryParse(TextBox2.Text, out ang) == false) { ang = 0; }
            }
            if (Item7.Checked)
            {
                if (int.TryParse(TextBox2.Text, out ang) == false) { ang = 0; }
            }

            if (Item1.Checked) { Move(xI, yI, zI); }                     // смещение
            if (Item2.Checked) { Symmetry(-1, 1, 1); }                   // отражение ОХ
            if (Item3.Checked) { Symmetry(1, -1, 1); }                   // отражение ОY
            if (Item4.Checked) { Symmetry(1, 1, -1); }                   // отражение ОZ
            if (Item6.Checked) { Scaling(kI, kII, kIII, V[0]); }         // масштабирование
            if (Item7.Checked) { RotationX(ang); }                       // вращение ось
            if (Item8.Checked) { RotationDiagonal(xI, ang); }    
            if (Item9.Checked) { Reset(); }
            if (Item11.Checked) { RotationY(ang); }
            if (Item12.Checked) { RotationZ(ang); ; }
            if (Item5.Checked) {
                int T = 0;
                while (T <= 180) {
                    T += 1;
                    RotationDiagonal(0, T);
                    RotationDiagonal(4, T);
                    Scaling(1.01, 1.01, 1.01, V[0]);
                    await Task.Delay(10);
                }
                T = 0;
                while (T <= 180)
                {
                    T += 1;
                    RotationDiagonal(0, T);
                    RotationDiagonal(4, T);
                    Scaling(0.99, 0.99, 0.99, V[0]);
                    await Task.Delay(10);
                }
                Reset();
            }
        }

    }

}

