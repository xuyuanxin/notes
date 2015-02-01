#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#define K 1024
#define WRITELEN 128*K

int main1(void)
{
    int result = -1;
	int fd[2],nbytes;
	pid_t pid;
	char string[WRITELEN] = "hello my pipe 2014! \r\n";
	char readbuffer[10*K] = {0};
	
	int *read_fd = &fd[0];
	int *write_fd = &fd[1];
	
	result = pipe(fd);
	if(-1 == result){
	    printf("fail to create pipe  \r\n");
		return -1;
	}
	
	pid = fork();
	
	if(-1 == pid){
	    printf("fail to fork");
		return -1;
	}
	
	if(0 == pid) {
	    int write_size = WRITELEN;
		result = 0;
		close(*read_fd);
		while(write_size >= 0){
		    result = write(*write_fd,string,write_size);
			if(result > 0){
			    write_size -= result;
				printf("write %d bytes data,the rest is %d bytes \r\n",result,write_size);
			} else {
			    sleep(10);
			}
			return 0;
		}
	} else {
	    close(*write_fd);
		while(1){
		    nbytes = read(*read_fd,readbuffer,sizeof(readbuffer));
			if(nbytes <= 0) {
			    printf("no data to write \r\n");
				break;
			}
			printf("receive %d bytes data:%s \r\n",nbytes,readbuffer);
		}
	}
	return 0;
}
		
		
int main(void)
{
    int result = -1,i;
	int fd[2],nbytes;
	pid_t pid;
    int rfd,wfd;
	char buf[20] = {0};
	result = pipe(fd);
	char *string = "child write!";
	if(-1 == result){
	    printf("fail to create pipe  \r\n");
		return -1;
	}

	rfd = fd[0];
	wfd = fd[1];

	printf("pipe create rfd:%d wfd:%d  \r\n",rfd,wfd);
	
	pid = fork();
	
	if(-1 == pid){
	    printf("fail to fork \r\n");
		return -1;
	}
	
	if(0 == pid) {
		close(rfd);
		result = write(wfd,string,strlen(string)+1);
		printf("child wirte %d bytes:%s\r\n",result,string);
		result = write(wfd,string,strlen(string)+1+10);
		printf("child wirte %d bytes:%s\r\n",result,string);	
	} else {
	    close(wfd);
		if (waitpid(pid, NULL, 0) < 0) {
            printf("wait error\r\n");
        }
        
		while(1) {
		    nbytes = read(rfd,buf,sizeof(buf));
			if(nbytes <= 0){
				printf("father read %d bytes",nbytes);
				break;
			}
			printf("--------> father read %d bytes: \r\n",nbytes);
			for(i = 0; i < nbytes; ++i){
		        printf("%2d: [%3d]-[%c]  \r\n",i,buf[i],buf[i]);
			}	
		}	
	}

	return 0;
}		

/*


        +----------------------+
        |       process        |
        |----------------------|
        |  fd[1]   |   fd[0]   |
        +----|-----------|-----+
             |          /|\                process
-------------|-----------|------------------------------
             |           |                 kernel
            \|/          |        
        +----|-----------|-+
        |        pipe      |
        +------------------+

*/
		
