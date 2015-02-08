

/* invoked when fd is either EV_READable or EV_WRITEable */
/* revent EV_READ, EV_WRITE */
/*-----------------------------------------------------------------------------------
 @active: 
     表示当前watcher是否被激活。ev_TYPE_start调用后置位，ev_TYPE_stop调用后复位；
 @pending: 
    表示当前watcher有事件就绪，等待处理。pending的值其实就是当前watcher在pendings队列
    中的下标；
 @priority: 
    是当前watcher的优先级；
 @data: 
    附加数据指针，用来在watcher中携带额外所需的数据；
 @cb：
    是事件触发后的回调函数定义。

 具体的watcher再在此基础上添加额外的属性。 开发者可以根据需要，选择特定类型的watcher，
 创建实例并进行初始化，然后将实例注册到loop中即可。libev中定义了若干种类型的watcher，
 每类watcher负责解决某一特定领域的问题（如：io, timer, signal等），可以在ev.h中看到这
 些watcher的定义。
-----------------------------------------------------------------------------------*/
typedef struct ev_io
{
	int active; /* private */		  
	int pending; /* private */			  
	int priority; /* private */		  
	void *data; /* rw */				  
	void (*cb)(struct ev_loop *loop, struct ev_io *w, int revents); /* private */
    int fd;     /* fd是监听的文件描述符 */
    int events; /* events是感兴趣的事件。  */
} ev_io;

