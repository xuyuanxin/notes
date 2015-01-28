#if 0
#include<errno.h>
#include<sys/stat.h>
#include<fcntl.h>

#define FIFO "/tmp/my_fifo"
/*-----------------------------------------------------------------------------------
 本程序从一个FIFO读数据，并把读到的数据打印到标准输出，如果读到字符“Q”，则退出 
-----------------------------------------------------------------------------------*/
int main(int argc, char** argv)
{
    char buf_r[100];
    int fd;
    int nread;
	
    if((mkfifo(FIFO, O_CREAT) < 0) && (errno != EEXIST))
    {
        printf("mkfifo fail \r\n");
        exit(1);
    }
	
    printf("read data:\r\n");
    fd = open(FIFO, O_RDONLY, 0);
    if(fd == -1)
    {
        perror("open");
        exit(1);
    }

    while(1)
    {
        if((nread = read(fd, buf_r, 100)) == -1)
        {
            if(errno == EAGAIN) printf("no data \r\n");
        }

        if(buf_r[0]=='Q') break;

        buf_r[nread]=0;
        printf("date from fifo：%s\n", buf_r);
        sleep(1);
    }
}
#endif


#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>

#define FIFO_SERVER  "/tmp/fifoserver"

/*-----------------------------------------------------------------------------------
 “S_IFIFO|0666”指明创建一个命名管道且存取权限为0666，即创建者、与创建者同组的用户、
 其他用户对该命名管道的访问权限都是可读可写。 
-----------------------------------------------------------------------------------*/
int main(int argc,char** argv)
{
	int fd,ret;
	char w_buf[4096*2];
	int real_wnum;
	
	memset(w_buf,0,4096*2);
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
	real_wnum = write(fd,w_buf,2048);
	if(real_wnum == -1)
	{
		if(errno == EAGAIN) {
			printf("write to fifo error; try later\n");
		}
	} else {
		printf("real write num is %d\n",real_wnum);
	}
	
	real_wnum = write(fd,w_buf,5000); /* 5000用于测试写入字节大于4096时的非原子性 */

	/* 4096用于测试写入字节不大于4096时的原子性 */
	//real_wnum=write(fd,w_buf,4096); 
		
	if(real_wnum == -1) {
		if(errno == EAGAIN) {
			printf("try later\n");
		}
		printf("write error; errno:%d",errno);
	}	
}

