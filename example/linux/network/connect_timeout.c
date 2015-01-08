/* include connect_timeo */
#include	"unp.h"

static void	connect_alarm(int);

/************************************************************************************
 The first three arguments are the three required by connect and the fourth argument 
 is the number of seconds to wait.

 One point to make with this example is that we can always reduce the timeout period 
 for a connect using this technique,but we cannot extend the kernel's existing timeout. 
 That is, on a Berkeley-derived kernel the timeout for a connect is normally 75 seconds. 
 We can specify a smaller value for our function,say 10,but if we specify a larger value, 
 say 80, the connect itself will still time out after 75 seconds.

 Another point with this example is that we use the interruptibility of the system call 
 (connect) to return before the kernel's time limit expires. This is fine when we perform 
 the system call and can handle the EINTR error return. But in Section 29.7, we will 
 encounter a library function that performs the system call, and the library function 
 reissues the system call when EINTR is returned. We can still use SIGALRM in this scenario, 
 but we will see in Figure 29.10 that we also have to use sigsetjmp and siglongjmp to get 
 around the library's ignoring of EINTR.

 Although this example is fairly simple, signals are quite difficult to use correctly 
 with multithreaded programs (see Chapter 26). So, the technique shown here is only 
 recommended for single-threaded programs.
************************************************************************************/
int connect_timeo(int sockfd, const struct sockaddr *saptr, socklen_t salen, int nsec)
{
	Sigfunc	*sigfunc;
	int		n;

/************************************************************************************
 A signal handler is established for SIGALRM. The current signal handler (if any) is 
 saved, so we can restore it at the end of the function.The alarm clock for the process 
 is set to the number of seconds specified by the caller. The return value from alarm 
 is the number of seconds currently remaining in the alarm clock for the process (if 
 one has already been set by the process) or 0 (if there is no current alarm). In the 
 former case we print a warning message since we are wiping out that previously set alarm.
************************************************************************************/
	sigfunc = signal(SIGALRM, connect_alarm);
	if (alarm(nsec) != 0)
		printf("connect_timeo: alarm was already set");

/************************************************************************************
 connect is called and if the function is interrupted (EINTR), we set the errno value 
 to ETIMEDOUT instead. The socket is closed to prevent the three-way handshake from 
 continuing.The alarm is turned off by setting it to 0 and the previous signal handler 
 ( if any ) is restored. The signal handler just returns, assuming this return will 
 interrupt the pending connect, causing connect to return an error of EINTR. Recall 
 our signal function (Figure 5.6) that does not set the SA_RESTART flag when the 
 signal being caught is SIGALRM.
************************************************************************************/
	if ( (n = connect(sockfd, saptr, salen)) < 0) {
		close(sockfd);
		if (errno == EINTR)
			errno = ETIMEDOUT;
	}
	alarm(0);					/* turn off the alarm */
	signal(SIGALRM, sigfunc);	/* restore previous signal handler */

	return(n);
}

static void connect_alarm(int signo)
{
	return;		/* just interrupt the connect() */
}

