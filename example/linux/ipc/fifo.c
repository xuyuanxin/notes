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



#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <fcntl.h>
#define FIFO_SERVER  "/tmp/fifoserver"
int main(int argc,char** argv)
{
	int fd;
	char w_buf[4096*2];
	int real_wnum;
	memset(w_buf,0,4096*2);
	if((mkfifo(FIFO_SERVER,O_CREAT|O_EXCL)<0)&&(errno!=EEXIST))
		printf("cannot create fifoserver\n");
		
    fd = open(FIFO_SERVER,O_WRONLY|O_NONBLOCK,0); /* 设置非阻塞标志 */
	//fd=open(FIFO_SERVER,O_WRONLY,0);
	if(fd==-1)
		if(errno==ENXIO)
			printf("open error; no reading process\n");

	real_wnum = write(fd,w_buf,2048);
	if(real_wnum==-1)
	{
		if(errno==EAGAIN)
			printf("write to fifo error; try later\n");
	} else {
		printf("real write num is %d\n",real_wnum);
	}
	
	real_wnum = write(fd,w_buf,5000); /* 5000用于测试写入字节大于4096时的非原子性 */
	
	//real_wnum=write(fd,w_buf,4096); /* 4096用于测试写入字节不大于4096时的原子性 */
		
	if(real_wnum==-1)
		if(errno==EAGAIN)
			printf("try later\n");
}


#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <fcntl.h>
#define FIFO_SERVER "/tmp/fifoserver"
main(int argc,char** argv)
{
	char r_buf[4096*2];
	int  fd;
	int  r_size;
	int  ret_size;
	r_size=atoi(argv[1]);
	printf("requred real read bytes %d\n",r_size);
	memset(r_buf,0,sizeof(r_buf));
	fd=open(FIFO_SERVER,O_RDONLY|O_NONBLOCK,0);
	//fd=open(FIFO_SERVER,O_RDONLY,0);
	//在此处可以把读程序编译成两个不同版本：阻塞版本及非阻塞版本
	if(fd==-1)
	{
		printf("open %s for read error\n");
		exit();	
	}
	while(1)
	{
		
		memset(r_buf,0,sizeof(r_buf));
		ret_size=read(fd,r_buf,r_size);
		if(ret_size==-1)
			if(errno==EAGAIN)
				printf("no data avlaible\n");
		printf("real read bytes %d\n",ret_size);
		sleep(1);
	}	
	pause();
	unlink(FIFO_SERVER);
}

