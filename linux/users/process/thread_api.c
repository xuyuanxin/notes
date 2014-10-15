typedef unsigned long int pthread_t; /*linux中这么定义*/
/*
在任何一个时间点上，线程是可结合的（joinable）或者是分离的（detached）。
一个可结合的线程能够被其他线程收回其资源和杀死。在被其他线程回收之前，它的存储器资源（例如栈）是不释放的。
相反，一个分离的线程是不能被其他线程回收或杀死的，它的存储器资源在它终止时由系统自动释放。

创建一个线程默认的状态是joinable, 如果一个线程结束运行但没有被join,则它的状态类似于进程中的Zombie Process,
即还有一部分资源没有被回收（退出状态码），所以创建线程者应该调用pthread_join来等待线程运行结束，
并可得到线程的退出代码，回收其资源（类似于wait,waitpid).但是调用pthread_join(pthread_id)后，
如果该线程没有运行结束，调用者会被阻塞，在有些情况下我们并不希望如此，
比如在Web服务器中当主线程为每个新来的链接创建一个子线程进行处理的时候，
主线程并不希望因为调用pthread_join而阻塞（因为还要继续处理之后到来的链接），
这时可以在子线程中加入代码
pthread_detach(pthread_self())
或者父线程调用
pthread_detach(thread_id)（非阻塞，可立即返回）
这将该子线程的状态设置为detached,则该线程运行结束后会自动释放所有资源。
*/

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
4 如果对返回状态不感兴趣,可以把@rval_ptr置NULL
5 当函数@pthread_join返回时，被等待线程@thread的资源被收回。*/
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

/*
By default, a thread's termination status is retained until we call @pthread_join for that thread. 
A thread's underlying storage can be reclaimed immediately on termination if the thread has been detached.
After a thread is detached, we can't use the @pthread_join function to wait for its termination status, 
because calling @pthread_join for a detached thread results in undefined behavior.
We can detach a thread by calling @pthread_detach.

Returns: 0 if OK, error number on failure*/
int pthread_detach(pthread_t tid);

/*
@mutex:
@attr:属性,@attr==NULL时用默认的属性初始化互斥量,
return: 0 if OK, error number on failure

1 互斥变量用 pthread_mutex_t 数据类型来表示,使用前必须初始化,初始值是PTHREAD_MUTEX_INITIALIZER*/
int pthread_mutex_init(pthread_mutex_t *restrict mutex,const pthread_mutexattr_t *restrict attr);

/*return: 0 if OK, error number on failure
如果动态地分配互斥量(例如通过malloc),那么在释放内存前需要调用@pthread_mutex_destroy*/
int pthread_mutex_destroy(pthread_mutex_t *mutex);

/*return: 0 if OK, error number on failure
@pthread_mutex_lock对互斥量加锁,如果互斥量已经上锁,则线程将阻塞直到互斥量被解锁*/
int pthread_mutex_lock(pthread_mutex_t *mutex);

/*return: 0 if OK, error number on failure
If a thread can't afford to block, it can use @pthread_mutex_trylockto lock the
mutex conditionally.If the mutex is unlocked at the time @pthread_mutex_trylock is called,  
then @pthread_mutex_trylock will lock the mutex without blocking and return  0. 
Otherwise, @pthread_mutex_trylock will fail, returning EBUSY without locking the mutex.*/
int pthread_mutex_trylock(pthread_mutex_t *mutex);

/*return: 0 if OK, error number on failure*/
int pthread_mutex_unlock(pthread_mutex_t *mutex);


/*
@attr:属性,@attr==NULL时用默认的属性初始化读写锁
return: 0 if OK, error number on failure

1 读写锁在使用之前必须初始化
*/
int pthread_rwlock_init(pthread_rwlock_t *restrict rwlock,const pthread_rwlockattr_t *restrict attr);

/*return: 0 if OK, error number on failure

1 在释放读写锁占用的内存之前,需要调用@pthread_rwlock_destroy做清理工作
2 如果@pthread_rwlock_init为读写锁分配了资源,@pthread_rwlock_destroy将释放这些资源
3 如果在调用@pthread_rwlock_destroy之前就释放了读写锁占用的内存空间,那么分配给这个锁的资源就丢失了*/
int pthread_rwlock_destroy(pthread_rwlock_t *rwlock);


/*return: 0 if OK, error number on failure*/
int pthread_rwlock_rdlock(pthread_rwlock_t *rwlock);

/*return: 0 if OK, error number on failure*/
int pthread_rwlock_wrlock(pthread_rwlock_t *rwlock);

/*return: 0 if OK, error number on failure
读锁和写锁都用这个函数解锁*/
int pthread_rwlock_unlock(pthread_rwlock_t *rwlock);

/*return: 0 if OK, error number on failure
When the lock can be acquired, these functions return 0. Otherwise, they return the error EBUSY.*/
int pthread_rwlock_tryrdlock(pthread_rwlock_t *rwlock);

/*return: 0 if OK, error number on failure
When the lock can be acquired, these functions return 0. Otherwise, they return the error EBUSY.*/
int pthread_rwlock_trywrlock(pthread_rwlock_t *rwlock);


