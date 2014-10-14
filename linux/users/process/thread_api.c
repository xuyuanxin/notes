typedef unsigned long int pthread_t; /*linux中这么定义*/


#include <pthread.h>
/*Returns: nonzero if equal, 0 otherwise*/
int pthread_equal(pthread_t tid1,pthread_t tid2);


/*Returns: the thread ID of the calling thread*/
pthread_t pthread_self(void);

/*
@tidp:返回线程ID
@attr:线程属性,为NULL时使用默认属性
@start_rtn:新创建的线程从@start_rtn函数的地址开始运行
@arg:@start_rtn函数的参数
returns: 0 if OK, error number on failure

1 新创建的线程可以访问进程的地址空间
2 继承调用线程的浮点环境和信号屏蔽字,但未决信号集被清除
3 不保证新创建线程和调用线程的执行顺序*/
int pthread_create(pthread_t *restrict tidp, const pthread_attr_t *restrict attr, void *(*start_rtn)(void *), void *restrict arg);

/*If any thread within a process calls exit, _Exit,or _exit,then the entire process terminates. 
  Similarly,when the default action is to terminate the process, a signal sent to a thread will terminate the entire process 
  A single thread can exit in three ways, there by stopping its flow of control, without terminating the entireprocess.
  1 The thread can simply return from the start routine. The return value is the thread's exit code.
  2 The thread can be canceled by another thread in the same process.
  3 The thread can call @pthread_exit.*/
void pthread_exit(void *rval_ptr);

/*
function: 获取线程@thread的返回状态(@rval_ptr指向返回状态)
returns : 0 if OK, error number on failure 

1 调用线程一直阻塞,直到指定线程调用@pthread_exit、从启动例程中返回或者被取消
2 如果从启动例程中返回,@rval_ptr将包含返回码
3 如果线程被取消,有@rval_ptr指定的内存单元就置为 PTHREAD_CANCELED
4 如果对返回状态不感兴趣,可以把@rval_ptr置NULL*/
int pthread_join(pthread_t thread,void **rval_ptr);

/*
function: 取消同一进程中的线程@tid
Returns : 0 if OK, error number on failure
1 @pthread_cancel不等待线程终止,仅仅是提出请求.线程可以忽略这个请求
2 如果线程收到请求退出,相当于调用了pthread_exit(PTHREAD_CANCELED)*/
int pthread_cancel(pthread_t tid);


/*
function:注册"线程清理处理程序",线程退出时调用,执行的顺序与注册顺序相反.
以下三种情况调用清理函数
1 调用pthread_exit时
2 响应取消请求时
3 用非零参数调用pthread_cleanup_pop时,pthread_cleanup_pop(0)仅仅弹出函数不调用.
无论哪种情况都将删除清理函数*/
void pthread_cleanup_push(void (*rtn)(void *), void *arg);
void pthread_cleanup_pop(int execute);

