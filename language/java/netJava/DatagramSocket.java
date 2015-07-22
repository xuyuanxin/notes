
public class DatagramSocket extends Object implements Closeable
{
/*-----------------------------------------------------------------------------------
 Constructs a datagram socket and binds it to any available port on the local host m-
 achine. 
 ----------------------------------------------------------------------------------*/
DatagramSocket();

/*-----------------------------------------------------------------------------------
 Creates an unbound datagram socket with the specified DatagramSocketImpl. 
 ----------------------------------------------------------------------------------*/
protected DatagramSocket(DatagramSocketImpl impl);

/*-----------------------------------------------------------------------------------
 Constructs a datagram socket and binds it to the specified port on the local host m-
 achine. 
 ----------------------------------------------------------------------------------*/
DatagramSocket(int port);

/*-----------------------------------------------------------------------------------
 Creates a datagram socket, bound to the specified local address. 
 ----------------------------------------------------------------------------------*/
DatagramSocket(int port, InetAddress laddr);

/*----------------------------------------------------------------------------------- 
 Creates a datagram socket, bound to the specified local socket address. 
 ----------------------------------------------------------------------------------*/
DatagramSocket(SocketAddress bindaddr);


/*-----------------------------------------------------------------------------------
 Closes this datagram socket. 
 Any thread currently blocked in receive (java.net.DatagramPacket) upon this socket -
 will throw a SocketException. If this socket has an associated channel then the cha-
 nnel is closed as well.
 ----------------------------------------------------------------------------------*/
public void close();

/*-----------------------------------------------------------------------------------
 Receives a datagram packet from this socket. When this method returns, the         -
 DatagramPacket's buffer is filled with the data received. The datagram packet also -
 contains the sender's IP address, and the port number on the sender's machine.  This 
 method blocks until a datagram is received. The length field of the datagram  packet 
 object contains the length of the received message. If the message is longer than t-
 he packet's length, the message is truncated.

 If there is a security manager,a packet cannot be received if the security manager's 
 checkAccept method does not allow it.
 ----------------------------------------------------------------------------------*/
public void receive(DatagramPacket p) throws IOException ;

/*-----------------------------------------------------------------------------------
 Parameters:
 p - the DatagramPacket to be sent.

 Sends a datagram packet from this socket. The DatagramPacket includes information i-
 ndicating the data to be sent, its length, the IP address of the remote host, and t-
 he port number on the remote host. If there is a security manager, and the socket is 
 not currently connected to a remote address, this method first performs some securi-
 ty checks. First, if p.getAddress().isMulticastAddress() is true, this method  calls 
 the security manager's checkMulticast method with p.getAddress() as its argument. I-
 f the evaluation of that expression is false, this method instead calls the security 
 manager's checkConnect method with arguments p.getAddress().getHostAddress() and   -
 p.getPort(). Each call to a security manager method could result in a              -
 SecurityException if the operation is not allowed.
 ----------------------------------------------------------------------------------*/
public void send(DatagramPacket p) throws IOException;


/*-----------------------------------------------------------------------------------
 Parameters:
 timeout - the specified timeout in milliseconds.

 Enable/disable SO_TIMEOUT with the specified timeout, in milliseconds. With this op-
 tion set to a non-zero timeout, a call to receive() for this DatagramSocket will bl-
 ock for only this amount of time. If the timeout expires, a                        -
 java.net.SocketTimeoutException is raised, though the DatagramSocket is still valid. 
 The option must be enabled prior to entering the blocking operation to have  effect. 
 The timeout must be > 0. A timeout of zero is interpreted as an infinite timeout.
 ----------------------------------------------------------------------------------*/
public void setSoTimeout(int timeout) throws SocketException;

/*-----------------------------------------------------------------------------------
 Retrieve setting for SO_TIMEOUT. 0 returns implies that the option is disabled(i.e., 
 timeout of infinity).
 Returns: the setting for SO_TIMEOUT
 ----------------------------------------------------------------------------------*/
public int getSoTimeout() throws SocketException;



}

