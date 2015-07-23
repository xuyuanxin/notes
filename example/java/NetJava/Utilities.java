/* http://www.cnblogs.com/cpcpc/archive/2011/09/05/2167889.html */
/*
public static byte[] int2byte(int res) 
{
byte[] targets = new byte[4];

targets[0] = (byte) (res & 0xff);// 最低位 
targets[1] = (byte) ((res >> 8) & 0xff);// 次低位 
targets[2] = (byte) ((res >> 16) & 0xff);// 次高位 
targets[3] = (byte) (res >>> 24);// 最高位,无符号右移。 
return targets; 
}


public static void main(String[] args) {  
        ByteArrayOutputStream baos = new ByteArrayOutputStream();  
        DataOutputStream dos = new DataOutputStream(baos);  
        try {  
            dos.writeByte(4);  
            dos.writeByte(1);  
            dos.writeByte(1);  
            dos.writeShort(217);  
          } catch (IOException e) {  
        e.printStackTrace();  
    }  
  
    byte[] aa = baos.toByteArray();  
    ByteArrayInputStream bais = new ByteArrayInputStream(baos.toByteArray());  
    DataInputStream dis = new DataInputStream(bais);  
  
    try {  
        System.out.println(dis.readByte());  
        System.out.println(dis.readByte());  
        System.out.println(dis.readByte());  
        System.out.println(dis.readShort());  
    } catch (IOException e) {  
        e.printStackTrace();  
    }  
    try {  
        dos.close();  
        dis.close();  
    } catch (IOException e) {  
        e.printStackTrace(); 
    }  
}
*/

/* http://blog.csdn.net/zgyulongfei/article/details/7738970 */
public class Utilities {

	public static byte[] int2byte(int res) 
	{
	    byte[] targets = new byte[4];
	
	    targets[0] = (byte) (res & 0xff);// 最低位 
	    targets[1] = (byte) ((res >> 8) & 0xff);// 次低位 
	    targets[2] = (byte) ((res >> 16) & 0xff);// 次高位 
	    targets[3] = (byte) (res >>> 24);// 最高位,无符号右移。 
	    return targets; 
	}

	public static byte[] int2Bytes(int num) 
	{
		byte[] byteNum = new byte[4];
		for (int ix = 0; ix < 4; ++ix) 
		{
			int offset = 32 - (ix + 1) * 8;
			byteNum[ix] = (byte) ((num >> offset) & 0xff);
		}
		return byteNum;
	}

	public static int bytes2Int(byte[] byteNum) 
	{
		int num = 0;
		for (int ix = 0; ix < 4; ++ix) {
			num <<= 8;
			num |= (byteNum[ix] & 0xff);
		}
		return num;
	}

	public static int bytes2Int(byte[] byteNum, int offset) 
	{
		int num = 0;
		for (int ix = 0; ix < 4; ++ix) {
			num <<= 8;
			num |= (byteNum[ix+offset] & 0xff);
		}
		return num;
	}


	public static byte int2OneByte(int num) 
	{
		return (byte) (num & 0x000000ff);
	}

	public static int oneByte2Int(byte byteNum) 
	{
						//针对正数的int
        return byteNum > 0 ? byteNum : (128 + (128 + byteNum));
	}
		
	public static byte[] long2Bytes(long num) 
	{
		byte[] byteNum = new byte[8];
		for (int ix = 0; ix < 8; ++ix) 
		{
			int offset = 64 - (ix + 1) * 8;
			byteNum[ix] = (byte) ((num >> offset) & 0xff);
		}
		return byteNum;
	}

	public static long bytes2Long(byte[] byteNum) 
	{
		long num = 0;
		for (int ix = 0; ix < 8; ++ix) 
		{
			num <<= 8;
			num |= (byteNum[ix] & 0xff);
		}
		return num;
	}
}



