#include<errno.h>
#include<stdio.h>
#include<signal.h>
#include<stdlib.h>

static void sig_int(int);

int main(void)
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

/*
在调用sigsuspend之前只有SIGINT被阻塞，调用sigsuspend后，信号屏蔽字集被临时替换成SIGUSR1，此时可以递送SIGINT，
当SIGINT发生，去执行sig_int，注意：在sig_int里会打出in sig_int: SIGINT SIGUSR1 ，是因为操作系统会自动给正在被递送的信号加入屏蔽字集里
(正在递送的信号也是未决信号，会被添加到信号屏蔽字中），当sig_int返回，sigsuspend也将返回，此时屏蔽字就是SIGINT。
*/

/*
program start:
in critical region: SIGINT
^C
in sig_int: SIGINT SIGUSR1
after return from sigsuspend: SIGINT
program exit:

*/
