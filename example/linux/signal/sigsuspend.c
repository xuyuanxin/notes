#include<errno.h>
#include<stdio.h>
#include<signal.h>
#include<stdlib.h>

static void sig_int(int);


int sigsuspend_eg_error()
{
	sigset_t newmask, oldmask;
	sigemptyset(&newmask);
	sigaddset(&newmask, SIGINT);
	
	/* block SIGINT and save current signal mask */
	if (sigprocmask(SIG_BLOCK, &newmask, &oldmask) < 0){
	    printf("SIG_BLOCK error");
	}
	
	/* 这里的代码不会受到SIGINT的影响，如果发生了SIGINT信号，则阻塞*/
	
	/* restore signal mask, which unblocks SIGINT */
	if (sigprocmask(SIG_SETMASK, &oldmask, NULL) < 0){
	    printf("SIG_SETMASK error");
	}
	
/* 如果在这里发生SIGINT信号，pause可能就等不到SIGINT(这个时候还没有调用pasue)。To correct 
 this problem, we need a way to both restore the signal mask and put the process to sleep 
 in a single atomic operation. This feature is provided by the @sigsuspend function.*/

    pause(); /* wait for signal to occur */
	
	/* continue processing */

}

int sigsuspend_eg(void)
{
	sigset_t  newmask, oldmask, waitmask;
	
	print_mask("program start: ");
	
	if (signal(SIGINT, sig_int) == SIG_ERR)
	    printf("signal(SIGINT) error");
	
	sigemptyset(&waitmask);
	sigaddset(&waitmask, SIGUSR1);
	sigemptyset(&newmask);
	sigaddset(&newmask, SIGINT);
	
	/*Block SIGINT and save current signal mask.*/
	if (sigprocmask(SIG_BLOCK, &newmask, &oldmask) < 0)
	    printf("SIG_BLOCK error");
	
	/*Critical region of code.*/
	
	print_mask("in critical region: ");
	
	/*Pause, allowing all signals except SIGUSR1.*/
	if (sigsuspend(&waitmask) != -1)
	    printf("sigsuspend error");
	
	print_mask("after return from sigsuspend: ");
	
	/*Reset signal mask which unblocks SIGINT*/
	if (sigprocmask(SIG_SETMASK, &oldmask, NULL) < 0)
	    printf("SIG_SETMASK error");
	
	/*And continue processing ...*/
	print_mask("program exit: ");
	exit(0);
}

static void sig_int(int signo)
{
    print_mask("\nin sig_int: ");
}

/*******************************************************************************
 在调用sigsuspend之前只有SIGINT被阻塞，调用sigsuspend后，信号屏蔽字集被临时替换成
 SIGUSR1，此时可以递送SIGINT，当SIGINT发生，去执行sig_int，注意：在sig_int里会打出
 in sig_int: SIGINT SIGUSR1 ，是因为操作系统会自动给正在被递送的信号加入屏蔽字集里
 (正在递送的信号也是未决信号，会被添加到信号屏蔽字中），当sig_int返回，sigsuspend也
 将返回，此时屏蔽字就是SIGINT。
*/

/*
program start:
in critical region: SIGINT
^C
in sig_int: SIGINT SIGUSR1
after return from sigsuspend: SIGINT
program exit:

*/

volatile sig_atomic_t quitflag; /* set nonzero by signal handler */

static void sig_int(int signo) /* one signal handler for SIGINT and SIGQUIT */
{
    if (signo == SIGINT)
        printf("\ninterrupt\n");
    else if (signo == SIGQUIT)
        quitflag = 1; /* set flag for main loop */
}


/************************************************************************************
 wait for a signal handler to set a global variable.we catch both the interrupt signal 
 and the quit signal,but want to wake up the main routine only when the quit signal is 
 caught.
************************************************************************************/
int sigsuspend_eg02(void)
{
	sigset_t newmask, oldmask, zeromask;
	
	if (signal(SIGINT, sig_int) == SIG_ERR)
	    printf("signal(SIGINT) error");
	
	if (signal(SIGQUIT, sig_int) == SIG_ERR)
        printf("signal(SIGQUIT) error");
	
	sigemptyset(&zeromask);
	sigemptyset(&newmask);
	sigaddset(&newmask, SIGQUIT);
	
	/* Block SIGQUIT and save current signal mask. */
	if (sigprocmask(SIG_BLOCK, &newmask, &oldmask) < 0)
	    printf("SIG_BLOCK error");
	
	while (quitflag == 0)
	    sigsuspend(&zeromask);
	
	/* SIGQUIT has been caught and is now blocked; do whatever. */
	quitflag = 0;
	
	/* Reset signal mask which unblocks SIGQUIT. */
	if (sigprocmask(SIG_SETMASK, &oldmask, NULL) < 0)
	    printf("SIG_SETMASK error");
	
	exit(0);
}

