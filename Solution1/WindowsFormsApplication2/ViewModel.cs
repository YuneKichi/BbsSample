using System;
using System.ComponentModel;
using System.Drawing;
using System.Threading;
using ClassLibrary1;

namespace WindowsFormsApplication2
{
    public class ViewModel : INotifyPropertyChanged
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

        private readonly Model _model;
        private readonly SynchronizationContext _context;

        public ViewModel()
        {
            _context = SynchronizationContext.Current;
            _model = new Model(_backColors.Length);

            _model.PropertyChanged += modelPropertyChanged;
        }

        public Color Background
        {
            get
            {
                return _backColors[_model.Index];
            }
        }

        private void modelPropertyChanged(object sender, PropertyChangedEventArgs e)
        {
            switch (e.PropertyName)
            {
                case "Index":
                    modelIndexPropertyChanged();
                    break;
            }
        }

        private void modelIndexPropertyChanged()
        {
            if (PropertyChanged == null)
            {
                return;
            }
            if (_context == null)
            {
                PropertyChanged(this, BackgroundChangedEventArgs);
            }
            else
            {
                _context.Post(state => PropertyChanged(this, BackgroundChangedEventArgs), null);
            }
        }

        private static readonly PropertyChangedEventArgs BackgroundChangedEventArgs = new PropertyChangedEventArgs("Background");

        public event PropertyChangedEventHandler PropertyChanged;
    }
}
