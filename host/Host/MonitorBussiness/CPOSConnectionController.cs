using System;
using System.Data;
using System.Data.OleDb;
using System.Net;
using System.Net.Sockets;
using System.Collections;
using System.Collections.Generic;
using System.Text;
using System.Threading;

namespace MonitorBussiness
{
    public class StateObject
    {
        // Client socket.
        public Socket workSocket = null;
        // Size of receive buffer.
        public const int BufferSize = 256;
        // Receive buffer.
        public byte[] buffer = new byte[BufferSize];
        // Received data string.
        public StringBuilder sb = new StringBuilder();
    }
    class CPOSConnectionController
    {
        public static ManualResetEvent connectDone;
        public static ManualResetEvent recvDone;
        public static ManualResetEvent isAliveDone;
        public CPOSConnectionController()
        {
            connectDone = new ManualResetEvent(false);
            isAliveDone = new ManualResetEvent(false);
            recvDone    = new ManualResetEvent(false);
        }
        public bool IPIsAlive(String _ip, int port)
        {
            bool retVal = false;
            try
            {
                connectDone = new ManualResetEvent(false);
                isAliveDone = new ManualResetEvent(false);
                recvDone    = new ManualResetEvent(false);
                // (int) 1 gelir
             
                Socket s = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);
                IPAddress ip = IPAddress.Parse(_ip);
                IPEndPoint ipp = new IPEndPoint(ip, port);
                Console.Write("\r\n\t" + _ip);
                //s.Connect(ipp);
                s.BeginConnect(ipp, new AsyncCallback(ConnectCallBack), s);
                if (!connectDone.WaitOne(2000, false)) {
                    //s.EndConnect(null);
                    s.Disconnect(false);
                    s.Shutdown(SocketShutdown.Both);
                    s.Close();
                    Console.WriteLine("\t NOT Connected");
                    return false;
                }
                if (s.Connected == false)
                {
                    Console.WriteLine("\txx NOT Connected");
                    s.Shutdown(SocketShutdown.Both);
                    s.Close();
                    return false;
                }
                Console.WriteLine("\tConnected");
                s.SendTimeout = 1000;
                s.ReceiveTimeout = 1000;

                byte[] arr = Common.ToByteArray(1, 4);
                Console.Write("Send Bytes: ");
                for (int i = 0; i < arr.Length; ++i)
                {
                    Console.Write(arr[i]);
                }
                Console.WriteLine();
                s.Send(arr);
                byte[] buff = new byte[2048];
                if (s.Receive(buff) > 0) {
                    int resp = Common.ToInt(buff, 4);
                    Console.WriteLine("\t Cevap: " + resp);
                    retVal = (resp == 1);
                }
                else {
                    Console.WriteLine("\t Cevap YOK!");
                    retVal = false;
                }
                if (s.Connected) {
                    s.Shutdown(SocketShutdown.Both);
                    s.Close();
                }
                return retVal;
            }
            catch (Exception ex) {
                //System.Windows.Forms.MessageBox.Show(ex.Message);
            }
            return retVal;
        }
        private static void ConnectCallBack(IAsyncResult ar)
        {
            try
            {
                Console.WriteLine("\r\n-----------Connect Callback!");
                Socket client = (Socket)ar.AsyncState;
                client.EndConnect(ar);
                Console.WriteLine("Yesss..." + client.RemoteEndPoint.ToString());
                connectDone.Set();
            }
            catch (Exception e)
            {
                Console.WriteLine(e.ToString());
            }
        }
        private static void SendCallback(IAsyncResult ar)
        {
            try
            {
                Socket client = (Socket)ar.AsyncState;
                int bytesSent = client.EndSend(ar);

                StateObject state = new StateObject();
                state.workSocket = client;

                byte[] buff = new byte[2048];
                client.BeginReceive(buff, 0, buff.Length, 0, new AsyncCallback(ReceiveCallback), state);
            }
            catch (Exception e)
            {
                Console.WriteLine(e.ToString());
            }
        }
        private static void ReceiveCallback(IAsyncResult ar)
        {
            try
            {
                StateObject state = (StateObject)ar.AsyncState;
                Socket client = state.workSocket;
                int bytesRead = client.EndReceive(ar);
                if (bytesRead > 0)
                {
                    state.sb.Append(Encoding.ASCII.GetString(state.buffer, 0, bytesRead));
                    client.BeginReceive(state.buffer, 0, StateObject.BufferSize, 0, new AsyncCallback(ReceiveCallback), state);
                    for (int i = 0; i < state.buffer.Length; ++i)
                    {
                        Console.Write(state.buffer[i]);
                    }
                    Console.WriteLine();
                }
                else
                {
                    recvDone.Set();
                    Console.WriteLine("!");
                    for (int i = 0; i < state.buffer.Length; ++i) {
                        Console.Write(state.buffer[i]);
                    }
                    Console.WriteLine();
                    int resp = Common.ToInt(state.buffer, 4);
                    if (resp == 1) {
                        isAliveDone.Set();
                    }
                }
            }
            catch (Exception e)
            {
                Console.WriteLine(e.ToString());
            }
        }
        public bool IsRestaurantsAlive(ArrayList list)
        {
            try {
                foreach(CMonitedClient client in list) {
                    client.durum = IPIsAlive(client.POSIP, 7000) ? 1 : 0;
                }
            }
            catch (Exception ex) {
            }
            finally {
            }
            return false;
        }
    }
}
