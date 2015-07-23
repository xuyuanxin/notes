import java.io.*;  
import java.net.*;  
  
/* http://sishuok.com/forum/blogPost/list/466.html */  
public class UdpClientSocket 
{  
    private byte[] buffer = new byte[1024];
    private DatagramSocket ds = null;
   
    public UdpClientSocket() throws Exception 
    {  
        ds = new DatagramSocket();  
    }  

	public final void setSoTimeout(final int timeout) throws Exception 
	{  
        ds.setSoTimeout(timeout);  
    }  
 
    public final int getSoTimeout() throws Exception 
	{  
        return ds.getSoTimeout();  
    }  
  
    public final DatagramSocket getSocket() 
	{  
        return ds;  
    }  
   
    public final DatagramPacket send(final String host, final int port, final byte[] bytes) throws IOException 
    {  
        DatagramPacket dp = new DatagramPacket(bytes, bytes.length, InetAddress.getByName(host), port);  
        ds.send(dp);  
        return dp;  
    }  
 
    public final String receive(final String lhost, final int lport)  throws Exception 
	{  
        DatagramPacket dp = new DatagramPacket(buffer, buffer.length);  
        ds.receive(dp);
		System.out.println("client recv len " + dp.getLength());
		for (int i = 0; i < dp.getLength(); ++i) {
			System.out.print(dp.getData()[i] + " ");
		}
		System.out.println();		
        String info = new String(dp.getData(), 0, dp.getLength()-4);
		int bytes2int = Utilities.bytes2Int(dp.getData(),dp.getLength()-4);
		System.out.println("bytes2int: " + bytes2int);	

		System.out.println("client recv len " + dp.getLength());
		for (int i = 0; i < dp.getLength(); ++i) {
			System.out.print(dp.getData()[i] + " ");
		}
		System.out.println();			
        return info;  
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
        UdpClientSocket client = new UdpClientSocket();  
        String serverHost = "127.0.0.1";  
        int serverPort = 3344;  
        
		while(true)
		{
		client.send(serverHost, serverPort, ("client").getBytes());
        String info = client.receive(serverHost, serverPort); 
		}
        //System.out.println("serv ack:" + info);  
    }  
}  

