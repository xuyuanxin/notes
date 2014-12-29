#include<sys/socket.h>
#include<netinet/in.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"net_pub.h"



void str_cli_v3(FILE *fp, int sockfd)
{
    int     maxfdp1, stdineof;
    fd_set  rset;
    char    buf[MAXLINE];
    int     n;
    stdineof = 0;
    FD_ZERO(&rset);
	
    for ( ; ; ) 
	{
        if (stdineof == 0)
            FD_SET(fileno(fp), &rset);
		
        FD_SET(sockfd, &rset);
        maxfdp1 = max(fileno(fp), sockfd) + 1;
		
        if(select(maxfdp1, &rset, NULL, NULL, NULL) < 0)
		{
			printf("tcp client select error\r\n");
		}

        if (FD_ISSET(sockfd, &rset)) /* socket is readable */
		{  
            if ( (n = read(sockfd, buf, MAXLINE)) == 0) 
			{
                if (stdineof == 1)
                    return;       /* normal termination */
                else
                    printf("str_cli: server terminated prematurely");
            }
			else if(n < 0)
			{
			    printf("\r\ntcp client error read 1");
			}
			
            if(n != write(fileno(stdout), buf, n))
				printf("\r\ntcp client error write 1");
        }
		
        if (FD_ISSET(fileno(fp), &rset))  /* input is readable */
		{ 
            if ( (n = read(fileno(fp), buf, MAXLINE)) == 0) 
			{
			    /*读到EOF不立即退出,是因为此时在套接字里可能还有数据没有读取*/
                stdineof = 1;
                if(shutdown(sockfd, SHUT_WR) < 0)
					printf("\r\ntcp client error shutdown");  /* send FIN */
				
                FD_CLR(fileno(fp), &rset);
                continue;
            }
			else if(n < 0)
			{
			    printf("\r\ntcp client error read 2 ");
			}
			
            if(n != write(fileno(stdout), buf, n))
				printf("\r\ntcp client error write 2 ");
        }
    }
}



/*
在标准输入或套接字上select可读条件
标准输入:数据或EOF
套接字  :RST 数据 FIN
Three conditions are handled with the socket:
1 If the peer TCP sends data, the socket becomes readable and read returns greater than 0 (i.e., the number of bytes of data).
2 If the peer TCP sends a FIN (the peer process terminates), the socket becomes readable and read returns 0 (EOF).
3 If the peer TCP sends an RST (the peer host has crashed and rebooted), the socket becomes readable, read returns –1, 
  and errno contains the specific error code.
*/
void str_cli_v2(FILE *fp, int sockfd)
{
     int     maxfdp1;
	 int     ready_nums;
     fd_set  rset;
     char    sendline[MAXLINE], recvline[MAXLINE];

     FD_ZERO(&rset);
     for ( ; ; )  
	 {
         FD_SET(fileno(fp), &rset);
         FD_SET(sockfd, &rset);
         maxfdp1 = max(fileno(fp), sockfd)  +  1;
		 
         ready_nums = select(maxfdp1,  &rset,  NULL,  NULL,  NULL);

		 if(ready_nums < 0)
		 {
		     printf("tcp client select error\r\n");
			 //return;
		 }

         if (FD_ISSET(sockfd,  &rset))  /* socket is readable */
		 {  
             if (x_readline(sockfd, recvline, MAXLINE) == 0)
                 printf("str_cli: server terminated prematurely");
			 
			 if (fputs(recvline, stdout) == EOF)
		         printf("\r\ntcp client error: str_cli -> fputs");
         }

         if (FD_ISSET(fileno(fp), &rset)) /*  input is readable */ 
		 { 
		     /*这个地方有个问题:当读到EOF时,立即退出了,但此时可能套接字里还有数据没有读.*/
             if (fgets(sendline, MAXLINE, fp) == NULL)
                 return;          /* all done */
			 
			 if(strlen(sendline) != x_writen(sockfd, sendline, strlen(sendline)))
			    printf("\r\ntcp client error:str_cli -> x_writen");
         }
     }
}

