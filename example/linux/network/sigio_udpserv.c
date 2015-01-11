
static int		sockfd;

#define	QSIZE	   8		/* size of input queue */
#define	MAXDG	4096		/* max datagram size */

typedef struct {
  void		*dg_data;		/* ptr to actual datagram */
  size_t	dg_len;			/* length of datagram */
  struct sockaddr  *dg_sa;	/* ptr to sockaddr{} w/client's address */
  socklen_t	dg_salen;		/* length of sockaddr{} */
} DG;
static DG	dg[QSIZE];			/* queue of datagrams to process */
static long	cntread[QSIZE+1];	/* diagnostic counter */

/*-----------------------------------------------------------------------------------
 @iget is the index of the next array entry for the main loop to process, and @iput 
 is the index of the next array entry for the signal handler to store into. @nqueue 
 is the total number of datagrams on the queue for the main loop to process.
-----------------------------------------------------------------------------------*/
static int	iget;		/* next one for main loop to process */
static int	iput;		/* next one for signal handler to read into */
static int	nqueue;		/* # on queue for main loop to process */
static socklen_t clilen;/* max length of sockaddr{} */

static void	sig_io(int);
static void	sig_hup(int);

void dg_echo_sigio(int sockfd_arg, struct sockaddr *pcliaddr, socklen_t clilen_arg)
{
	int			i;
	const int	on = 1;
	sigset_t	zeromask, newmask, oldmask;

	sockfd = sockfd_arg;
	clilen = clilen_arg;

	for (i = 0; i < QSIZE; i++) {	/* init queue of buffers */
		dg[i].dg_data = malloc(MAXDG);
		dg[i].dg_sa = malloc(clilen);
		dg[i].dg_salen = clilen;
	}
	iget = iput = nqueue = 0;

/*-----------------------------------------------------------------------------------
 Signal handlers are established for SIGHUP (which we use for diagnostic purposes) and 
 SIGIO.The socket owner is set using @fcntl and the signal-driven and non-blocking I/O 
 flags are set using @ioctl.
 We mentioned earlier that the O_ASYNC  flag with @fcntl is  the POSIX way to  specify 
 signal-driven I/O, but since most systems do not yet support it,we use @ioctl instead. 
 While most systems do support the O_NONBLOCK flag to set nonblocking,we show the ioctl 
 method here.
-----------------------------------------------------------------------------------*/
	signal(SIGHUP, sig_hup);
	signal(SIGIO, sig_io);
	fcntl(sockfd, F_SETOWN, getpid());
	ioctl(sockfd, FIOASYNC, &on);
	ioctl(sockfd, FIONBIO, &on);

	sigemptyset(&zeromask);		/* init three signal sets */
	sigemptyset(&oldmask);
	sigemptyset(&newmask);
	sigaddset(&newmask, SIGIO);	/* signal we want to block */

	sigprocmask(SIG_BLOCK, &newmask, &oldmask); /* block SIGIO */
	for ( ; ; ) {
		while (nqueue == 0){
			sigsuspend(&zeromask);	/* wait for datagram to process. @zeromask is an */
		}	                        /* empty signal set, this enables all signals*/
		sigprocmask(SIG_SETMASK, &oldmask, NULL); /* 4unblock SIGIO */
		sendto(sockfd, dg[iget].dg_data, dg[iget].dg_len, 0,dg[iget].dg_sa, dg[iget].dg_salen);
		if (++iget >= QSIZE){
			iget = 0;
		}

/*-----------------------------------------------------------------------------------
 We must block the signal while modifying @nqueue since it is shared between the main 
 loop and the signal handler. Also, we need SIGIO blocked when we test @nqueue at the 
 top of the loop.

 An alternate technique is to remove both calls to sigprocmask that are within the for 
 loop,which avoids unblocking the signal and then blocking it later.The problem,however, 
 is that this executes the  entire loop  with the signal  blocked, which  decreases the 
 responsiveness of the  signal  handler. Datagrams should not get lost  because of this 
 change (assuming the socket receive buffer is large enough), but the  delivery of  the 
 signal to the process will be delayed the entire time that the signal is  blocked. One 
 goal when coding applications that perform signal handling  should  be  to  block  the 
 signal for the minimum amount of time.
-----------------------------------------------------------------------------------*/
		sigprocmask(SIG_BLOCK, &newmask, &oldmask);/* 4block SIGIO */
		nqueue--;
	}
}

/*-----------------------------------------------------------------------------------
 The SIGIO signal handler places arriving datagrams onto a queue.This queue is an array 
 of DG structures that we treat as a circular buffer. Each structure contains a pointer 
 to the received datagram,its length,a pointer to a socket address structure containing 
 the protocol address of the client, and the size of the protocol address.

 The problem that we encounter when coding this signal handler is that POSIX signals are 
 normally not queued. This means that, if we are in the signal handler, which guarantees 
 that the signal is blocked,and the signal occurs two more times,the signal is delivered 
 only one more time.

 POSIX provides some real-time signals that are queued, but other  signals such as SIGIO 
 are normally not queued.

 Consider the following scenario: A  datagram  arrives  and the signal is delivered. The 
 signal handler reads the datagram and places it onto the queue  for the main  loop. But 
 while the signal handler is executing, two more datagrams arrive, causing the signal to 
 be generated two more times.Since the signal is blocked,when the signal handler returns, 
 it is called only one more time. The second time the  signal handler executes, it reads 
 the second datagram, but the  third  datagram is left on the socket receive queue. This 
 third datagram will be read only if and  when a  fourth datagram arrives. When a fourth 
 datagram arrives, it is the third datagram that is read and placed on the queue for the
 main loop, not the fourth one.

 Because  signals are  not queued, the  descriptor that is  set for signal-driven I/O is 
 normally  set to nonblocking also. We  then  code our SIGIO  handler to read in a loop, 
 terminating only when the read returns EWOULDBLOCK.
-----------------------------------------------------------------------------------*/
static void sig_io(int signo)
{
	ssize_t		len;
	int			nread;
	DG			*ptr;

	for (nread = 0; ; ) {
		if (nqueue >= QSIZE){
			printf("receive overflow");
			return;
		}

		ptr = &dg[iput];
		ptr->dg_salen = clilen;
		len = recvfrom(sockfd,ptr->dg_data,MAXDG,0,ptr->dg_sa,&ptr->dg_salen);
		if (len < 0) {
			if (errno == EWOULDBLOCK)
				break;		/* all done; no more queued to read */
			else
				printf("recvfrom error");
		}
		ptr->dg_len = len;

		nread++;
		nqueue++;
		if (++iput >= QSIZE)
			iput = 0;

	}
	cntread[nread]++;		/* histogram of # datagrams read per signal */
}

static void sig_hup(int signo)
{
	int		i;

	for (i = 0; i <= QSIZE; i++)
		printf("cntread[%d] = %ld\n", i, cntread[i]);
}

int main(int argc, char **argv)
{
	int					sockfd;
	struct sockaddr_in	servaddr, cliaddr;

	sockfd = socket(AF_INET, SOCK_DGRAM, 0);

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family      = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port        = htons(SERV_PORT);

	bind(sockfd, (struct sockaddr *) &servaddr, sizeof(servaddr));

	dg_echo_sigio(sockfd, (struct sockaddr *) &cliaddr, sizeof(cliaddr));
}

