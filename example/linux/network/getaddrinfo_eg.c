#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>
#include <stdio.h>
#include <sys/types.h>
#include <arpa/inet.h>

int getaddrinfo_eg01(int argc, char **argv)
{
    struct addrinfo *answer, hint, *curr;
    char ipstr[16];   

    if (argc != 2) {
        fprintf(stderr, "Usage: %s hostname\n",
        argv[1]);
        exit(1);   
    }

    bzero(&hint, sizeof(hint));
    hint.ai_family = AF_INET;
    hint.ai_socktype = SOCK_STREAM;

    int ret = getaddrinfo(argv[1], NULL, &hint, &answer);
    if (ret != 0) {
        fprintf(stderr,"getaddrinfo: &s\n",
        gai_strerror(ret));
        exit(1);
    }

    for (curr = answer; curr != NULL; curr = curr->ai_next) {
        inet_ntop(AF_INET,&(((struct sockaddr_in *)(curr->ai_addr))->sin_addr),ipstr, 16);
        printf("%s\n", ipstr);
    }

    freeaddrinfo(answer);
    exit(0);
}

/*
$ ./a.exe  www.baidu.com
111.13.100.92
111.13.100.91

http://www.cnblogs.com/sunada2005/p/3304593.html
*/

int getaddrinfo_eg02(int argc, char **argv)
{
    struct addrinfo hints;
    struct addrinfo *res, *cur;
    int ret;
    struct sockaddr_in *addr;
    char ipbuf[16];

    if (argc != 2) {
        printf("Usag...\n");
        exit(1);
    }

    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_INET; /* Allow IPv4 */
    hints.ai_flags = AI_PASSIVE; /* For wildcard IP address */
    hints.ai_protocol = 0; /* Any protocol */
    hints.ai_socktype = SOCK_STREAM;
       
    ret = getaddrinfo(argv[1],NULL,&hints,&res);
    
    if (ret == -1) {
        perror("getaddrinfo");
        exit(1);
    }
    
    for (cur = res; cur != NULL; cur = cur->ai_next) {
        addr = (struct sockaddr_in *)cur->ai_addr;
        printf("%s\n", inet_ntop(AF_INET,&addr->sin_addr, ipbuf, 16));
    }
	
    freeaddrinfo(res);
    exit(0);
}
