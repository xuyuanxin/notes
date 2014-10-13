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

