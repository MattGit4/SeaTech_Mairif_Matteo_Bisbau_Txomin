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
using System.Security.RightsManagement;

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
            serialPort1 = new ExtendedSerialPort("COM8", 115200, Parity.None, 8, StopBits.One);
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
                DecodeMessage(c);
                //textBoxReception.Text += c.ToString("X2") + " ";
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
            //byte[] byteList = new byte[20];
            //for (int i = 0; i < byteList.Length; i++) {
            //byteList[i] = (byte)(2 * i);
            //}
            //serialPort1.Write(byteList,0,byteList.Length);
            
            byte[] array = Encoding.ASCII.GetBytes("Bonjour");
            UartEncodeAndSendMessage(0x0080,array.Length,array);
        }

        private void textBoxEmission_KeyUp(object sender, KeyEventArgs e)
        {
            if (e.Key == Key.Enter) 
            {
                SendMessage();
            }
        }

        byte CalculateChecksum(int msgFunction,int msgPayloadLength, byte[] msgPayload)
        {
            byte checksum = 0;
            checksum ^= 0xFE;
            checksum ^= (byte) (msgFunction >> 8);
            checksum ^= (byte)(msgFunction >> 0);
            checksum ^= (byte)(msgPayloadLength >> 8);
            checksum ^= (byte)(msgPayloadLength >> 0);
            for (int i=0; i < msgPayloadLength; i++)
            {
                checksum ^= msgPayload[i];
            }
            return checksum;
        }

        void UartEncodeAndSendMessage(int msgFunction,int msgPayloadLength, byte[] msgPayload)
        {
            int taille = msgPayloadLength + 6;
            byte[] trame = new byte[taille];
            int pos = 0;
            trame[pos++] = 0xFE;
            trame[pos++] = (byte)(msgFunction >> 8);
            trame[pos++] = (byte)(msgFunction);
            trame[pos++] = (byte)(msgPayloadLength >> 8);
            trame[pos++] = (byte)(msgPayloadLength);
            for (int i = 0; i < msgPayloadLength; i++)
                trame[pos++] = msgPayload[i];
            trame[pos++] = CalculateChecksum(msgFunction, msgPayloadLength, msgPayload);
            serialPort1.Write(trame, 0, trame.Length);
        }

        public enum StateReception
        {
            Waiting,
            FunctionMSB,
            FunctionLSB,
            PayloadLengthMSB,
            PayloadLengthLSB,
            Payload,
            CheckSum
        }
        StateReception rcvState = StateReception.Waiting;
        int msgDecodedFunction = 0;
        int msgDecodedPayloadLength = 0;
        byte[] msgDecodedPayload;
        int msgDecodedPayloadIndex = 0;
        private void DecodeMessage(byte c)
        {
            switch (rcvState)
            {
                case StateReception.Waiting:
                    if (c == 0xFE)
                        rcvState = StateReception.FunctionMSB;
                break;
                case StateReception.FunctionMSB:
                    msgDecodedFunction = c << 8;
                    rcvState = StateReception.FunctionLSB;
                break;
                case StateReception.FunctionLSB:
                    msgDecodedFunction |= c;
                    rcvState = StateReception.PayloadLengthMSB;
                break;
                case StateReception.PayloadLengthMSB:
                    msgDecodedPayloadLength = c << 8;
                    rcvState = StateReception.PayloadLengthLSB;
                break;
                case StateReception.PayloadLengthLSB:
                    msgDecodedPayloadLength |= c;
                    if (msgDecodedPayloadLength == 0)
                        rcvState = StateReception.CheckSum;
                    else if (msgDecodedPayloadLength > 512)
                        rcvState = StateReception.Waiting;
                    else
                    {
                        msgDecodedPayload = new byte[msgDecodedPayloadLength];
                        msgDecodedPayloadIndex = 0;
                        rcvState = StateReception.Payload;
                    }
                break;
                case StateReception.Payload:
                    msgDecodedPayload[msgDecodedPayloadIndex++] = c;
                    if (msgDecodedPayloadIndex >= msgDecodedPayloadLength)
                        rcvState = StateReception.CheckSum;
                break;
                case StateReception.CheckSum:
                    var calculatedChecksum = CalculateChecksum(msgDecodedFunction, msgDecodedPayloadLength, msgDecodedPayload);
                    var receivedChecksum = c;
                    if (calculatedChecksum == receivedChecksum)
                        {
                            //Success, on a un message valide
                            textBoxReception.Text += "\n Cool";
                        }
                    else
                        {
                            textBoxReception.Text += "\n Pas Cool";
                        }
                    rcvState = StateReception.Waiting;
                break;
                default:
                    rcvState = StateReception.Waiting;
                    break;
            }
        }


    }
    }