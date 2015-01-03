#include <signal.h>
#include <stdio.h>

static void sig_usr(int); /* one handler for both signals */

int signal_eg(void)
{
    if (signal(SIGUSR1, sig_usr) == SIG_ERR){
        printf("can¡¯t catch SIGUSR1");
		return -1;
    }	

    if (signal(SIGUSR2, sig_usr) == SIG_ERR){
        printf("can¡¯t catch SIGUSR2");
		return -1;
    }	

    for ( ; ; )
        pause();
}

static void sig_usr(int signo) /* argument is signal number */
{
    if (signo == SIGUSR1)
        printf("received SIGUSR1\n");
    else if (signo == SIGUSR2)
        printf("received SIGUSR2\n");
    else
        printf("received signal %d\n", signo);
}

int main()
{
    int ret;
	
    ret = signal_eg();

	return ret;
}

/************************************************************************************
$ ./a.out &                     start process in background
[1] 7216                        job-control shell prints job number and process ID
$ kill -USR1 7216               send it SIGUSR1
received SIGUSR1
$ kill -USR2 7216               send it SIGUSR2
received SIGUSR2
$ kill 7216                     now send it SIGTERM
[1]+ Terminated ./a.out

When we send the SIGTERM signal, the process is terminated, since it doesn't catch the
signal,and the default action for the signal is termination.
************************************************************************************/

