#include <netdb.h>

struct hostent {
   char  *h_name;       /* official (canonical) name of host .表示的是主机的规范名。例如www.google.com的规范名其实是www.l.google.com。*/
   char **h_aliases;    /* pointer to array of pointers to alias names.
                              表示的是主机的别名.www.google.com就是google他自己的别名。有的时候，有的主机可能有好几个别名，
                              这些，其实都是为了易于用户记忆而为自己的网站多取的名字。*/
   int    h_addrtype;   /* host address type: AF_INET .表示的是主机ip地址的类型，到底是ipv4(AF_INET)，还是pv6(AF_INET6)*/
   int    h_length;     /* length of address: 4. 表示的是主机ip地址的长度*/
   char **h_addr_list;  /* ptr to array of ptrs with IPv4 addrs . 表示的是主机的ip地址，注意，这个是以网络字节序存储的。*/
};

#define HOST_NOT_FOUND
#define TRY_AGAIN
#define NO_RECOVERY
#define NO_DATA    /* specified name is valid, but it does not have an A record*/

/* 
  Returns: non-null pointer if OK,NULL on error with h_errno set
  
  1 it returns a pointer to a hostent structure that contains all the IPv4 addresses for the host. */
struct hostent *gethostbyname (const char *hostname);
	 
	 
#include <netdb.h>
/*@addr：指向网络字节顺序地址的指针。
  @len： 地址的长度，在AF_INET类型地址中为4。
  @type：地址类型，应为AF_INET。
  @Returns: non-null pointer if OK, NULL on error with h_errno set */	  
struct hostent *gethostbyaddr (const char *addr, socklen_t len, int family);
	  
	  
#include <netdb.h>
struct servent {
  char   *s_name;      /* official service name */
  char  **s_aliases;   /* alias list */
  int     s_port;      /* port number, network-byte order */
  char   *s_proto;     /* protocol to use */
};
{
struct servent *sptr;

sptr = getservbyname("domain", "udp"); /* DNS using UDP */
sptr = getservbyname("ftp", "tcp");    /* FTP using TCP */
sptr = getservbyname("ftp", NULL);     /* FTP using TCP */
sptr = getservbyname("ftp", "udp");    /* this call will fail */
}
/*Returns: non-null pointer if OK, NULL on error */	   
struct servent *getservbyname (const char *servname, const char *protoname);
	   
	   
int getaddrinfo( const char *hostname, const char *service, 
	                const struct addrinfo *hints, struct addrinfo **result );

