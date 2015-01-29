#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define FIFO_SERVER "/tmp/fifoserver"

/*-----------------------------------------------------------------------------------
 普通文件的读写时不会出现阻塞问题，而在管道的读写中却有阻塞的可能，这里的非阻塞标志可
 以在open()函数中设定为O_NONBLOCK
-----------------------------------------------------------------------------------*/
int main(int argc,char** argv)
{
	char r_buf[4096*2];
	int  fd;
	int  r_size;
	int  ret_size;
	
	if (argc != 2){
		printf("usage: ./fifor <len>");
		return 1;
	}
	r_size = atoi(argv[1]);
	printf("requred real read bytes %d\n",r_size);
	memset(r_buf,0,sizeof(r_buf));
	//fd = open(FIFO_SERVER,O_RDONLY|O_NONBLOCK,0);
	fd = open(FIFO_SERVER,O_RDONLY,0);
	if(fd == -1) {
		printf("open %s for read error; errno:%d\n",FIFO_SERVER,errno);
		exit(0);	
	}
	while(1) {
		memset(r_buf,0,sizeof(r_buf));
		ret_size = read(fd,r_buf,r_size);
		if(ret_size==-1) {
			if(errno==EAGAIN) {
				printf("no data avlaible\n");
			}
			printf("read error; errno:%d",errno);
		}
		printf("real read bytes %d\n",ret_size);
		sleep(1);
	}	
	pause();
	unlink(FIFO_SERVER);
}

