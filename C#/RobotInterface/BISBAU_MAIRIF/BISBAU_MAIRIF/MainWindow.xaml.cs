using System.Text;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using ExtendedSerialPort_NS;
using System.IO.Ports;

namespace BISBAU_MAIRIF
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        ExtendedSerialPort serialPort1;


        public MainWindow()
        {
            InitializeComponent();
            serialPort1 = new ExtendedSerialPort("COM8", 115200, Parity.None, 8, StopBits.One);
            serialPort1.Open();
        }


        int a = 0;
        private void SendMessage()
        {
            textBoxReception.Text += "Reçu : " + textBoxEmission.Text + "\n";
            textBoxEmission.Text = null;
        }
        private void DeletMessage()
        {

            textBoxReception.Text = null;
        }
        private void buttonEnvoyer_Click(object sender, RoutedEventArgs e)
        {
            a++;
            if (a % 2 == 0) { buttonEnvoyer.Background = Brushes.RoyalBlue; }
            else { buttonEnvoyer.Background = Brushes.Beige; }
            SendMessage();
        }
        private void buttonClear_Click(object sender, RoutedEventArgs e)
        {
            a++;
            if (a % 2 == 0) { buttonClear.Background = Brushes.RoyalBlue; }
            else { buttonClear.Background = Brushes.Beige; }    
            DeletMessage();
        }
        private void buttonTest_Click(object sender, RoutedEventArgs e)
        {
            a++;
            if (a % 2 == 0) { buttonTest.Background = Brushes.RoyalBlue; }
            else { buttonTest.Background = Brushes.Beige; }
        }

        private void textBoxEmission_KeyUp(object sender, KeyEventArgs e)
        {
            if (e.Key == Key.Enter) 
            {
                SendMessage();
            }
        }
    }
}