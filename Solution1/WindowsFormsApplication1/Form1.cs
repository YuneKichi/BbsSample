using System;
using System.Drawing;
using System.Windows.Forms;

namespace WindowsFormsApplication1
{
    public partial class Form1 : Form
    {
        private static readonly Color[] _backColors =
        {
            Color.Black,
            Color.Blue,
            Color.Green,
            Color.Cyan,
            Color.Red,
            Color.Purple,
            Color.Yellow,
            Color.White,
        };

        private int _colorIndex = 0;

        public Form1()
        {
            InitializeComponent();

            ChangeBackgroundColor();
        }

        private void timer1_Tick(object sender, EventArgs e)
        {
            ChangeBackgroundColor();
        }

        private void ChangeBackgroundColor()
        {
            this.BackColor = _backColors[_colorIndex];
            _colorIndex = (_colorIndex + 1) % _backColors.Length;
        }
    }
}
