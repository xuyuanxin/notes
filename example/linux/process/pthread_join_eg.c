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
    printf("thread 1 returning\n");
    return((void *)1);
}

void *thr_fn2(void *arg)
{
    printf("thread 2 exiting\n");
    pthread_exit((void *)2);
}

void *thr_fn3(void *arg)
{
	struct foo foo = {1, 2, 3, 4};
	printfoo("thread 1:\n", &foo);
	pthread_exit((void *)&foo);
}

void *thr_fn4(void *arg)
{
    printf("thread 2: ID is %lu\n", (unsigned long)pthread_self());
    pthread_exit((void *)0);
}


/*-----------------------------------------------------------------------------------
 As we can see, when a thread exits by calling @pthread_exitor by simply returning f-
 rom the start routine, the exit status can  be obtained by another thread by calling 
 @pthread_join

output:
$ ./a.exe
thread 1 returning
thread 2 exiting
thread 1 exit code 1
thread 2 exit code 2
-----------------------------------------------------------------------------------*/
int pthread_join_eg01(void)
{
    int  err;
    pthread_t  tid1, tid2;
    void  *tret;
    
    err = pthread_create(&tid1, NULL, thr_fn1, NULL);
    if (err != 0)
        printf("can't create thread 1 %d",err);
    
    err = pthread_create(&tid2, NULL, thr_fn2, NULL);
    if (err != 0)
        printf("can't create thread 2 %d",err);
    
    err = pthread_join(tid1, &tret);
    if (err != 0)
        printf("can't join with thread 1 %d",err);
    
    printf("thread 1 exit code %ld\n", (long)tret);
    
    err = pthread_join(tid2, &tret);
    if (err != 0)
        printf("can't join with thread 2 %d",err);
    
    printf("thread 2 exit code %ld\n", (long)tret);
    
    return 0;
}

/*-----------------------------------------------------------------------------------
 The typeless pointer passed to @pthread_create and @pthread_exit can be used to pass 
 more than a single value. The pointer can be used  to pass the address of a structure 
 containing more complex information.Be careful that the memory used for the structure 
 is still valid when the caller has completed. If the structurewas allocated on the c-
 aller's stack, for example, the memory contents might have changed by the time the s-
 tructure is used. If a thread allocates a structure on its stack and passes a pointer 
 to this structure to @pthread_exit, then the stack might  be destroyed and its memory
 reused for something else by the time the caller of @pthread_join tries to use it.

output:
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
-----------------------------------------------------------------------------------*/
int pthread_join_eg02(void)
{
	int  err;
	pthread_t  tid1, tid2;
	struct foo *fp;
	
	err = pthread_create(&tid1, NULL, thr_fn3, NULL);	
	if (err != 0)
	    printf("can't create thread 1 %d",err);
	
	err = pthread_join(tid1, (void *)&fp);
	if (err != 0)
	    printf("can't join with thread 1 %d",err);
	
	sleep(1);
	printf("parent starting second thread\n");

	err = pthread_create(&tid2, NULL, thr_fn4, NULL);
	if (err != 0)
	    printf("can't create thread 2 %d",err);
	sleep(1);
	
	printfoo("parent:\n", fp);
	
	return 0;
}


int main()
{
    pthread_join_eg01();
	pthread_join_eg02();

	return 0;

}


