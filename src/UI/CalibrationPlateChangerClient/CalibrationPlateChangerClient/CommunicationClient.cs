using System;
using System.Threading;
using System.Net;
using System.Net.Sockets;
using System.IO;

namespace CalibrationPlateChangerClient {
    class CommunicationClient
    {
        private string m_ServerIp;
        private int m_ServerPort;
        private TcpClient m_TcpClient;
        private Thread m_ReceiveThread;
        private bool m_IsConnected;
        
        public CommunicationClient(string serverIp, int serverPort) {
            m_ServerIp = serverIp;
            m_ServerPort = serverPort;
            m_TcpClient = new TcpClient();
            m_IsConnected = false;
        }

        public int Connect() {
            if (m_TcpClient.Connected)
                return -1;
            try {
                m_TcpClient.Connect(m_ServerIp, m_ServerPort);
                m_IsConnected = true;
            }
            catch (SocketException ex) {
                return -2;
            }
            return 0;
        }

        public int Disconnect() {
            if (!m_IsConnected)
                return -1;
            if (m_ReceiveThread != null) {
                try {
                    m_ReceiveThread.Abort();
                    m_ReceiveThread = null;
                }
                catch (ThreadAbortException ex) {
                    return -3;
                }
            }
            try {  
                m_TcpClient.Close();
                m_IsConnected = false;
                m_TcpClient = new TcpClient();
            }
            catch (SocketException ex) {
                return -2;
            }
            return 0;
        }

        public int Send(string dataToSend) {
            if (!m_TcpClient.Connected)
                return -1;
            if (ConnectionState() != 0) {
                Disconnect();
                return -4;
            }
            try {
                NetworkStream dataStream = m_TcpClient.GetStream();
                byte[] dataBuffer = System.Text.Encoding.ASCII.GetBytes(dataToSend);
                dataStream.Write(dataBuffer, 0, dataBuffer.Length);
                dataStream.Flush();
            }
            catch (SocketException ex) {
                Disconnect();
                return -2;
            }
            catch (IOException ex) {
                Disconnect();
                return -3;
            }
            return 0;
        }

        public int StartReceiving(Func<string, int> receiveHandler) {
            if (!m_TcpClient.Connected)
                return -1;
            if (m_ReceiveThread != null)
                return -2;
            try {
                m_ReceiveThread = new Thread(() => ReceiveListener(receiveHandler));
                m_ReceiveThread.Start();
            }
            catch (ThreadStartException ex) {
                return -3;
            }
            return 0;
        }

        private void ReceiveListener(Func<string, int> receiveHandler) {
            while (m_TcpClient.Connected) {
                if (ConnectionState() != 0)
                    return;
                NetworkStream dataStream = m_TcpClient.GetStream();
                int buffSize = 0;
                byte[] inStream = new byte[256];
                buffSize = m_TcpClient.ReceiveBufferSize;
                try {
                    dataStream.Read(inStream, 0, inStream.Length);
                }
                catch (SocketException ex) {
                    Disconnect();
                    return;
                }
                string receivedData = System.Text.Encoding.ASCII.GetString(inStream);
                if (receivedData.EndsWith("\0"))
                    receivedData = receivedData.TrimEnd('\0');
                if (receiveHandler(receivedData) != 0) 
                    return;            
            }
        }

        private int ConnectionState() {
            if (m_TcpClient.Client.Poll(0, SelectMode.SelectRead)) {
                byte[] buffer = new byte[1];
                if (m_TcpClient.Client.Receive(buffer, SocketFlags.Peek) == 0)
                    return -1;
            }
            return 0;
        }

        public string GetLocalIPAddress() {
            var host = Dns.GetHostEntry(Dns.GetHostName());
            foreach (var ip in host.AddressList) {
                if (ip.AddressFamily == AddressFamily.InterNetwork) {
                    string[] ipNrsServer = m_ServerIp.ToString().Split('.');
                    string[] ipNrsHost = ip.ToString().Split('.');
                    if (ipNrsServer[0] == ipNrsHost[0] && ipNrsServer[1] == ipNrsHost[1] && ipNrsServer[2] == ipNrsHost[2])
                        return ip.ToString();
                }
            }
            throw new Exception("Local IP Address Not Found!");
        }
    }
}
