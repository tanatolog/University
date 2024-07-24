using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Images
{
    public partial class Form1 : Form
    {
        byte[,] image_matr; // матрица полутонового изображения
        double[,] obr_image; // матрица обработанного изображения
        int w_b, h_b; //ширина и высота изображения

        public Form1()
        {
            InitializeComponent();
        }

        private void button_Click(object sender, EventArgs e)
        {
            openFileDialog1.Filter = "JPeg Image|*.jpg|Bitmap Image|*.bmp|Gif Image|*.gif|Png Image|*.png";
            openFileDialog1.Title = "Выберите файл изображения";

            if (openFileDialog1.ShowDialog() == System.Windows.Forms.DialogResult.OK)
            {
                pictureBox1.Image = Image.FromFile(@openFileDialog1.FileName);
            }
        }

        private void button1_Click(object sender, EventArgs e)
        {
            Bitmap ish_bitmap = (Bitmap)pictureBox1.Image;
            Bitmap now = (Bitmap)pictureBox1.Image;
            w_b = ish_bitmap.Width;  //Ширина изображения
            h_b = ish_bitmap.Height; //Высота изображения

            image_matr = new byte[w_b, h_b];  //матрица изображения 
            obr_image = new double[w_b, h_b];  //матрица изображения 

            for (int x = 0; x < w_b; x++) {
                for (int y = 0; y < h_b; y++) {
                    Color c = ish_bitmap.GetPixel(x, y);//получаем цвет указанной точки

                    int r = Convert.ToInt32(c.R);
                    int b = Convert.ToInt32(c.B);
                    int g = Convert.ToInt32(c.G);
                    int brit = Convert.ToInt32(0.299 * r + 0.587 * g + 0.114 * b); //Перевод из RGB в полутон 

                    // image_matr[x, y] = Convert.ToByte(brit); 
                    // 255 - c.R негатив, среднее арифметическое - ч/б

                    int sr = (int)Math.Round((float)((r + b + g) / 3));

                    c = Color.FromArgb(sr, sr, sr);
                    now.SetPixel(x, y, c);
                }
            }
            pictureBox1.Image = now; 

          /*for (int x = 0; x < w_b; x++)
            {
                for (int y = 0; y < h_b; y++)
                {
                    obr_image[x, y] = (double)(255 - image_matr[x, y]);
                }
            }

            Bitmap obr = (Bitmap)pictureBox1.Image;
            for (int x = 0; x < w_b; x++)
            {
                for (int y = 0; y < h_b; y++)
                {
                    byte briteness = Convert.ToByte(obr_image[x, y]);
                    System.Drawing.Color c = System.Drawing.Color.FromArgb(briteness, briteness, briteness);
                    obr.SetPixel(x, y, c);
                }
            }
            pictureBox1.Image = obr; */
        }
    }
}
