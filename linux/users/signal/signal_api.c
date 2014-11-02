#define SIG_ERR (void (*)())-1
#define SIG_DFL (void (*)())0
#define SIG_IGN (void (*)())1

#include <signal.h>

/*******************************************************************************
 @signo:信号编号
 @func: 信号处理函数。
         SIG_IGN 忽略此信号(SIGKILL和SIGSTOP不能忽略)
         SIG_DFL 使用默认处理函数
 function: 给信号@signo注册处理函数@func.
 Returns : previous disposition of signal if OK,SIG_ERR on error

 1 不改变信号的处理方式就不能确定当前处理方式
 ******************************************************************************/
void (*signal(int signo,void (*func)(int)))(int);


/*
@seconds:秒
function:经过@seconds秒后产生SIGALRM信号
Returns: 0 or number of seconds until previously set alarm

1 每个进程只能设置一个闹钟,如果调用alarm时,以前设置的闹钟还没有超时,则用@seconds更新闹钟的超时时间。
  上次闹钟的残留值作为本次调用alarm的返回值
2 如果上次闹钟还没超时,而且本次调用@seconds为0,则取消以前的闹钟,残留值作为本次调用alarm的返回值
3 SIGALRM信号的默认动作是终止进程

*/
#include <unistd.h>
unsigned int alarm(unsigned int seconds);

/*
function:挂起进程直至捕获到一个信号
Returns:-1with errno set to EINTR

1 只有当执行了一个信号处理程序并从其返回时,pause才会返回。*/
#include <unistd.h>
int pause(void);



#include <signal.h>
/*
function:清除@set指向的信号集
return: 0 if OK,-1 on error*/
int sigemptyset(sigset_t *set);

/*
function:使信号集@set包含所有的信号
return: 0 if OK,-1 on error*/
int sigfillset(sigset_t *set);

/*
function:把信号@signo添加进信号集@set
return: 0 if OK,-1 on error*/
int sigaddset(sigset_t *set,int signo);

/*
function:从信号集@set中删除信号@signo
return: 0 if OK,-1 on error*/
int sigdelset(sigset_t *set,int signo);

/*Returns: 1 if true, 0 if false,-1 on error*/
int sigismember(const sigset_t *set,intsigno);



#include <signal.h>
/*
@how:指示如何修改当前信号屏蔽字
     SIG_BLOCK 把@set指向的信号集加入当前进程的屏蔽字
     SIG_UNBLOCK
     SIG_SETMASK  把进程的信号屏蔽字设置为@set指向的信号集
@set:结合@how来使用,@set为空时,@how无意义
@oset:若@oset是非空指针,那么进程当前的信号屏蔽字通过@oset返回
Returns: 0 if OK,-1 on error

1 调用@sigprocmask后如果有任何未决的,不再阻塞的信号,则在@sigprocmask返回前至少会将其中一个信号递送给改进程*/
int sigprocmask(int how,const sigset_t *restrict set,sigset_t *restrict oset);

#include <signal.h>
/*
function:通过@set返回进程阻塞的信号
Returns: 0 if OK,-1 on error*/
int sigpending(sigset_t *set);

struct sigaction 
{
    void  (*sa_handler)(int); /* addr of signal handler,or SIG_IGN, or SIG_DFL */
    sigset_t sa_mask; /* additional signals to block */
    int  sa_flags; /* signal options, Figure 10.16 */
    void  (*sa_sigaction)(int, siginfo_t *, void *);/* alternate handler */
};

#include <signal.h>
/*
@signo:the signal number whose action we are examining or modifying.
@act: If the @act pointer is non-null, we are modifying the action. 
@oact: If the @oact pointer is non-null, the system returns the previous action for the signal through the @oact pointer.

function:The @sigaction function allows us to examine or modify (or both) the action associated with a particular signal. 
Returns: 0 if OK,-1 on error

1 sa_mask字段说明了一个信号集,在调用该信号捕捉函数之前,这一信号集要加到进程的信号屏蔽字中。当信号捕捉函数返回时,进程的屏蔽字恢复到原来的值
2 当信号捕捉函数运行时,同时会屏蔽这个信号(@signo)
3 同一种信号多次发生通常不排队,也就是解除阻塞后通常只会调用一次信号捕捉函数，即使这期间发生了很多次这个信号。
4 Once we install an action for a given signal, that action remains installed until we explicitly change it by calling @sigaction.*/
int sigaction(int signo,const struct sigaction *restrict act,struct sigaction *restrict oact);



#include <signal.h>
/*
@sigmask:将进程的信号屏蔽字设置为由@sigmask指向的值。
Returns:-1 with errno set to EINTR
sigsuspend的整个原子操作过程为：
(1) 设置新的mask阻塞当前进程，之后进程挂起；
(2) 收到信号，恢复原先mask；
(3) 调用该进程设置的信号处理函数；
(4) 待信号处理函数返回后，sigsuspend返回。*/
int sigsuspend(const sigset_t *sigmask);


#include <stdlib.h>
/*
function: sends the SIGABRT signal to the caller.(Processes should not ignore this signal.) 
return:This function never returns*/
void abort(void);


#include <unistd.h>
/*
Returns: 0 or number of unslept seconds

This function causes the calling process to be suspended until either
1.  The amount of wall clock time specified by @seconds has elapsed.
2.  A signal is caught by the process and the signal handler returns.
In case 1, the return value is 0. When sleep returns early because of some signal
being caught (case 2), the return value is the number of unslept seconds (the requested
time minus the actual time slept)*/
unsigned int sleep(unsigned int seconds);



