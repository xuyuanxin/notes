typedef void __signalfn_t(int);
typedef __signalfn_t __user *__sighandler_t;


struct sigaction {
	__sighandler_t sa_handler;  /* 函数指针 */
	unsigned long sa_flags;
	__sigrestore_t sa_restorer;
	sigset_t sa_mask;		    /* 每个比特代表一种信号，为1表示阻塞此信号 0表示不阻塞*/
};

/*
进程结构体中有关信号的变量
struct task_struct {
struct signal_struct *signal;
struct sighand_struct *sighand;
sigset_t blocked, real_blocked;
sigset_t saved_sigmask;		
struct sigpending pending;
}


sigset_t

sigaction   给一个信号设置处理函数
sigsuspend  等待一个信号
sigemptyset 函数初始化信号集合set,将set 设置为空.


