using System;
using System.Collections.Generic;
using System.Drawing;
using System.Drawing.Imaging;
using System.Linq;
using System.Runtime.InteropServices;
using System.Windows.Forms;

namespace CGlaba1           
{
    public partial class Form1 : Form
    {
        private readonly Bitmap pic, pixel;
        readonly Graphics graph;
        int X1, Y1;
        Color black = Color.FromArgb(255, 1, 1, 1);
        Color red = Color.FromArgb(255, 255, 1, 1);

        void strbrez8(int x1, int y1, int x2, int y2)
        {

            sbyte sign(int par)
            {
                if (par >= 0) { return 1; }
                else { return -1; }
            }

            int x, y, dx, dy, s1, s2, act;
            bool f;
            x = x1;
            y = y1;
            dx = (int)Math.Abs(x2 - x1);
            dy = (int)Math.Abs(y2 - y1);
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
                if ((x < 994) && (y < 479) && (x >= 0) && (y >= 0)) { pic.SetPixel(x, y, black); }
                while (eact >= 0)
                {
                    if (f) { x += s1; }
                    else { y += s2; }
                    eact -= 2 * dx;
                }
                if (f) { y += s2; }
                else { x += s1; }
                eact += 2 * dy;
                if ((x < 994) && (y < 479) && (x >= 0) && (y >= 0)) { pic.SetPixel(x, y, black); }
            }
        }

        async void Fill(Bitmap bitmap, int x, int y, Color color)
        {
             BitmapData data = bitmap.LockBits(new Rectangle(0, 0, bitmap.Width, bitmap.Height), ImageLockMode.ReadWrite, PixelFormat.Format32bppRgb);
             int[] bits = new int[data.Stride / 4 * data.Height];
             Marshal.Copy(data.Scan0, bits, 0, bits.Length);
             LinkedList<Point> CheckPoint = new LinkedList<Point>();
             int FillTo = color.ToArgb();
             int FillFrom = bits[x + y * data.Stride / 4];
             bits[x + y * data.Stride / 4] = FillTo;
             if (FillFrom != FillTo)
             {
                 CheckPoint.AddLast(new Point(x, y));
                 while (CheckPoint.Count > 0)
                 {
                     Point current = CheckPoint.First.Value;
                     CheckPoint.RemoveFirst();
                     foreach (Point off in new Point[] { new Point(0, -1), new Point(0, 1), new Point(-1, 0), new Point(1, 0) })
                     {
                         Point next = new Point(current.X + off.X, current.Y + off.Y);
                         if (next.X >= 0 && next.Y >= 0 && next.X < data.Width && next.Y < data.Height)
                             if (bits[next.X + next.Y * data.Stride / 4] == FillFrom)
                             {
                                 CheckPoint.AddLast(next);
                                 bits[next.X + next.Y * data.Stride / 4] = FillTo;
                             }
                     }
                 }
             }
             Marshal.Copy(bits, 0, data.Scan0, bits.Length);
             bitmap.UnlockBits(data);
         }  

        public Form1()
        {
            int xI, xII, yI, yII;
            InitializeComponent();
            pic = new Bitmap(994, 479);
            graph = Graphics.FromImage(pic);
            saveFileDialog1.DefaultExt = "png";
            graph.Clear(Color.White);
            pictureBox1.Image = pic;
            xI = 100;
            yI = 50;
            xII = 400;
            yII = 200;
            strbrez8(xI, yI, xI, yII);
            strbrez8(xI, yI, xII, yI);
            strbrez8(xII, yII, xI, yII);
            strbrez8(xII, yII, xII, yI);
            strbrez8(xII, yII, xI, yI);
            strbrez8(xI, yII, xII, yI);
        }

        Stack<int> stackX = new Stack<int>();
        Stack<int> stackY = new Stack<int>();

        void drawBrush(int x0, int y0, Color ci, Color cb)
        {
            int x, y, xw, xb, xr, xl, j;
            bool fl;
            stackX.Push(x0);
            stackY.Push(y0);
            while (stackX.Count != 0)
            {
                x = stackX.Pop();
                y = stackY.Pop();
                pic.SetPixel(x, y, ci);
                xw = x;
                x = x + 1;
                while (pic.GetPixel(x, y).Equals(cb) == false)
                {
                    pic.SetPixel(x, y, ci);
                    x = x + 1;
                }
                xr = x - 1;
                //x = xw - 1;
                x = xw;
                x = x - 1;
                while (pic.GetPixel(x, y).Equals(cb) == false)
                {
                    pic.SetPixel(x, y, ci);
                    x = x - 1;
                }
                xl = x + 1;
                j = -1;
                //for (j = -1; j <= 2; j++)
                do
                {
                    x = xl;
                    y = y + j;
                    while (x <= xr)
                    {
                        fl = false;
                        while ((pic.GetPixel(x, y).Equals(cb) == false) && (pic.GetPixel(x, y).Equals(ci) == false) && (x < xr))
                        {
                            x += 1;
                            if (!fl)
                            {
                                fl = true;
                            }
                        }
                        if (fl)
                        {
                            if ((x == xr) && (pic.GetPixel(x, y).Equals(cb) == false) && (pic.GetPixel(x, y).Equals(ci) == false))
                            {
                                stackX.Push(x);
                                stackY.Push(y);
                            }
                            else
                            {
                                stackX.Push(x - 1);
                                stackY.Push(y);
                            }
                            fl = false;
                        }
                        xb = x;
                        while ((pic.GetPixel(x, y).Equals(cb) == true) || (pic.GetPixel(x, y).Equals(ci) == true) && (x < xr))
                        {
                            x += 1;
                        }
                        if (x == xb) { x += 1; }
                    }
                    j = j + 3;
                } while (j <= 2);
            }
        }

        private void ВыходToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Application.Exit();
        }

        private void button2_Click(object sender, EventArgs e)
        {
            graph.Clear(Color.White);
            pictureBox1.Image = pic;
        }

        private void pictureBox1_MouseDown(object sender, MouseEventArgs e)
        {
            X1 = e.X;
            Y1 = e.Y;
        }

        private void pictureBox1_MouseClick(object sender, MouseEventArgs e)
        {
            if (e.Button == MouseButtons.Right)
            {
                //drawBrush(110, 60, Color.Red, Color.Black);
                drawBrush(e.X, e.Y, red, black);
                //Fill(pic, e.X, e.Y, Color.Red);
            }
            pictureBox1.Invalidate();
        }

        private void pictureBox1_MouseMove(object sender, MouseEventArgs e)
        {
            if (e.Button == MouseButtons.Left) {
                strbrez8(e.X, e.Y, X1, Y1);
                X1 = e.X;
                Y1 = e.Y;
            }
            pictureBox1.Invalidate();
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

