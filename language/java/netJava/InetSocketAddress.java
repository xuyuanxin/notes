
public class InetSocketAddress extends SocketAddress
{
/* Creates a socket address from an IP address and a port number. */
InetSocketAddress(InetAddress addr, int port);

/* Creates a socket address where the IP address is the wildcard address and the port number a specified value. */	
InetSocketAddress(int port);

/* Creates a socket address from a hostname and a port number. */
InetSocketAddress(String hostname, int port);


}


