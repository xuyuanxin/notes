public final class DatagramPacket extends Object
{
/* Constructs a DatagramPacket for receiving packets of length @length. */
DatagramPacket(byte[] buf, int length);

/*----------------------------------------------------------------------------------- 
 Constructs a datagram packet for sending packets of length length to the specified -
 port number on the specified host. 
 -----------------------------------------------------------------------------------*/
DatagramPacket(byte[] buf, int length, InetAddress address, int port);

/* Constructs a DatagramPacket for receiving packets of length length, specifying an offset into the buffer. */
DatagramPacket(byte[] buf, int offset, int length);

/* Constructs a datagram packet for sending packets of length length with offset ioffsetto the specified port number on the specified host. */
DatagramPacket(byte[] buf, int offset, int length, InetAddress address, int port);

/* Constructs a datagram packet for sending packets of length length with offset ioffsetto the specified port number on the specified host. */
DatagramPacket(byte [ ] buf,int length,InetAddress address,int port)(byte[] buf, int offset, int length, SocketAddress address)

/* Constructs a datagram packet for sending packets of length @length to the specified port number on the specified host. */
DatagramPacket(byte[] buf, int length, SocketAddress address);


/* Returns the IP address of the machine to which this datagram is being sent or from which the datagram was received. */
InetAddress	getAddress();


/*-----------------------------------------------------------------------------------
 Returns the data buffer. The data received or the data to be sent starts from the o-
 ffset in the buffer, and runs for length long.
 Returns: the buffer used to receive or send data
 ----------------------------------------------------------------------------------*/
public byte[] getData();

/* Returns the length of the data to be sent or the length of the data received. */
int	getLength();


/* Returns the offset of the data to be sent or the offset of the data received. */
int	getOffset();

/*-----------------------------------------------------------------------------------
 Returns the port number on the remote host to which this datagram is being sent or -
 from which the datagram was received.
 ----------------------------------------------------------------------------------*/
public int getPort();


/*----------------------------------------------------------------------------------- 
 Set the data buffer for this packet. With the offset of this DatagramPacket set to 0, 
 and the length set to the length of buf. 
 -----------------------------------------------------------------------------------*/
void	setData(byte[] buf);

/*-----------------------------------------------------------------------------------
 Parameters:
 buf - the buffer to set for this packet
 offset - the offset into the data
 length - the length of the data and/or the length of the buffer used to receive data

 Set the data buffer for this packet. This sets the data, length and offset of the p-
 acket. 
-----------------------------------------------------------------------------------*/
void	setData(byte[] buf, int offset, int length);

/*-----------------------------------------------------------------------------------
 length - the length to set for this packet.

 Set the length for this packet. The length of the packet is the number of bytes from 
 the packet's data buffer that will be sent, or the number of bytes of the packet's -
 data buffer that will be used for receiving data. The length must be lesser or equal 
 to the offset plus the length of the packet's buffer.
 ----------------------------------------------------------------------------------*/
public void setLength(int length);



}

