import java.io.IOException;  
import java.net.DatagramPacket;  
import java.net.DatagramSocket;  
import java.net.InetAddress;  
import java.net.InetSocketAddress;  
import java.net.SocketException;  
   
public class UdpServerSocket 
{  
    private byte[] buffer = new byte[1024];
    private DatagramSocket ds = null;
    private DatagramPacket packet = null;
    private InetSocketAddress socketAddress = null;
    private String orgIp;
  
    public UdpServerSocket(String host, int port) throws Exception 
    {  
        socketAddress = new InetSocketAddress(host, port);  
        ds = new DatagramSocket(socketAddress);  
        System.out.println("server startup");  
    }  
      
    public final String getOrgIp() 
	{  
        return orgIp;  
    }  
   
    public final void setSoTimeout(int timeout) throws Exception 
	{  
        ds.setSoTimeout(timeout);  
    }  
  
    public final int getSoTimeout() throws Exception 
	{  
        return ds.getSoTimeout();  
    }  
   
    public final void bind(String host, int port) throws SocketException 
	{  
        socketAddress = new InetSocketAddress(host, port);  
        ds = new DatagramSocket(socketAddress);  
    }  
 
    public final String receive() throws IOException 
    {  
        packet = new DatagramPacket(buffer, buffer.length); 
		
        ds.receive(packet);
        orgIp = packet.getAddress().getHostAddress();
		
        String info = new String(packet.getData(), 0, packet.getLength());
		
        System.out.println("recv from client:" + info);  
        return info;  
    }  

	public static byte[] byteMerger(byte[] byte_1, byte[] byte_2)
	{	
		 byte[] byte_3 = new byte[byte_1.length+byte_2.length];  
		 System.arraycopy(byte_1, 0, byte_3, 0, byte_1.length);  
		 System.arraycopy(byte_2, 0, byte_3, byte_1.length, byte_2.length);  
		 return byte_3;  
	}	

    public final void response(String info) throws IOException 
	{
		int num = 0x11020304;
		System.out.println("num:" + num);

		byte[] int2bytes = Utilities.int2Bytes(num);
		byte[] all;

		//int bytes2int = Utilities.bytes2Int(int2bytes);
		//System.out.println("bytes2int: " + bytes2int);
	
        System.out.println("client ip:" + packet.getAddress().getHostAddress() + 
			               ",port:" + packet.getPort());
		
        DatagramPacket dp = new DatagramPacket(buffer, buffer.length, packet.getAddress(), packet.getPort());  

        all = byteMerger(info.getBytes(),int2bytes);
		System.out.println("setData Len " + all.length);
		dp.setData(all,0,all.length);
		//dp.setData(int2bytes,info.length(),info.length()+4);

		System.out.println("serv send:");

		for (int i = 0; i < all.length; ++i) {
			System.out.print(all[i] + " ");
		}
		System.out.println();

        ds.send(dp);  
    }  
 
    public final void setLength(int bufsize) 
	{  
        packet.setLength(bufsize);  
    }  

    public final InetAddress getResponseAddress() 
    {  
        return packet.getAddress();  
    }
	
    public final int getResponsePort() 
    {  
        return packet.getPort();  
    }  
  
    public final void close() 
	{  
        try {  
            ds.close();  
        } catch (Exception ex) {  
            ex.printStackTrace();  
        }  
    }  

    public static void main(String[] args) throws Exception 
    {  
        String serverHost = "127.0.0.1";  
        int serverPort = 3344;

        UdpServerSocket udpServerSocket = new UdpServerSocket(serverHost, serverPort); 
		
        while (true) 
		{  
            udpServerSocket.receive();  
            udpServerSocket.response("hello client:");  
        }  
    }  
}  

