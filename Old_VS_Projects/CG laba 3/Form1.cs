using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

internal delegate Point Func(int o1, int o2);

namespace CGlaba1           
{
    public partial class Form1 : Form
    {
        private readonly Bitmap pic, pixel;
        readonly Graphics graph;
        int xI, xII, yI, yII;
        int a = 0, b = 0, g = 0, r = 0;
        float kx = 0, ky = 0;

        Point offset(int x, int y)
        {
            Point poopa = new Point(0, 0);
            x += a;
            y += b;
            poopa.X = x;
            poopa.Y = y;
            return poopa;
        }

        Point reflexOX(int x, int y)
        {
            Point poopa = new Point(0, 0);
            y -= 225;
            y = -y;
            y += 225;
            poopa.X = x;
            poopa.Y = y;
            return poopa;
        }

        Point reflexOY(int x, int y)
        {
            Point poopa = new Point(0, 0);
            x -= 500;
            x = -x;
            x += 500;
            poopa.X = x;
            poopa.Y = y;
            return poopa;
        }

        Point scale(int x, int y)
        {
            Point poopa = new Point(0, 0);
            x -= 500;
            y -= 225;
            x = (int)Math.Round((float)(x * kx - a * kx + a));
            y = (int)Math.Round((float)(y * ky - b * ky + b));
            x += 500;
            y += 225;
            poopa.X = x;
            poopa.Y = y;
            return poopa;
        }

        Point left(int x, int y)
        {
            Point poopa = new Point(0, 0);
            x -= 500;
            y -= 225;
            int ab = x;
            int ba = y;
            x = (int)Math.Round((float)(ab * Math.Cos((r * Math.PI) / 180) - ba * Math.Sin((r * Math.PI) / 180) + 500 - a * Math.Cos((r * Math.PI) / 180) + a + b * Math.Sin((r * Math.PI) / 180)));
            y = (int)Math.Round((float)(ab * Math.Sin((r * Math.PI) / 180) + ba * Math.Cos((r * Math.PI) / 180) + 225 - a * Math.Sin((r * Math.PI) / 180) - b * Math.Cos((r * Math.PI) / 180) + b));
            poopa.X = x;
            poopa.Y = y;
            return poopa;
        }

        Point right(int x, int y)
        {
            Point poopa = new Point(0, 0);
            x -= 500;
            y -= 225;
            int ab = x;
            int ba = y;
            x = (int)Math.Round((float)(ab * Math.Cos((r * Math.PI) / 180) + ba * Math.Sin((r * Math.PI) / 180) + 500 - a * Math.Cos((r * Math.PI) / 180) + a + b * Math.Sin((r * Math.PI) / 180)));
            y = (int)Math.Round((float)(-ab * Math.Sin((r * Math.PI) / 180) + ba * Math.Cos((r * Math.PI) / 180) + 225 - a * Math.Sin((r * Math.PI) / 180) - b * Math.Cos((r * Math.PI) / 180) + b));
            poopa.X = x;
            poopa.Y = y;
            return poopa;
        }

        void strbrez8(int x1, int y1, int x2, int y2, Func move)
        {

            sbyte sign(int par)
            {
                if (par >= 0) { return 1; }
                else { return -1; }
            }
            int x, y, dx, dy, s1, s2, act, did1 = 0, did2 = 0;
            bool f;
            Point aboba = new Point(0, 0);
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
                aboba = move(x, y);
                did1 = aboba.X;
                did2 = aboba.Y;
                graph.DrawImageUnscaled(pixel, did1, did2);
                while (eact >= 0)
                {
                    if (f) { x += s1; }
                    else { y += s2; }
                    eact -= 2 * dx;
                }
                if (f) { y += s2; }
                else { x += s1; }
                eact += 2 * dy;
                aboba = move(x, y);
                did1 = aboba.X;
                did2 = aboba.Y;
                graph.DrawImageUnscaled(pixel, did1, did2);
            }
        }

        void draw(Func move)
        {
            xI += 500;
            xII += 500;
            yII += 225;
            yI += 225;
            graph.Clear(Color.White);
            strbrez8(xI, yI, xI, yII, move);
            strbrez8(xI, yI, xII, yI, move);
            strbrez8(xII, yII, xI, yII, move);
            strbrez8(xII, yII, xII, yI, move);
            strbrez8(xII, yII, xI, yI, move);
            strbrez8(xI, yII, xII, yI, move);
        }

        public Form1()
        {
            InitializeComponent();
            pixel = new Bitmap(2, 2);
            pic = new Bitmap(1000, 450);
            graph = Graphics.FromImage(pic);
            pixel.SetPixel(0, 0, Color.Black);
            pixel.SetPixel(1, 0, Color.Black);
            pixel.SetPixel(0, 1, Color.Black);
            pixel.SetPixel(1, 1, Color.Black);
            saveFileDialog1.DefaultExt = "png";
            xI = -100;
            yI = -25;
            xII = 100;
            yII = 25;
            draw(offset);
            pictureBox1.Image = pic;
        }

