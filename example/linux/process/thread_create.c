#include <stdio.h>
#include <pthread.h>
#include<stdlib.h>

pthread_t ntid;

void printids(const char *s)
{
    pid_t pid;
    pthread_t tid;
    pid = getpid();
    tid = pthread_self();
    printf("%s pid %lu tid %lu (0x%lx)\n", s, (unsigned long)pid,
           (unsigned long)tid, (unsigned long)tid);
}

void *thr_fn(void *arg)
{
    printids("new thread: ");
    return((void *)0);
}

/*-----------------------------------------------------------------------------------
 The first is the need to sleep in the main thread. If it doesn't sleep, the main th-
 read might exit, thereby terminating the entire process before the new thread gets a 
 chance to run. 

 the main thread stores this ID in @ntid, but the new thread  can't safely use it. If 
 the new thread runs before the main thread returns from calling pthread_create, then 
 the new thread will see the uninitialized contents of ntid instead of the thread ID.

output:
$ gcc -pthread thread_create.c
$ ./a.exe
new thread:  pid 5560 tid 25769870336 (0x600010400)
main thread: pid 5560 tid 25769803872 (0x600000060)
-----------------------------------------------------------------------------------*/
int main(void)
{
    int err;
    err = pthread_create(&ntid, NULL, thr_fn, NULL);
    if (err != 0)
        printf("can't create thread \r\n");
    printids("main thread:");
    sleep(1);
    exit(0);
}
