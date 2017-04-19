using System;
using System.Threading;
using System.Net.Sockets;
using System.Windows.Forms;

namespace SocketClient_PoC
{
    public partial class Form1 : Form
    {
        private const string serverIp = "192.168.0.42";
        private const int serverPort = 4244;
        private bool isConnected;
        private Thread receiveThread;
        private TcpClient tcpClient;

        public Form1()
        {
            InitializeComponent();
            tcpClient = new TcpClient();
            isConnected = false;
            UpdateUI();
        }

        private void UpdateUI()
        {
            if (isConnected)
            {
                btnSend.Enabled = true;
                tbToSend.Enabled = true;
                btnDisconnect.Enabled = true;
                btnConnect.Enabled = false;
            }
            else
            {
                btnSend.Enabled = false;
                tbToSend.Enabled = false;
                btnDisconnect.Enabled = false;
                btnConnect.Enabled = true;
            }
        }

        private void btnConnect_Click(object sender, EventArgs e)
        {
            if (isConnected)
            {
                return;
            }
            logMessage("Connecting.....");
            try
            {
                tcpClient.Connect(serverIp, serverPort);
                isConnected = true;
            }
            catch(SocketException ex)
            {
                logMessage(ex.ToString());
                return;
            }
            logMessage("Connected!");
            receiveThread = new Thread(receiveListener);
            receiveThread.Start();
            UpdateUI();
        }

        private void btnClear_Click(object sender, EventArgs e)
        {
            tbLog.Text = "";
        }

        private void btnSend_Click(object sender, EventArgs e)
        {
            try
            {
                NetworkStream dataStream = tcpClient.GetStream();
                byte[] dataBuffer = System.Text.Encoding.ASCII.GetBytes(tbToSend.Text);
                dataStream.Write(dataBuffer, 0, dataBuffer.Length);
                dataStream.Flush();
            }
            catch (SocketException ex)
            {
                logMessage(ex.ToString());
                return;
            }
            logMessage("Sent: " + tbToSend.Text);
        }

        private void btnDisconnect_Click(object sender, EventArgs e)
        {
            Disconnect();
        }

        private void Disconnect()
        {
            if (!isConnected)
            {
                return;
            }
            try
            {
                receiveThread.Abort();
                tcpClient.GetStream().Close();
                tcpClient.Close();
                tcpClient = new TcpClient();
                isConnected = false;
            }
            catch (Exception ex)
            {
                logMessage(ex.ToString());
                return;
            }
            logMessage("Disconnected!");
            UpdateUI();
        }

        private void receiveListener()
        {
            logMessage("Start receiving");
            string receivedData = null;
            while (tcpClient.Connected)
            {
                if (tcpClient.Client.Poll(0, SelectMode.SelectRead))
                {
                    byte[] buffer = new byte[1];
                    if (tcpClient.Client.Receive(buffer, SocketFlags.Peek) == 0)
                    {
                        logMessage("Connection closed.");
                        return;
                    }
                }
                NetworkStream dataStream = tcpClient.GetStream();
                int buffSize = 0;
                byte[] inStream = new byte[256];
                buffSize = tcpClient.ReceiveBufferSize;
                try
                {
                    dataStream.Read(inStream, 0, inStream.Length);
                }
                catch (Exception ex)
                {
                    logMessage(ex.ToString());
                    return;
                }
                string returndata = System.Text.Encoding.ASCII.GetString(inStream);
                receivedData = "" + returndata;
                logMessage("Received data: " + receivedData);
            }
        }

        private void logMessage(string message)
        {
            if (InvokeRequired)
            {
                this.Invoke(new Action<string>(logMessage), new object[] { message });
                return;
            }
            tbLog.AppendText(message + "\r\n");
        }
    }
}
