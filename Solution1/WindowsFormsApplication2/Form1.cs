using System;
using System.Windows.Forms;

namespace WindowsFormsApplication2
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();

            viewModelBindingSource.DataSource = new ViewModel();
        }
    }
}
