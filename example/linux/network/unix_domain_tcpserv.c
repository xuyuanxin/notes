#include<sys/socket.h>
#include<netinet/in.h>
#include<errno.h>  /*errno*/
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/un.h>
#include"net_pub.h"

int main(int argc, char **argv)
{
	int					listenfd, connfd,ret;
	pid_t				childpid;
	socklen_t			clilen;
	struct sockaddr_un	cliaddr, servaddr;
	void				sig_chld(int);

	listenfd = socket(AF_LOCAL, SOCK_STREAM, 0);
	if(listenfd < 0){
	    printf("unix domain tcp server error socket fail %d",listenfd);
		return 1;
	}

	unlink(UNIXSTR_PATH);
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sun_family = AF_LOCAL;
	strcpy(servaddr.sun_path, UNIXSTR_PATH);

	ret = bind(listenfd, (struct sockaddr *) &servaddr, sizeof(servaddr));
	if(ret < 0){
	    printf("unix domain tcp server error bind fail %d",ret);
		return 1;
	}	

	ret = listen(listenfd, 1024);
	if(ret < 0)
	{
	    printf("unix domain tcp server error listen fail %d",ret);
		return 1;
	}

	signal(SIGCHLD, sig_chld);

	for ( ; ; ) {
		clilen = sizeof(cliaddr);
		if ( (connfd = accept(listenfd, (struct sockaddr *) &cliaddr, &clilen)) < 0) {
			if (errno == EINTR)
				continue;		/* back to for() */
			else
				printf("accept error");
		}

		if ( (childpid = fork()) == 0) {	/* child process */
			close(listenfd);	/* close listening socket */
			str_echo(connfd);	/* process request */
			exit(0);
		}
		close(connfd);			/* parent closes connected socket */
	}
}

