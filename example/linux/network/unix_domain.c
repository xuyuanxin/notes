#include <sys/un.h>
#include <sys/socket.h>	 
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

/*
 creates a Unix domain socket, binds a pathname to it, and then calls @getsockname and 
 prints the bound pathname.
*/
int unix_domain_bind(int argc, char **argv)
{
	int					sockfd;
	socklen_t			len;
	struct sockaddr_un	addr1, addr2;

	if (argc != 2){
		printf("usage: unixbind <pathname>\r\n");
        return -1;
	}	

	sockfd = socket(AF_LOCAL, SOCK_STREAM, 0);

/*
 The pathname that we bind to the socket is the command-line argument. But the @bind 
 will fail if the pathname already exists in the filesystem.Therefore,we call @unlink 
 to delete the pathname,in case it already exists.If it does not exist,unlink returns 
 an error, which we ignore.
*/
	unlink(argv[1]);
	bzero(&addr1, sizeof(addr1));
	addr1.sun_family = AF_LOCAL;
	strncpy(addr1.sun_path, argv[1], sizeof(addr1.sun_path)-1);
	bind(sockfd, (struct sockaddr *) &addr1, SUN_LEN(&addr1));

	len = sizeof(addr2);
	getsockname(sockfd, (struct sockaddr *) &addr2, &len);
	printf("bound name = %s, returned len = %d\n", addr2.sun_path, len);
	
	exit(0);
}


