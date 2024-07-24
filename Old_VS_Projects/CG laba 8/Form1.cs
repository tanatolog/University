using System;
using System.Collections.Generic;
using System.Drawing;
using System.Drawing.Drawing2D;
using System.Globalization;
using System.IO;
using System.Net;
using System.Numerics;
using System.Windows.Forms;
using System.Linq;
using System.ComponentModel;
using System.Data;
using System.Text;
using System.Threading.Tasks;

namespace WindowsFormsApp1
{
    public partial class Form1 : Form
    {
        Model model;
        TrackBar tbSize;
        TrackBar tbRoll;
        TrackBar tbPitch;
        TrackBar tbYaw;
        string filePath = "";

        public Form1()
        {
            InitializeComponent();

            SetStyle(ControlStyles.AllPaintingInWmPaint | ControlStyles.OptimizedDoubleBuffer | ControlStyles.UserPaint, true);

            Size = new Size(1000, 500);
            openFileDialog1.DefaultExt = "obj";
            tbSize = new TrackBar { Parent = this, Maximum = 200, Left = 0, Value = 10 };
            tbRoll = new TrackBar { Parent = this, Maximum = 360, Left = 110, Value = 30 };
            tbPitch = new TrackBar { Parent = this, Maximum = 360, Left = 220, Value = 45 };
            tbYaw = new TrackBar { Parent = this, Maximum = 360, Left = 330, Value = 45 };

            tbSize.ValueChanged += tb_ValueChanged;
            tbRoll.ValueChanged += tb_ValueChanged;
            tbPitch.ValueChanged += tb_ValueChanged;
            tbYaw.ValueChanged += tb_ValueChanged;

            model = new Model();
        }

        void tb_ValueChanged(object sender, EventArgs e)
        {
            scale = tbSize.Value;
            pitch = (float)(tbPitch.Value * Math.PI / 180);
            roll = (float)(tbRoll.Value * Math.PI / 180);
            yaw = (float)(tbYaw.Value * Math.PI / 180);

            Invalidate();
        }

        float yaw = 0;
        float pitch = 0;
        float roll = 0;
        float scale = 10;
        Vector3 position = new Vector3(500, 200, 200);

        protected override void OnPaint(PaintEventArgs e)
        {
            var scaleM = Matrix4x4.CreateScale(scale / 2);
            var rotateM = Matrix4x4.CreateFromYawPitchRoll(yaw, pitch, roll);
            var translateM = Matrix4x4.CreateTranslation(position);
            var paneXY = new Matrix4x4() { M11 = 1f, M22 = 1f, M44 = 1f };
            var m = scaleM * rotateM * translateM * paneXY;
            var vertexes = model.Vertexes.Select(v => Vector3.Transform(v, m)).ToList();

            using (var path = new GraphicsPath())
            {
                var prev = Vector3.Zero;
                var prevF = 0;
                foreach (var f in model.Fig)
                {
                    if (f == 0) path.CloseFigure();
                    var v = vertexes[f];
                    if (prevF != 0 && f != 0)
                        path.AddLine(prev.X, prev.Y, v.X, v.Y);
                    prev = v;
                    prevF = f;
                }

                e.Graphics.DrawPath(Pens.Black, path);
            }
        }

        private void button1_Click(object sender, EventArgs e)
        {
            if (openFileDialog1.ShowDialog() == DialogResult.OK)
            {
                tb_ValueChanged(null, EventArgs.Empty);
                filePath = openFileDialog1.FileName;
                model.LoadFromObj(new StreamReader(File.OpenRead(@filePath)));            //"C:\Users\User\Desktop\Steve"
            }
        }
    }

    public class Model
    {
        public List<Vector3> Vertexes = new List<Vector3>();
        public List<int> Fig = new List<int>();

        public void LoadFromObj(TextReader tr)
        {
            string line;
            Vertexes.Clear();
            Vertexes.Add(Vector3.Zero);

            while ((line = tr.ReadLine()) != null)
            {
                var parts = line.Split(' ');
                if (parts.Length == 0) continue;
                switch (parts[0])
                {
                    case "v":
                        Vertexes.Add(new Vector3(float.Parse(parts[1], CultureInfo.InvariantCulture),
                  float.Parse(parts[2], CultureInfo.InvariantCulture),
                  float.Parse(parts[3], CultureInfo.InvariantCulture)));
                        break;
                    case "f":
                        for (int i = 1; i < parts.Length; i++)
                            Fig.Add(int.Parse(parts[i].Split('/')[0]));
                        Fig.Add(0);
                        break;
                }
            }
        }
    }
}
