using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using System.Windows.Threading;

namespace WpfApplication1
{
    /// <summary>
    /// MainWindow.xaml の相互作用ロジック
    /// </summary>
    public partial class MainWindow : Window
    {
        private static readonly Brush[] _backBrushes =
        {
            Brushes.Black,
            Brushes.Blue,
            Brushes.Green,
            Brushes.Cyan,
            Brushes.Red,
            Brushes.Purple,
            Brushes.Yellow,
            Brushes.White,
        };

        private readonly DispatcherTimer _timer;
        private int _brushIndex = 0;

        public MainWindow()
        {
            InitializeComponent();

            _timer = new DispatcherTimer(DispatcherPriority.Normal);
            _timer.Interval = TimeSpan.FromSeconds(1);
            _timer.Tick += timerTick;
            _timer.Start();

            ChangeBackground();
        }

        private void timerTick(object sender, EventArgs e)
        {
            ChangeBackground();
        }

        private void ChangeBackground()
        {
            this.Background = _backBrushes[_brushIndex];
            _brushIndex = (_brushIndex + 1) % _backBrushes.Length;
        }
    }
}
