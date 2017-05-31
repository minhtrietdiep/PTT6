using System;
using System.Threading;
using System.Net.Sockets;
using System.IO;
using System.Security;

namespace CalibrationPlateChangerClient
{
    class CommunicationClient
    {
        private string m_ServerIp;
        private int m_ServerPort;
        private TcpClient m_TcpClient;
        private Thread m_ReceiveThread;
        private bool m_IsConnected;
        
        public CommunicationClient(string serverIp, int serverPort)
        {
            m_ServerIp = serverIp;
            m_ServerPort = serverPort;
            m_TcpClient = new TcpClient();
            m_TcpClient.NoDelay = true;
            m_IsConnected = false;
        }

        public int Connect()
        {
            if (m_TcpClient.Connected)
            {
                return -1;
            }
            try
            {
                IAsyncResult result = m_TcpClient.BeginConnect(m_ServerIp, m_ServerPort, null, null);
                bool success = result.AsyncWaitHandle.WaitOne(1000);
                if (!success)
                {
                    throw new TimeoutException();
                }
                m_IsConnected = true;
            }
            catch (ArgumentNullException ex)
            {
                Console.WriteLine(ex + "\nHost parameter is null");
                return -2;
            }
            catch (SocketException ex)
            {
                Console.WriteLine(ex + "\nAn error occured when attempting to access the socket");
                return -3;
            }
            catch (ObjectDisposedException ex)
            {
                Console.WriteLine(ex + "\nThe socket has been closed");
                return -4;
            }
            catch (ArgumentOutOfRangeException ex)
            {
                Console.WriteLine(ex + "\nInvalid port");
                return -5;
            }
            catch (TimeoutException ex)
            {
                Console.WriteLine(ex + "\nServer is not responding");
                return -6;
            }
            return 0;
        }

        public int Disconnect()
        {
            if (!m_IsConnected)
                return -1;
            if (m_ReceiveThread != null)
            {
                try
                {
                    m_ReceiveThread.Abort();
                    m_ReceiveThread = null;
                }
                catch (SecurityException ex)
                {
                    Console.WriteLine(ex + "\nNo permissions");
                    return -2;
                }
                catch (ThreadStateException ex)
                {
                    Console.WriteLine(ex + "\nThe thread that is being aborted is currently suspended");
                    return -3;
                }
            }
            m_TcpClient.Close();
            m_IsConnected = false;
            m_TcpClient = new TcpClient();
            return 0;
        }

        public int Send(string dataToSend)
        {
            if (!m_TcpClient.Connected)
            {
                if (Connect() != 0)
                    return -1;
            }
            if (ConnectionState() != 0)
            {
                Disconnect();
                return -2;
            }

            NetworkStream dataStream = null;
            byte[] dataBuffer = null;

            try
            {
                dataStream = m_TcpClient.GetStream();
                dataBuffer = System.Text.Encoding.ASCII.GetBytes(dataToSend);
            }
            catch (ObjectDisposedException ex)
            {
                Console.WriteLine(ex + "\ntcpClient has been closed");
                return -3;
            }
            catch (InvalidOperationException ex)
            {
                Console.WriteLine(ex + "\ntcpClient is not connected to a remote host");
                return -4;
            }
            catch (ArgumentNullException ex)
            {
                Console.WriteLine(ex + "\ndataToSend is null");
                return -5;
            }
            catch (System.Text.EncoderFallbackException ex)
            {
                Console.WriteLine(ex + "\nA fallback occurred");
                return -6;
            }
            try
            {
                dataStream.Write(dataBuffer, 0, dataBuffer.Length);
                dataStream.Flush();
            }
            catch (ArgumentNullException ex)
            {
                Console.WriteLine(ex + "\ndataBuffer is null");
                return -7;
            }
            catch (ArgumentOutOfRangeException ex)
            {
                Console.WriteLine(ex + "\none or more arguments are invalid");
                return -8;
            }
            catch (IOException ex)
            {
                Console.WriteLine(ex + "\nThere was a failure when writing to the network");
                return -9;
            }
            catch (ObjectDisposedException ex)
            {
                Console.WriteLine(ex + "\nThe networkstream is closed");
                return -10;
            }
            return 0;
        }

        public int StartReceiving(Func<string, int> receiveMessageHandler)
        {
            if (!m_TcpClient.Connected)
            {
                if (Connect() != 0)
                    return -1;
            }
            if (m_ReceiveThread != null)
                return -2;
            try
            {
                m_ReceiveThread = new Thread(() => ReceiveListener(receiveMessageHandler));
                m_ReceiveThread.Start();
            }
            catch (ArgumentNullException ex)
            {
                Console.WriteLine(ex + "\nnew Thread() parameter is null");
                return -3;
            }
            catch (ThreadStateException ex)
            {
                Console.WriteLine(ex + "\nThread has already been started");
                return -4;
            }
            catch (OutOfMemoryException ex)
            {
                Console.WriteLine(ex + "\nNot enough memory available to start thread");
                return -5;
            }
            return 0;
        }



        private void ReceiveListener(Func<string, int> receiveMessageHandler)
        {
            while (m_TcpClient.Connected)
            {
                if (ConnectionState() != 0)
                    return;
                NetworkStream dataStream = null;
                try
                {   
                    dataStream = m_TcpClient.GetStream();
                }
                catch (ObjectDisposedException ex)
                {
                    Console.WriteLine(ex + "\ntcpClient has been closed");
                }
                catch (InvalidOperationException ex)
                {
                    Console.WriteLine(ex + "\ntcpClient is not connected to a remote host");
                }

                int buffSize = 0;
                byte[] inStream = new byte[4096];
                buffSize = m_TcpClient.ReceiveBufferSize;

                try
                {
                    dataStream.Read(inStream, 0, inStream.Length);
                }
                catch (ArgumentNullException ex)
                {
                    Console.WriteLine(ex + "\nBuffer parameter is null");
                    return;
                }
                catch (ArgumentOutOfRangeException ex)
                {
                    Console.WriteLine(ex + "\nOne or more parameters are invalid");
                }
                catch (IOException ex)
                {
                    Console.WriteLine(ex + "The underlying socket is closed");
                }
                catch (ObjectDisposedException ex)
                {
                    Console.WriteLine(ex + "\ntcpClient has been closed");
                }


                string receivedData = System.Text.Encoding.ASCII.GetString(inStream);
                if (receivedData.EndsWith("\0"))
                    receivedData = receivedData.TrimEnd('\0');
                dataStream.Flush();
                Console.WriteLine("Received: " + receivedData);
                if (receiveMessageHandler(receivedData) != 0)
                    Disconnect();          
            }
        }

        private int ConnectionState()
        {
            if (m_TcpClient.Client.Poll(0, SelectMode.SelectRead))
            {
                byte[] buffer = new byte[1];
                if (m_TcpClient.Client.Receive(buffer, SocketFlags.Peek) == 0)
                    return -1;
            }
            return 0;
        }
    }
}
