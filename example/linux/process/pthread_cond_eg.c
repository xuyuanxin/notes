#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <errno.h>  /*errno*/


pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
pthread_mutex_t mymutex2 ;
pthread_cond_t mycond2 ;
pthread_mutex_t mymutex3 ;
pthread_cond_t mycond3 ;

void *thread1(void *);
void *thread2(void *);

int i=1;

void maketimeout(struct timespec *tsp, long seconds)
{
    struct timeval now;

    gettimeofday(&now, NULL); /* get the current time */
    tsp->tv_sec = now.tv_sec;
    tsp->tv_nsec = now.tv_usec * 1000; /* usec to nsec */

    tsp->tv_sec += seconds; /* add the offset to get timeout value */
}

void *thread1(void *junk)
{
    for(i=1;i<=6;i++)
    {
        pthread_mutex_lock(&mutex);
		printf("thread1: lock %d\n", __LINE__);
        if(i%3==0){
			printf("thread1:signal 1  %d\n", __LINE__);
            pthread_cond_signal(&cond);
			printf("thread1:signal 2  %d\n", __LINE__);
			sleep(1);
		}
        pthread_mutex_unlock(&mutex);
		printf("thread1: unlock %d\n\n", __LINE__);
		sleep(1);
	}
}

void *thread2(void *junk)
{
    while(i<6)
    {
        pthread_mutex_lock(&mutex);
		printf("thread2: lock %d\n", __LINE__);
		if(i%3!=0){
			printf("thread2: wait 1  %d\n", __LINE__);
            pthread_cond_wait(&cond,&mutex);
			printf("thread2: wait 2  %d\n", __LINE__);
		}
        pthread_mutex_unlock(&mutex);
		printf("thread2: unlock %d\n\n", __LINE__);
		sleep(1);
	}
}

void *thread3(void *junk)
{
    printf("thread3: sleep 1s \n");
	sleep(1);
    pthread_mutex_lock(&mymutex2);
	printf("thread3: locked and signaling\n");
    pthread_cond_signal(&mycond2);	
    pthread_mutex_unlock(&mymutex2);
	printf("thread3: unlocked \n");
}

void *thread4(void *junk)
{
    pthread_mutex_lock(&mymutex2);
	printf("thread4: locked and wait cond...\n");
    pthread_cond_wait(&mycond2,&mymutex2);
    printf("thread4: condition to be true \n");
    pthread_mutex_unlock(&mymutex2);
	printf("thread4: unlocked \n");	
}

void *thread5(void *junk)
{
    int ret;
    printf("thread5: sleep 1s sleeping... \n");
	sleep(1);
    pthread_mutex_lock(&mymutex3);
	printf("thread5: locked, cond signaling... \n");
    ret = pthread_cond_signal(&mycond3);	
    pthread_mutex_unlock(&mymutex3);
	printf("thread5: unlocked cond ret:%d\n",ret);
}

void *thread6(void *junk)
{
	struct timespec timeout;
	int ret;

    printf("thread6: sleep 2s sleeping... \n");
	sleep(2);

    pthread_mutex_lock(&mymutex3);
	printf("thread6: locked and wait cond(timeout 3s)... \n");
	maketimeout(&timeout,3);
	ret = pthread_cond_timedwait(&mycond3,&mymutex3,&timeout);
	if(0 == ret) {
		printf("thread6: condition to be true \n");
	} else {
	    if(ETIMEDOUT == ret)
			printf("thread6: condition timeout \n");
	}
    pthread_mutex_unlock(&mymutex3);
	printf("thread6: unlocked cond ret:%d\n",ret);	
}

/*-----------------------------------------------------------------------------------
-----------------------------------------------------------------------------------*/
int pthread_cond_eg01(void)
{
    pthread_t t_a;
    pthread_t t_b;
    pthread_create(&t_a,NULL,thread1,(void *)NULL);
    pthread_create(&t_b,NULL,thread2,(void *)NULL); 
    pthread_join(t_a, NULL);
    pthread_join(t_b, NULL);
    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&cond);
	return 0;
}

/*
output:
----> pthread cond test 2                                                                                                           
thread3: sleep 1s                                                                                                                   
thread4: locked and wait cond...                                                                                                    
thread3: locked and signaling                                                                                                       
thread3: unlocked                                                                                                                   
thread4: condition to be true                                                                                                       
thread4: unlocked
*/
int pthread_cond_eg02(void)
{
    pthread_t t_a;
    pthread_t t_b;
	
	printf("\n----> pthread cond test 2 \n");
    pthread_mutex_init(&mymutex2, NULL);
    pthread_cond_init(&mycond2, NULL);	
    pthread_create(&t_a,NULL,thread3,(void *)NULL);
    pthread_create(&t_b,NULL,thread4,(void *)NULL); 
    pthread_join(t_a, NULL);
    pthread_join(t_b, NULL);
    pthread_mutex_destroy(&mymutex2);
    pthread_cond_destroy(&mycond2);
	return 0;
}

/*
output:
----> pthread cond test 3                                                                                                           
thread5: sleep 1s sleeping...                                                                                                       
thread6: sleep 2s sleeping...                                                                                                       
thread5: locked, cond signaling...                                                                                                  
thread5: unlocked cond ret:0                                                                                                        
thread6: locked and wait cond(timeout 3s)...                                                                                        
thread6: condition timeout                                                                                                          
thread6: unlocked cond ret:110
*/
int pthread_cond_eg03(void)
{
    pthread_t t_a;
    pthread_t t_b;
	printf("\n----> pthread cond test 3 \n");
    pthread_mutex_init(&mymutex3, NULL);
    pthread_cond_init(&mycond3, NULL);	
    pthread_create(&t_a,NULL,thread5,(void *)NULL);
    pthread_create(&t_b,NULL,thread6,(void *)NULL); 
    pthread_join(t_a, NULL);
    pthread_join(t_b, NULL);
    pthread_mutex_destroy(&mymutex3);
    pthread_cond_destroy(&mycond3);
	return 0;
}

int main()
{
	pthread_cond_eg02();
    pthread_cond_eg03();
	return 0;
}


