#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

void cleanup(void *arg)
{
    printf("cleanup: %s\n", (char *)arg);
}

void *thr_fn1(void *arg)
{
	printf("thread 1 start\n");
	pthread_cleanup_push(cleanup, "thread 1 first handler");
	pthread_cleanup_push(cleanup, "thread 1 second handler");
	printf("thread 1 push complete\n");
	
	if (arg)
	    return((void *)1);
	
	pthread_cleanup_pop(0);
	pthread_cleanup_pop(0);
	
	return((void *)1);
}

void *thr_fn2(void *arg)
{
	printf("thread 2 start\n");
	pthread_cleanup_push(cleanup, "thread 2 first handler");
	pthread_cleanup_push(cleanup, "thread 2 second handler");
	printf("thread 2 push complete\n");
	
	if (arg)
	    pthread_exit((void *)2);
	
	pthread_cleanup_pop(0);
	pthread_cleanup_pop(0);
	
	pthread_exit((void *)2);
}

void *thr_fn3(void *arg)
{
	printf("thread 3 start\n");
	pthread_cleanup_push(cleanup, "thread 3 first handler");
	pthread_cleanup_push(cleanup, "thread 3 second handler");
	printf("thread 3 push complete\n");
	
	if (arg)
	    pthread_exit((void *)2);
	
	pthread_cleanup_pop(0);
	pthread_cleanup_pop(1);
	
	pthread_exit((void *)3);
}


/*-----------------------------------------------------------------------------------
 Note that although we never intend to pass zero as an argument to the thread start-up 
 routines, we still need to match calls to pthread_cleanup_pop with the calls to @pthread_cleanup_push;
 otherwise, the program might not compile.

 From the output, we can see that both threads start properly and exit, but that only 
 the second thread's cleanup handlers are called . Thus , if the thread terminates by 
 returning from its start routine, its cleanup handlers are not called, although this 
 behavior varies among implementations. Also note that the cleanup handlers arecalled 
 in the reverse order from which they wereinstalled.

output:
thread 1 start 
thread 2 start 
thread 2 push complete          
thread 1 push complete            
thread 3 start                       
thread 3 push complete               
cleanup: thread 3 first handler          
thread 1 exit code 1   
cleanup: thread 2 second handler              
cleanup: thread 2 first handler  
thread 2 exit code 2
thread 3 exit code 3
-----------------------------------------------------------------------------------*/
int pthread_cleanup_push_eg01(void)
{
	int  err;
	pthread_t  tid1, tid2,tid3;
	void  *tret;
	
	err = pthread_create(&tid1, NULL, thr_fn1, (void *)1);
	if (err != 0)
	    printf("can't create thread 1 %d",err);
	
	err = pthread_create(&tid2, NULL, thr_fn2, (void *)1);
	if (err != 0)
	    printf("can't create thread 2 %d",err);

	err = pthread_create(&tid3, NULL, thr_fn3, (void *)0);
	if (err != 0)
	    printf("can't create thread 3 %d",err);
	
	err = pthread_join(tid1, &tret);
	if (err != 0)
	    printf("can't join with thread 1 %d",err);	
	printf("thread 1 exit code %ld\n", (long)tret);
	
	err = pthread_join(tid2, &tret);
	if (err != 0)
	    printf("can't join with thread 2 %d",err);	
	printf("thread 2 exit code %ld\n", (long)tret);

	err = pthread_join(tid3, &tret);
	if (err != 0)
	    printf("can't join with thread 3 %d",err);	
	printf("thread 3 exit code %ld\n", (long)tret);
	
	exit(0);
}

int main(void)
{
    pthread_cleanup_push_eg01();
	return 0;
}
