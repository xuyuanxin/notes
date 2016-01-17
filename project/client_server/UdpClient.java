import java.io.*;  
import java.net.*;  
  
/* http://sishuok.com/forum/blogPost/list/466.html */  
public class UdpClient 
{  
    private byte[] buffer = new byte[1024];
    private DatagramSocket ds = null;
    private String servip = null;
    private int servport = 0;
   
    public UdpClient() throws Exception 
    {  
        ds = new DatagramSocket();  
    }

    public UdpClient(String serv, int port) throws Exception 
    {
	   ds = new DatagramSocket(servport, InetAddress.getByName(servip));
       servip = serv;
       servport = port;
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
    public final DatagramPacket send(final String msg) throws IOException 
    {
        byte[] msg_str = msg.getBytes("US-ASCII");
		int msg_len = msg.getBytes("US-ASCII").length;
        byte[] data = new byte[8+msg_len];

		System.arraycopy(intToBytes(1),0,data,0,4);
		System.arraycopy(intToBytes(msg_len),0,data,4,4);
		System.arraycopy(msg_str,0,data,8,msg_len);

        DatagramPacket dp = new DatagramPacket(data, data.length, InetAddress.getByName(servip), servport); 
		//DatagramPacket dp = new DatagramPacket(data, data.length); 
        ds.send(dp);
        return dp;  
    }
 
    public final int receive()  throws Exception 
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
		//din.readFully(str,8,4);
		str2 = new String(dp.getData(), 8, dp.getLength()-8, "US-ASCII");

		System.out.printf("mgc1: 0x%x\n",mgc1);
		System.out.printf("mgc2: 0x%x\n",mgc2);
		//System.out.printf("str : %s\n",str.toString());
		System.out.println("str : " + str2);

        return 1;
    }  

    public final int getflags(String str) throws Exception 
    {
        int flags = -1;
        setSoTimeout(2);
        send(str);
        flags = receive();
        return flags;
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
        UdpClient client = new UdpClient("127.0.0.1",9877);
        int flags = -100;
        int cnt = 0;

		//("client").getBytes()
        
		while(true)
		{
            flags = client.getflags("aaaaaaaaaaaaaaaaaaaaaaaaaaa");
			cnt++;
	        if(cnt>1000)
                break;
		}
        //System.out.println("serv ack:" + info);

        client.close();
    }  
}  

