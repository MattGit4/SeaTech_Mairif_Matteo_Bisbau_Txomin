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
using System.Windows.Interop;
using System.Windows.Threading;
using System.Collections.Generic;

namespace BISBAU_MAIRIF
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        ExtendedSerialPort serialPort1;
        DispatcherTimer timerAffichage;
        Robot robot = new Robot();


        public MainWindow()
        {
            InitializeComponent();
            serialPort1 = new ExtendedSerialPort("COM3", 115200, Parity.None, 8, StopBits.One);
            serialPort1.DataReceived += SerialPort1_DataReceived;
            serialPort1.Open();
            timerAffichage = new DispatcherTimer();
            timerAffichage.Interval = new TimeSpan(0, 0, 0, 0, 100);
            timerAffichage.Tick += TimerAffichage_Tick;
            timerAffichage.Start();
        }

        private void TimerAffichage_Tick(object? sender, EventArgs e)
        {
            // textBoxReception.Text += robot.receivedText;
            // robot.receivedText = "";
            while (robot.byteListReceived.Count > 0)
            {
                var c = robot.byteListReceived.Dequeue();
                textBoxReception.Text += "0x" + c.ToString("X2") + " ";
            }
        }

        public void SerialPort1_DataReceived(object sender, DataReceivedArgs e)
        {
            //robot.receivedText += Encoding.UTF8.GetString(e.Data, 0, e.Data.Length);
            foreach (var item in e.Data)
            {
                robot.byteListReceived.Enqueue(item);
            }
        }


        int a = 0;
        private void SendMessage()
        {
            //textBoxReception.Text += "Reçu : " + textBoxEmission.Text + "\n";
            serialPort1.WriteLine(textBoxEmission.Text);
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
            byte[] byteList = new byte[20];
            for (int i = 0; i < byteList.Length; i++) {
                byteList[i] = (byte)(2 * i);
            }
            serialPort1.Write(byteList,0,byteList.Length);
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