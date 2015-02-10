/************************************************************************************
 ev_io的主要使命就是监听并响应指定文件描述fd上的读写事件。对fd的监听工作，主要委托给底
 层的io库来完成。libev对目前比较流行的io库都提供了支持，如：select, epoll以及windows的
 iocp等。在这里libev使用了Adaptor模式，通过统一的适配层隐藏了底层io库的细节。 在loop初
 始化的时候（loop_init），会根据配置将函数指针绑定到底层的io库函数对应的适配代码上。所
 以，开发者可以很方便的把代码切换到不同的底层实现上。 相关的函数有：backend_modify，向
 底层库注册fd事件，如：epoll的epoll_ctl；backend_poll， 向底层库轮询fd上是否有感兴趣的
 事件发生，如：epoll的epoll_wait。适配器实现的代码可以在ev_LIB.c中看到， LIB是io库的名
 字，如：ev_epoll.c，ev_win32.c等。

 +-----------------------------------------+
 |              Hight Level Codes          |
 +-----------------------------------------+
                         /|\
                          |
                          |
 +----------------------------------------------+
 |         backend_modify     |   backend_poll  |    Adaptor Layer      
 +----------------------------------------------+
                         /|\
                          |
                          |
 +-------------------------------------------------------+
 | ev_select | ev_poll | ev_epoll | ev_kqueue | ev_win32 |    Adaptor Implement
 +-------------------------------------------------------+
*************************************************************************************

 ev_io的结构
    EV_WATCHER_LIST是EV_WATCHER结构的链表节点结构。fd是监听的文件描述符，events是感兴
    趣的事件。 ev_io从它诞生的那一刻起，便于文件描述符紧密结合在一起了。ev_io的实例被
    存储在loop->anfds的结构中。anfds的结构如下图所示：
            ANFD
          +--------+      ev_io linked list
          |  head  |----> w0 ----> w1 ----> w2
          |--------|
          | events |
          |--------|
          |  ...   |
          +--------+
             /|\
 loop->anfds  |
    +-----+   |  
    | fd0 |----  
    +-----+     
    | fd1 |       
    +-----+       
    | ... |       
    +-----+
    | fdn |
    +-----+
 anfds其实是一个数组，它使用fd作为下标，数组中的元素是一个ANFD的结构。ANFD是一个维护
 fd信息的结构体。其中，events记录了当前fd上感兴趣的事件的记录。head是watcher列表的头
 指针，这个列表就是在这个fd上注册的watcher列表。当fd的大小超出了anfds的容量，anfds会
 进行相应的扩展。

ev_io的插入
    从前面的介绍我们知道，要通过libev来监听fd上的事件，得要先插入一个ev_io到libev的
    loop中。ev_io的插入操作被封装在ev_io_start函数中。毫无疑问，libev首先会根据fd找
    到对应的watcher列表，并将新watcher加入到列表中。接下来，会调用fd_change函数，将
    fd加入到loop->fdchanges中。fdchanges是一个简单的数组， 记录的是当前注册事件有发
    生改变的fd。到此为止，新ev_io的插入完成，上面的所有操作时间代价都是O(1)。 
ev_io的选取
    前面我们已经向libev的loop中插入了一个ev_io，那么libev是怎么把这个ev_io注册到底层
    io并响应底层的io事件的呢？ 从ev_run流程中可以看到，ev_io的选取由fd_reify和
    backend_poll这两个步骤来完成。 
    fd_reify函数的工作主要是遍历fdchanges，将对应列表的watcher的events字段合并到ANFD
    结构的events字段。ANFD上如果新的events与原来监听的events不一致，则表示在这个fd上
    监听的事件集发生了变化，需要将fd和事件集合通过backend_modify注册到底层的io库。 
    在循环的后面，则会调用backend_poll来检查fd上是否有注册的事件发生。如果有事件发生
    ，则通过fd_event函数，遍历fd对应的watcher列表，比较每个watcher上的events字段与发
    生的事件event值，找出就绪的watcher添加到pendings中。
    最后，这些pendings中的watcher会在循环结束前调用ev_invoke_pending来统一触发。
ev_io的移除
    ev_io的移除由ev_io_stop来完成。首先，会先检查该watcher是否在pendings列表中，如果
    是，则先从pendings中删除该watcher。pendings是一个数组，libev中的数组一般是以数组
    和元素数量来维护的。删除数组中的一个元素，只要把数组末尾的元素替换掉被删除的元素
    ，并把元素数量减一就可以了，操作的时间复杂度是O(1) 。 
    接下来就是通过fd找到watcher列表，从中删除这个watcher。这个操作需要遍历列表找到待
    删除的watcher，所以平均时间复杂度是O(n)。其中n是注册在fd上的watcher数量， 一般这
    个数量不会太大。
    然后是把watcher的active标志位复位，并减少全局active的watcher计数。
    最后是把fd加入到fdchanges中，因为移除一个watcher，可能会改变fd上感兴趣的事件，所
    以要在下一轮循环中重新计算该fd上的事件集合。
*/

#define ev_init(ev,cb_) do {			\
  ((ev_watcher *)(void *)(ev))->active  =	\
  ((ev_watcher *)(void *)(ev))->pending = 0;	\
  ev_set_priority ((ev), 0);			\
  ev_set_cb ((ev), cb_);			\
} while (0)


int x_ev_io_init(ev_io *ev,void *cb,int fd,int events)
{
	ev->active   = 0;
	ev->pending  = 0;
	ev->priority = 0;
	ev->cb       = cb;
	ev->fd       = fd; 
	ev->events   = (events) | EV__IOFDSET;
}

/*-----------------------------------------------------------------------------------
 notes01
    是对函数 “ev_verify"的调用，那么ev_verify是干什么的呢？用文档的话“This can be 
    used to catch bugs inside libev itself”，如果看其代码的话，就是去检测Libev的内部
    数据结构，判断各边界值是否合理，不合理的时候assert掉。
-----------------------------------------------------------------------------------*/
void x_ev_io_start (ev_loop *loop, ev_io *w)
{
    int fd = w->fd;

    if (expect_false (ev_is_active (w)))
        return;

    assert (("libev: ev_io_start called with negative fd", fd >= 0));
    assert (("libev: ev_io_start called with illegal event mask", !(w->events & ~(EV__IOFDSET | EV_READ | EV_WRITE))));

    EV_FREQUENT_CHECK; /* notes01 */

    ev_start (loop, (W)w, 1);
    array_needsize (ANFD, anfds, anfdmax, fd + 1, array_init_zero);
    wlist_add (&anfds[fd].head, (WL)w);

    /* common bug, apparently */
    assert (("libev: ev_io_start called with corrupted watcher", ((WL)w)->next != (WL)w));

    fd_change (EV_A_ fd, w->events & EV__IOFDSET | EV_ANFD_REIFY);
    w->events &= ~EV__IOFDSET;

    EV_FREQUENT_CHECK;
}

