using System;
using System.Net;
using System.Net.Sockets;
using System.Text;

class Program
{
    public static void sendaware_req(string cmd,string ip,string udpport){

        /*
        Socket s = new Socket(AddressFamily.InterNetwork, SocketType.Dgram,ProtocolType.Udp);

        IPAddress broadcast = IPAddress.Parse("192.168.43.108");
        //server send other NDS ip format: srvaware-192.168.xxx.xxx.-NDS_UDP_PORT
        //correct: string udpmsg = "srvaware-192.168.43.188-8889";
        string udpmsg = "srvaware-192.168.43.151-8889";

        byte[] sendbuf = Encoding.ASCII.GetBytes(udpmsg);
        IPEndPoint ep = new IPEndPoint(broadcast, 8888);

        s.SendTo(sendbuf, ep);

        Console.WriteLine("Message sent to the broadcast address");
        */

        Socket s = new Socket(AddressFamily.InterNetwork, SocketType.Dgram, ProtocolType.Udp);

        IPAddress broadcast = IPAddress.Parse(ip);
        //server send other NDS ip format: srvaware-192.168.xxx.xxx.-NDS_UDP_PORT
        //correct: string udpmsg = "srvaware-192.168.43.188-8889";
        string udpmsg = cmd + "-" + ip + "-";

        byte[] sendbuf = Encoding.ASCII.GetBytes(udpmsg);
        IPEndPoint ep = new IPEndPoint(broadcast, Convert.ToInt32(udpport));

        s.SendTo(sendbuf, ep);

        Console.WriteLine("UDPSENT MSG \n ");
        
    }

    public static void sendudpmsg(string msg, string ip_target, string udp_port)
    {
        Socket s = new Socket(AddressFamily.InterNetwork, SocketType.Dgram, ProtocolType.Udp);

        IPAddress broadcast = IPAddress.Parse(ip_target);
        //correct sender server msg: string udpmsg = "srvaware-192.168.43.188-host/guest-";
        string udpmsg = msg;

        byte[] sendbuf = Encoding.ASCII.GetBytes(udpmsg);
        IPEndPoint ep = new IPEndPoint(broadcast, Convert.ToInt32(udp_port));

        s.SendTo(sendbuf, ep);

    }
    static void Main(string[] args)
    {
        //sendaware_req("debug-hellllllllooooonkjjjjjjjjjjjjjjjjjjjjrse-", "192.168.43.58", "8888");
        sendudpmsg("debug-dsconnect-ndsmultiip-", "192.168.43.108", "8888");
    }
}