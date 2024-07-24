using System;
using System.Collections.Generic;
using System.Drawing;
using System.Drawing.Imaging;
using System.Runtime.InteropServices;
using System.Windows.Forms;

namespace CGlaba1           
{
    public partial class Form1 : Form
    {
        private readonly Bitmap pic, pixel;
        readonly Graphics graph;
        long xr = 800, xl = 200, ya = 50, yb = 350, xI = 0, xII = 0, yI = 0, yII = 0;


        void strbrez8(long x1, long y1, long x2, long y2)
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
                if ((x < 994) && (y < 479) && (x >= 0) && (y >= 0)) { pic.SetPixel((int)x, (int)y, Color.Black); }
                while (eact >= 0)
                {
                    if (f) { x += s1; }
                    else { y += s2; }
                    eact -= 2 * dx;
                }
                if (f) { y += s2; }
                else { x += s1; }
                eact += 2 * dy;
                if ((x < 994) && (y < 479) && (x >= 0) && (y >= 0)) { pic.SetPixel((int)x, (int)y, Color.Black); }
            }
        }

        public Form1()
        {
            InitializeComponent();
            pic = new Bitmap(994, 479);
            graph = Graphics.FromImage(pic);
            saveFileDialog1.DefaultExt = "png";
            graph.Clear(Color.White);
            pictureBox1.Image = pic;
            strbrez8(xl, ya, xl, yb);
            strbrez8(xl, ya, xr, ya);
            strbrez8(xr, yb, xl, yb);
            strbrez8(xr, yb, xr, ya);
        }

        private void button2_Click(object sender, EventArgs e)
        {
            graph.Clear(Color.White);
            pictureBox1.Image = pic;
            strbrez8(xl, ya, xl, yb);
            strbrez8(xl, ya, xr, ya);
            strbrez8(xr, yb, xl, yb);
            strbrez8(xr, yb, xr, ya);
        }

        void SazerlandKoen(long x1, long y1, long x2, long y2)
        {
            long kod(long x, long y)
            {
                long kp = 0;
                if (x < xl) kp = kp + 1;
                if (y < ya) kp = kp + 2;
                if (x > xr) kp = kp + 4;
                if (y > yb) kp = kp + 8;
                return kp;
            }

            while (true) {
                long p1 = kod(x1, y1);
                long p2 = kod(x2, y2);
                if (((p1 == p2) && (p1 != 0)) || ((p1 == 3) && (p2 == 1)) || ((p1 == 1) && (p2 == 9)) || ((p1 == 9) && (p2 == 1)) || ((p1 == 1) && (p2 == 3))
                    || ((p1 == 6) && (p2 == 4)) || ((p1 == 4) && (p2 == 6)) || ((p1 == 4) && (p2 == 12)) || ((p1 == 12) && (p2 == 4))) { break; }
                if ((p1 == p2) && (p1 == 0)) {
                    strbrez8(x1, y1, x2, y2);
                    break; 
                }
                if (p1 == 0) {
                    (x1, x2) = (x2, x1);
                    (y1, y2) = (y2, y1);
                    p1 = p2;
                }
                if ((p1 == 3) || (p1 == 1) || (p1 == 9)) {
                    y1 = y1 + (y2 - y1) * (xl - x1) / (x2 - x1);
                    x1 = xl;
                }
                if ((p1 == 3) || (p1 == 2) || (p1 == 6))
                {
                    x1 = x1 + (x2 - x1) * (ya - y1) / (y2 - y1);
                    y1 = ya;
                }
                if ((p1 == 6) || (p1 == 4) || (p1 == 12))
                {
                    y1 = y1 + (y2 - y1) * (xr - x1) / (x2 - x1);
                    x1 = xr;
                }
                if ((p1 == 9) || (p1 == 8) || (p1 == 12))
                {
                    x1 = x1 + (x2 - x1) * (yb - y1) / (y2 - y1);
                    y1 = yb;
                }
            }
        }

        private void pictureBox1_MouseClick(object sender, MouseEventArgs e)
        {
            if (e.Button == MouseButtons.Left)
            {
                if ((xI == 0) || (yI == 0))
                {
                    xI = e.X;
                    yI = e.Y;
                }
                else if ((xII == 0) || (yII == 0)) {
                    xII = e.X;
                    yII = e.Y;
                    SazerlandKoen(xI, yI, xII, yII);
                    xI = 0;
                    xII = 0;
                    yI = 0;
                    yII = 0;
                }
                pictureBox1.Invalidate();
            }
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