/*V1版本有个问题:当套接字上发生事情的时候,客户端可能阻塞与fgets调用*/
void str_cli_v1(FILE *fp, int sockfd)
{
	char	sendline[MAXLINE], recvline[MAXLINE];	
	char	*read_string = NULL;

    do
    {
        /*cli_close_normal 1(客户端发起正常终止):当客户端键入EOF,fgets返回NULL,则客户端调用exit退出*/
	    read_string = fgets(sendline, MAXLINE, fp);

	    if( read_string == NULL && ferror(fp))
		    printf("\r\ntcp client error:str_cli -> fgets");

		if(NULL != read_string)
		{
		    /*假设服务器异常终止,发送一个FIN.客户端收到FIN后返回ack.此时客户端可
		       能阻塞在fgets,当获得字符后,走到这里调用write发往服务器,这个消息可
		       以发过去因为TCP只关闭了一半.服务器收到消息后,由于先前打开的那个套
		       接字的进程已经终止,于是响应一个RST(第一次写引发RST,第二次写产生
		       SIGPIPE信号,写返回EPIPE错误).然而客户进程看不到这个RST,因为它在调
		       用write后立即调用readline,并且由于上面的FIN报文,所以readline立即
		       返回0(EOF)
			   The problem in this example is that the client is blocked in the 
			   call to @fgets when the FIN arrives on the socket. The client is 
			   really working with two descriptors—the socket and the user input
			   —and instead of blocking on input from only one of the two sources 
			   (as str_cli is currently coded), it should block on input from either 
			   source. Indeed, this is one purpose of the @select and @poll functions, 
			   which we will describe in Chapter 6. When we recode the str_cli 
			   function in Section 6.4, as soon as we kill the server child, the 
			   client is notified of the received FIN.*/
			if(strlen(sendline) != x_writen(sockfd, sendline, strlen(sendline)))
			    printf("\r\ntcp client error:str_cli -> x_writen");

		    if (x_readline(sockfd, recvline, MAXLINE) == 0)
			    printf("tcp client error:str_cli server terminated prematurely");

			if (fputs(recvline, stdout) == EOF)
				printf("\r\ntcp client error: str_cli -> fputs");
		}
    }while(NULL != read_string);

    #if 0
	while (Fgets(sendline, MAXLINE, fp) != NULL) 
	{

		Writen(sockfd, sendline, strlen(sendline));

		if (Readline(sockfd, recvline, MAXLINE) == 0)
			err_quit("str_cli: server terminated prematurely");

		Fputs(recvline, stdout);
	}
	#endif
}


/*./cli.exe 192.168.1.101*/
int main(int argc, char **argv)
{
	int					sockfd;
	int                 ret = 0;
	struct sockaddr_in	servaddr;

	if (argc != 2)
	{
		printf("usage: tcpcli <IPaddress>");
		return 1;
	}

	sockfd = socket(AF_INET,SOCK_STREAM, 0);
	
	if(sockfd < 0)
	{
	    printf("tcp client error socket fail %d",sockfd);
		return 1;
	}

	memset(&servaddr,0, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(SERV_PORT);
	inet_pton(AF_INET, argv[1], &servaddr.sin_addr);

    /* The foreign IP address and foreign port must be specified by the client 
        in the call to @connect. The two local values are normally chosen by the 
        kernel as part of the @connect function. The client has the option of 
        specifying either or both of the local values, by calling @bind before 
        @connect, but this is not common.the client can obtain the two local 
        values chosen by the kernel by calling @getsockname after the connection 
        is established.*/

    /*客户端connect发起三次握手,收到ack后返回(第二次握手),而服务器要第三个握手才返回*/
	ret = connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr));
	if(ret < 0)
	{
		printf("tcp client error connect fail %d",ret);
		return 1;
	}

	str_cli_v1(stdin, sockfd);		/* do it all */
	
	/*cli_close_normal 2:exit关闭打开的描述符,当关闭套接字时,客户端发送一个FIN给
	  服务器,收到服务器的ack后,TCP前半部分关闭至此服务器套接字处于CLOSE_WAIT状态,
	  客户端套接字处于FIN_WAIT_2状态*/

    /*close decrements the descriptor's reference count and closes the socket only if the count reaches 0. 
	  close terminates both directions of data transfer, reading and writing. */
	exit(0);
}

