
public class InetAddress extends Object implements Serializable
{

/*-----------------------------------------------------------------------------------
 Parameters:
 host - the specified host, or null.
 Returns:
 an IP address for the given host name.

 Determines the IP address of a host, given the host's name. The host name can either 
 be a machine name, such as "java.sun.com", or a textual representation of its IP ad-
 dress. If a literal IP address is supplied, only the validity of the address  format 
 is checked.

 For host specified in literal IPv6 address, either the form defined in RFC 2732 or -
 the literal IPv6 address format defined in RFC 2373 is accepted. IPv6 scoped addres-
 ses are also supported. See here for a description of IPv6 scoped addresses.

 If the host is null then an InetAddress representing an address of the loopback int-
 erface is returned. See RFC 3330 section 2 and RFC 2373 section 2.5.3.
 ----------------------------------------------------------------------------------*/
public static InetAddress getByName(String host) throws UnknownHostException;

}

