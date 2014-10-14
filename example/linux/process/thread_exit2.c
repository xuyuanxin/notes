#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

struct foo {
int a, b, c, d;
};

void printfoo(const char *s, const struct foo *fp)
{
	printf("%s", s);
	printf("  structure at 0x%lx\n", (unsigned long)fp);
	printf("  foo.a=%d\n", fp->a);
	printf("  foo.b=%d\n", fp->b);
	printf("  foo.c=%d\n", fp->c);
	printf("  foo.d=%d\n", fp->d);
}

void *thr_fn1(void *arg)
{
	struct foo foo = {1, 2, 3, 4};
	printfoo("thread 1:\n", &foo);
	pthread_exit((void *)&foo);
}

void *thr_fn2(void *arg)
{
    printf("thread 2: ID is %lu\n", (unsigned long)pthread_self());
    pthread_exit((void *)0);
}

int main(void)
{
	int  err;
	pthread_t  tid1, tid2;
	struct foo *fp;
	
	err = pthread_create(&tid1, NULL, thr_fn1, NULL);	
	if (err != 0)
	    printf("can¡¯t create thread 1 %d",err);
	
	err = pthread_join(tid1, (void *)&fp);
	if (err != 0)
	    printf("can¡¯t join with thread 1 %d",err);
	
	sleep(1);
	printf("parent starting second thread\n");

	err = pthread_create(&tid2, NULL, thr_fn2, NULL);
	if (err != 0)
	    printf("can¡¯t create thread 2 %d",err);
	sleep(1);
	
	printfoo("parent:\n", fp);
	
	exit(0);
}

/*
$ ./a.exe
thread 1:
  structure at 0xffffcd50
  foo.a=1
  foo.b=2
  foo.c=3
  foo.d=4
parent starting second thread
thread 2: ID is 25769870304
parent:
  structure at 0xffffcd50
Segmentation fault (core dumped)

