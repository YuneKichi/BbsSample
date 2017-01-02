using System;
using System.ComponentModel;
using System.Threading;

namespace ClassLibrary1
{
    public sealed class Model : INotifyPropertyChanged
    {
        private int _index;
        private readonly int _maxIndex;
        private Timer _timer;

        [Obsolete("use only design time.", true)]
        public Model()
        {
            throw new InvalidOperationException();
        }

        public Model(int maxIndex)
        {
            if (maxIndex <= 0)
            {
                throw new ArgumentOutOfRangeException("maxIndex");
            }
            _maxIndex = maxIndex;
            _index = 0;
            _timer = new Timer(TimerTicked, null, 1000, 1000);
        }

        private void TimerTicked(object state)
        {
            Index = (Index + 1) % _maxIndex;
        }

        public int Index
        {
            get { return _index; }
            private set
            {
                if (_index == value)
                {
                    return;
                }
                _index = value;
                if (PropertyChanged != null)
                {
                    PropertyChanged(this, IndexChangedEventArgs);
                }
            }
        }
        private static readonly PropertyChangedEventArgs IndexChangedEventArgs = new PropertyChangedEventArgs("Index");

        public event PropertyChangedEventHandler PropertyChanged;
    }
}
