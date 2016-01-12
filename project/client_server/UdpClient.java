import java.io.*;  
import java.net.*;  
  
/* http://sishuok.com/forum/blogPost/list/466.html */  
public class UdpClient 
{  
    private byte[] buffer = new byte[1024];
    private DatagramSocket ds = null;
   
    public UdpClient() throws Exception 
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

	public static byte[] intToBytes(int num) 
	{
		byte[] byteNum = new byte[4];
		for (int ix = 0; ix < 4; ++ix) 
		{
			int offset = 32 - (ix + 1) * 8;
			byteNum[ix] = (byte) ((num >> offset) & 0xff);
		}
		return byteNum;
	}	

    /* int strlen str */
    public final DatagramPacket send(final String host, final int port, final String msg) throws IOException 
    {
        byte[] msg_str = msg.getBytes("US-ASCII");
		int msg_len = msg.getBytes("US-ASCII").length;
        byte[] data = new byte[8+msg_len];

		System.arraycopy(intToBytes(1),0,data,0,4);
		System.arraycopy(intToBytes(msg_len),0,data,4,4);
		System.arraycopy(msg_str,0,data,8,msg_len);

        DatagramPacket dp = new DatagramPacket(data, data.length, InetAddress.getByName(host), port);  
        ds.send(dp);
        return dp;  
    }  
 
    public final String receive(final String lhost, final int lport)  throws Exception 
	{
	    byte[] str = new byte[1024];
        String str2 ;
        DatagramPacket dp = new DatagramPacket(buffer, buffer.length);  
        ds.receive(dp);
		System.out.println("client recv from serv, len " + dp.getLength() + 
			               " offset " + dp.getOffset() + " : ");
		
		for (int i = 0; i < dp.getLength(); ++i) 
		{
			System.out.print(dp.getData()[i] + " ");
		}
		System.out.println();

		InputStream in = new ByteArrayInputStream(dp.getData(), dp.getOffset(), dp.getLength());
		DataInputStream din = new DataInputStream(in);
		int mgc1 = din.readInt();
		int mgc2 = din.readInt();
		din.readFully(str,8,4);
		str2 = new String(dp.getData(), 8, dp.getLength()-8, "US-ASCII");

		System.out.printf("mgc1: 0x%x\n",mgc1);
		System.out.printf("mgc2: 0x%x\n",mgc2);
		System.out.printf("str : %s\n",str.toString());
		System.out.println("str : " + str2);

        return "tmp";
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
        UdpClient client = new UdpClient();
        String serverHost = "127.0.0.1";  
        int serverPort = 9877; 

		//("client").getBytes()
        
		//while(true)
		{
		client.send(serverHost, serverPort, "abcdefg");
        String info = client.receive(serverHost, serverPort); 
		}
        //System.out.println("serv ack:" + info);  
    }  
}  

