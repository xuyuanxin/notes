#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<fcntl.h>

#define BUFSIZE 1024

int popen_eg_01(char *cmd)
{
    FILE *fp;
    char buf[BUFSIZE];
    buf[BUFSIZE]='\0';
	int ret;

	printf("\r\n---- popen_eg_01 run ---- \r\n");

	fp=popen(cmd,"r");

	printf("popen ret:%p\r\n",fp);
	
    if(fp == NULL){
        perror("popen");
		printf("popen error\r\n");
    }
	
    while((fgets(buf,BUFSIZE,fp))!=NULL)
        printf("%s",buf);
	
    ret = pclose(fp);

	printf("pclose ret:%d",ret);
	
    return 0;
}

int main()
{
	popen_eg_01("ls -l");
	popen_eg_01("lws -l");
	return 0;
}


