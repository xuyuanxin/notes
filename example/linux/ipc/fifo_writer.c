#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <limits.h> /* PIPE_BUF */

#define FIFO_SERVER  "/tmp/fifoserver"

/*-----------------------------------------------------------------------------------
 “S_IFIFO|0666”指明创建一个命名管道且存取权限为0666，即创建者、与创建者同组的用户、
 其他用户对该命名管道的访问权限都是可读可写。 
-----------------------------------------------------------------------------------*/
int main(int argc,char** argv)
{
	int fd,ret,wlen;
	char w_buf[4096*2];
	int real_wnum;
	
	if (argc != 2){
		printf("usage: ./fifow <len>");
		return 1;
	}	
	memset(w_buf,0,4096*2);
	wlen = atoi(argv[1]);
	ret = mkfifo(FIFO_SERVER,S_IFIFO | 0666);
	if( (ret < 0) && (errno != EEXIST)) {
		printf("cannot create fifoserver\n");
	}			
    //fd = open(FIFO_SERVER,O_WRONLY|O_NONBLOCK,0); /* 设置非阻塞标志 */
	fd = open(FIFO_SERVER,O_WRONLY,0);
	if(fd == -1) {
		if(errno == ENXIO) {
			printf("open error; no reading process\n");
		}	
		printf("open error; errno:%d \n",errno);
		return -1;
	}
	printf("PIPE_BUF:%d wlen:%d\r\n",PIPE_BUF,wlen);
	real_wnum = write(fd,w_buf,wlen);
	if(real_wnum == -1)
	{
		if(errno == EAGAIN) {
			printf("write to fifo error; try later\n");
		}
	} else {
		printf("real write num is %d\n",real_wnum);
	}
}

