// a single header file is required
#include <ev.h>

#include <stdio.h> // for puts

// every watcher type has its own typedef'd struct
// with the name ev_TYPE
ev_io stdin_watcher;
ev_timer timeout_watcher;

// all watcher callbacks have a similar signature
// this callback is called when data is readable on stdin
static void stdin_cb (EV_P_ ev_io *w, int revents)
{
  puts ("stdin ready");
  // for one-shot events, one must manually stop the watcher
  // with its corresponding stop function.
  ev_io_stop (EV_A_ w);

  // this causes all nested ev_run's to stop iterating
  ev_break (EV_A_ EVBREAK_ALL);
}

// another callback, this time for a time-out
static void timeout_cb (EV_P_ ev_timer *w, int revents)
{
  puts ("timeout");
  // this causes the innermost ev_run to stop iterating
  ev_break (EV_A_ EVBREAK_ONE);
}

/*-----------------------------------------------------------------------------------
 这是libev官网文档的例子
 1 获取ev_loop实例。ev_loop，从名字上可以看出，它代表了一个事件循环，也是我们后面代码
   的主要组织者。
 2 创建和初始化watcher。libev中定义了一系列的watcher，每类watcher负责一类特定的事件。
   一般可以通过ev_TYPE_init函数来创建一个watcher实例（TYPE是某一种watcher类型，如：io, 
   timer等）。例子中分别创建了io和timer两个watcher，并绑定了相应的回调函数。当感兴趣的
   事件发生后，对应的回调函数将会被调用。
 3 将watcher注册到ev_loop中。一般可以通过ev_TYPE_start函数来完成。注册成功后，watcher
   便和loop关联起来了，当loop中检测到感兴趣的事件发生，便会通知相关的watcher。
 4 启动事件循环。 即后面的ev_run函数。事件循环启动后，当前线程/进程将会被阻塞，直到循
   环被终止。
 5 在上面的例子中，在两个回调函数中的ev_break函数就是终止循环的地方。当5.5秒超时或是标
   准输入有输入事件，则会进入到相应的回调函数，然后会终止事件循环，退出程序。
-----------------------------------------------------------------------------------*/
int main (void)
{
  // use the default event loop unless you have special needs
  struct ev_loop *loop = EV_DEFAULT;

  // initialise an io watcher, then start it
  // this one will watch for stdin to become readable
  ev_io_init (&stdin_watcher, stdin_cb, /*STDIN_FILENO*/ 0, EV_READ);
  ev_io_start (loop, &stdin_watcher);

  // initialise a timer watcher, then start it
  // simple non-repeating 5.5 second timeout
  ev_timer_init (&timeout_watcher, timeout_cb, 5.5, 0.);
  ev_timer_start (loop, &timeout_watcher);

  // now wait for events to arrive
  ev_run (loop, 0);

  // break was called, so exit
  return 0;
}