        private void ВыходToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Application.Exit();
        }

        public void Checker (ToolStripMenuItem Mitem)
        {
            Item1.Checked = false;
            Item2.Checked = false;
            Item3.Checked = false;
            Item4.Checked = false;
            Item5.Checked = false;
            Item6.Checked = false;
            Item7.Checked = false;
            Item8.Checked = false;
            Item9.Checked = false;
            Mitem.Checked = true;
        }

        public void Varible(int mod)
        {
            if (mod == 5)
            {
                TextBox3.Visible = true;
                TextBox4.Visible = false;
                label3.Visible = true;
                label4.Visible = false;
                label3.Text = "    g ";
                TextBox2.Visible = true;
                TextBox1.Visible = true;
                label2.Visible = true;
                label1.Visible = true;
                label1.Text = "    X ";
                label2.Text = "    Y ";
                TextBox3.Mask = "#000"; //000
            }
            if (mod == 4) {
                TextBox3.Visible = true;
                TextBox4.Visible = true;
                label3.Visible = true;
                label4.Visible = true;
                label3.Text = "    X2 ";
                label4.Text = "    Y2 ";
                TextBox2.Visible = true;
                TextBox1.Visible = true;
                label2.Visible = true;
                label1.Visible = true;
                label1.Text = "    X1 ";
                label2.Text = "    Y1 ";
                TextBox3.Mask = "#000";
                TextBox4.Mask = "#000";
            }
            if (mod == 3) {
                TextBox3.Visible = true;
                TextBox4.Visible = true;
                label3.Visible = true;
                label4.Visible = true;
                label3.Text = "    kx ";
                label4.Text = "    ky ";
                TextBox2.Visible = true;
                TextBox1.Visible = true;
                label2.Visible = true;
                label1.Visible = true;
                label1.Text = "    X ";
                label2.Text = "    Y ";
                TextBox3.Mask = "0.00";
                TextBox4.Mask = "0.00";
            }
            if (mod == 2) {
                TextBox3.Visible = false;
                TextBox4.Visible = false;
                label3.Visible = false;
                label4.Visible = false;
                TextBox2.Visible = true;
                TextBox1.Visible = true;
                label2.Visible = true;
                label1.Visible = true;
                label1.Text = "    X ";
                label2.Text = "    Y ";
            }
            if (mod == 0)  {
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

        private void Item1_Click(object sender, EventArgs e)
        {
            Checker(Item1);
            Varible(4);
        }

        private void Item2_Click(object sender, EventArgs e)
        {
            Checker(Item2);
            Varible(2);
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

        private void Item5_Click(object sender, EventArgs e)
        {
            Checker(Item5);
            Varible(0);
        }

        private void Item6_Click(object sender, EventArgs e)
        {
            Checker(Item6);
            Varible(0);
        }

        private void Item7_Click(object sender, EventArgs e)
        {
            Checker(Item7);
            Varible(3);
        }

        private void Item8_Click(object sender, EventArgs e)
        {
            Checker(Item8);
            Varible(5);
        }

        private void Item9_Click(object sender, EventArgs e)
        {
            Checker(Item9);
            Varible(5);
        }

        private void button2_Click(object sender, EventArgs e)
        {
            graph.Clear(Color.White);
            pictureBox1.Image = pic;
        }

        private void button3_Click_1(object sender, EventArgs e)
        {
            if (saveFileDialog1.ShowDialog() == DialogResult.OK)
            {
                if (saveFileDialog1.FileName != "") { pic.Save(saveFileDialog1.FileName); }
            }
        }

        async private void button1_Click(object sender, EventArgs e)
        {
            int i = 0;
            if (Item1.Checked) {
                if (int.TryParse(TextBox1.Text, out xI) == false) { xI = 0; }
                if (int.TryParse(TextBox2.Text, out yI) == false) { yI = 0; }
                if (int.TryParse(TextBox3.Text, out xII) == false) { xII = 0; }
                if (int.TryParse(TextBox4.Text, out yII) == false) { yII = 0; }
            }
            if (Item2.Checked) {
                if (int.TryParse(TextBox1.Text, out a) == false) { a = 0; }
                if (int.TryParse(TextBox2.Text, out b) == false) { b = 0; }
            }
            if (Item7.Checked)
            {
                if (int.TryParse(TextBox1.Text, out a) == false) { a = 0; }
                if (int.TryParse(TextBox2.Text, out b) == false) { b = 0; }
                if (float.TryParse(TextBox3.Text, out kx) == false) { kx = 0; }
                if (float.TryParse(TextBox4.Text, out ky) == false) { ky = 0; }
            }
            if (Item8.Checked || Item9.Checked)
            {
                if (int.TryParse(TextBox1.Text, out a) == false) { a = 0; }
                if (int.TryParse(TextBox2.Text, out b) == false) { b = 0; }
                if (int.TryParse(TextBox3.Text, out g) == false) { g = 0; }
                if (float.TryParse(TextBox4.Text, out kx) == false) { kx = 0; }
                if ((Convert.ToInt32(TextBox1.Text) > 500) /*|| (Convert.ToInt32(TextBox3.Text) > 360) || (Convert.ToInt32(TextBox3.Text) < 0)*/ || (Convert.ToInt32(TextBox1.Text) < -500) || (Convert.ToInt32(TextBox2.Text) > 225) || (Convert.ToInt32(TextBox2.Text) < -225))
                {
                    MessageBox.Show("Координата х не может превышать 500, у не может превышать 225, g не может превышать 360");
                    return;
                }
            }
            // MessageBox.Show(Convert.ToString(xI) + " " + Convert.ToString(yI) + " " + Convert.ToString(xII) + " " + Convert.ToString(yII) + " " + Convert.ToString(a) + " " + Convert.ToString(b));
            if (!Item7.Checked && !Item8.Checked && !Item9.Checked && !Item2.Checked)
            {
                if ((Convert.ToInt32(TextBox1.Text) > 500) || (Convert.ToInt32(TextBox3.Text) > 500) || (Convert.ToInt32(TextBox1.Text) < -500) || (Convert.ToInt32(TextBox3.Text) < -500) ||
                    (Convert.ToInt32(TextBox2.Text) > 225) || (Convert.ToInt32(TextBox4.Text) > 225) || (Convert.ToInt32(TextBox2.Text) < -225) || (Convert.ToInt32(TextBox4.Text) < -225))
                {
                    MessageBox.Show("Координата х не может превышать 500, у не может превышать 225");
                    return;
                }
            }
            if (Item7.Checked)
            {
                if ((Convert.ToInt32(TextBox1.Text) > 500) || (Convert.ToInt32(TextBox1.Text) < -500) || (Convert.ToInt32(TextBox2.Text) > 225) || (Convert.ToInt32(TextBox2.Text) < -225))
                {
                    MessageBox.Show("Координата х не может превышать 500, у не может превышать 225");
                    return;
                }
            }

            if (Item1.Checked) {                                           // рисованиe     
                a = 0;
                b = 0;
                draw(offset); 
            }                           
            else if (Item2.Checked) {                                      // смещение
                xI -= 500;
                xII -= 500;
                yII -= 225;
                yI -= 225;
                draw(offset);
                xI += a;
                xII += a; 
                yII += b;
                yI += b;
            }
            else if (Item3.Checked) {                                      // отражение ох
                xI -= 500;
                xII -= 500;
                yII -= 225;
                yI -= 225;
                draw(reflexOX);
                yII -= 225;
                yI -= 225;
                yI = -yI;
                yII = -yII;
                yII += 225;
                yI += 225;
            }                        
            else if (Item4.Checked) {                                     // отражение оy
                xI -= 500;
                xII -= 500;
                yII -= 225;
                yI -= 225;
                draw(reflexOY);
                xII -= 500;
                xI -= 500;
                xI = -xI;
                xII = -xII;
                xII += 500;
                xI += 500;
            }                        
            else if (Item5.Checked) {                                      // отражение y = x
                a = 0;
                b = 0;
                xI -= 500;
                xII -= 500;
                yII -= 225;
                yI -= 225;
                (xI, yI) = (-yI, -xI);
                (xII, yII) = (-yII, -xII);
                draw(offset); 
            }                      
            else if (Item6.Checked) {                                     // отражение y = -x 
                a = 0;
                b = 0;
                xI -= 500;
                xII -= 500;
                yII -= 225;
                yI -= 225;
                (xI, yI) = (yI, xI);
                (xII, yII) = (yII, xII);
                draw(offset);
            }                       
            else if (Item7.Checked) {                                     // масштабирование
                xI -= 500;
                xII -= 500;
                yII -= 225;
                yI -= 225;
                draw(scale);
                xI -= 500;
                xII -= 500;
                yII -= 225;
                yI -= 225;  
                xI = (int)Math.Round((float)(xI * kx - a * kx + a));
                xII = (int)Math.Round((float)(xII * kx - a * kx + a));
                yI = (int)Math.Round((float)(yI * ky - b * ky + b));
                yII = (int)Math.Round((float)(yII * ky - b * ky + b));
                xI += 500;
                xII += 500;
                yII += 225;
                yI += 225;  
            }                          
            else if (Item8.Checked) {                                      // вращение по часовой
                r = 0;
                while (r <= g) {
                    //MessageBox.Show("da");
                    xI -= 500;
                    xII -= 500;
                    yII -= 225;
                    yI -= 225;
                    r += 1;
                    draw(left);
                    await Task.Delay(10);
                    pictureBox1.Image = pic;
                }
            }
            else if (Item9.Checked) {                                        // вращение против часовой
                r = 0;
                while (r < g)
                {
                    //MessageBox.Show("da");
                    xI -= 500;
                    xII -= 500;
                    yII -= 225;
                    yI -= 225;
                    r += 1;
                    draw(right);
                    await Task.Delay(10);
                    pictureBox1.Image = pic;
                }
            }

            pictureBox1.Image = pic;
        }

    }

}

