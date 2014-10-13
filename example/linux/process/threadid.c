//#include "apue.h"
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

pthread_t ntid;

void printids(const char *s)
{
	pid_t		pid;
	pthread_t	tid;

	pid = getpid();
	tid = pthread_self();
	printf("%s pid %lu tid %lu (0x%lx) %lu\n", s, (unsigned long)pid,
	  (unsigned long)tid, (unsigned long)tid,(unsigned long)ntid);
}

void *thr_fn(void *arg)
{
	printids("new thread: ");
	return((void *)0);
}

int main(void)
{
	int		err;
	printf("ntid1=%d\r\n",(unsigned long)ntid);

	err = pthread_create(&ntid, NULL, thr_fn, NULL);
	
	if (err != 0)
		printf("can't create thread");
	
	printids("main thread:");
	printf("\r\nntid2=%d",(unsigned long)ntid);
	printf("\r\nsize = %d %d",sizeof (pthread_t),sizeof(void *));
	
	sleep(1);
	exit(0);
}

/*
1 主线程需要休眠,如果不休眠它可能推出,这样在新线程运行前整个进程已经终止了
2 新线程没用用全局变量ntid获得线程ID,如果新线程在主线程调用pthread_create返回之前就运行了,那么新线程看到的是未经初始化的ntid
*/
