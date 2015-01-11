#include<sys/socket.h>
#include<netinet/in.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/un.h>
#include"net_pub.h"

int main(int argc, char **argv)
{
	int					sockfd,ret;
	struct sockaddr_un	servaddr;

	sockfd = socket(AF_LOCAL, SOCK_STREAM, 0);
	if(sockfd < 0){
	    printf("unix domain tcp client error socket fail %d",sockfd);
		return 1;
	}

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sun_family = AF_LOCAL;
	strcpy(servaddr.sun_path, UNIXSTR_PATH);

	ret = connect(sockfd, (struct sockaddr *) &servaddr, sizeof(servaddr));
	if(ret < 0)
	{
		printf("unix domain tcp client error connect fail %d",ret);
		return 1;
	}

	str_cli(stdin, sockfd);		/* do it all */

	exit(0);
}
