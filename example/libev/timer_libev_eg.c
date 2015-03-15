#include <ev.h>    // a single header file is required
#include <stdio.h> 
#include <stdlib.h>


static void timeout_cb01 (struct ev_loop *loop, ev_timer *w, int revents)
{
    puts ("timeout\n");
	
    ev_break (loop, EVBREAK_ONE);
}

int timer_libev_eg01 (void)
{
    struct ev_loop *loop = EV_DEFAULT;
	ev_timer timer;
	
    ev_timer_init (&timer, timeout_cb01, 1.5, 0.);
    ev_timer_start (loop, &timer);
	
    ev_run(loop, 0);
	
    return 0;
}

static void timeout_cb02 (struct ev_loop *loop, ev_timer *w, int revents)
{
     //.. ten seconds without any activity
     
	 puts ("timeout02\n");
}

int timer_libev_eg02()
{
	struct ev_loop *loop = EV_DEFAULT; 

	ev_timer mytimer;
	ev_timer_init (&mytimer, timeout_cb02, 0., 2.); /* note, only repeat used */
	ev_timer_again (loop,&mytimer); /* start timer */
	ev_run (loop, 0);
	
	// and in some piece of code that gets executed on any "activity":
	// reset the timeout to start ticking again at 10 seconds
	printf("break from ev_run\n");
	ev_timer_again (loop,&mytimer);

	return 0;

}

int main(int argc, char *argv[])
{
    int tflag = 0;
	
    if(1 == argc) {
		return timer_libev_eg01();
    } else if(2 == argc) {
		tflag = atoi(argv[1]);
		if(1 == tflag) {
			return timer_libev_eg01();
		} else if(2 == tflag) {
			return timer_libev_eg02();
		} else {
		    printf("inpara error01\n");
			return 0;
		}
	} else {
	   printf("inpara error\n");
	   return 0;
	}
}

/*
ev_timer_init
ev_timer_set
ev_timer_again 
ev_timer_remaining

ev_tstamp repeat [read-write]


ev_timer - relative and optionally repeating timeouts
    Timer watchers are simple relative timers that generate an event after a given t-
    ime, and optionally repeating in regular intervals after that.

    The timers are based on real time, that is, if you register an event that times -
    out after an hour and you reset your system clock to January last year, it will -
    still time out after (roughly) one hour. "Roughly" because detecting time jumps -
    is hard, and some inaccuracies are unavoidable ( the monotonic clock option helps 
    a lot here).

    The callback is guaranteed to be invoked only after its timeout has passed (not -
    at, so on systems with very low-resolution clocks this might introduce a small d-
    elay). If multiple timers become ready during the same loop iteration then the o-
    nes with earlier time-out values are invoked before ones of the same priority wi-
    th later time-out values (but this is no longer true when a callback calls ev_run 
    recursively).




1.分析定时器监控器

定时器在程序中可以做固定周期tick操作，也可以做一次性的定时操作。Libev中与定时器类似的还有个周期事件watcher。其本质都是一样的，只是在时间的计算方法上略有不同，并有他自己的一个事件管理的堆。对于定时器事件，我们按照之前说的顺序从ev_init开始看起。

1.1定时器监控器的初始化

定时器初始化使用 ev_init(&timer_w,timer_action);,这个过程和之前的IO类似，主要就是设置基类的active、pending、priority以及触发动作回调函数cb。

1.2设置定时器监控器的触发条件

通过 ev_timer_set(&timer_w,2,0);可以设置定时器在2秒钟后被触发。如果第三个参数不是0而是一个大于0的正整数n时，那么在第一次触发（2秒后），每隔n秒会再次触发定时器事件。

其为一个宏定义 do { ((ev_watcher_time *)(ev))->at = (after_); (ev)->repeat = (repeat_); } while (0) 也就是设置派生类定时器watcher的“at”为触发事件，以及重复条件“repeat”。

1.3将定时器注册到事件驱动器上

ev_timer_start(main_loop,&timer_w);会将定时器监控器注册到事件驱动器上。其首先 ev_at (w) += mn_now; 得到未来的时间，这样放到时间管理的堆“timers”中作为权重。然后通过之前说过的“ev_start”修改驱动器loop的状态。这里我们又看到了动态大小的数组了。Libev的堆的内存管理也是通过这样的关系的。具体这里堆的实现，感兴趣的可以仔细看下实现。这里的操作就是将这个时间权重放到堆中合适的位置。这里堆单元的结构为：

typedef struct {
    ev_tstamp at;
    WT w;
} ANHE;
其实质就是一个时刻at上挂一个放定时器watcher的list。当超时时会依次执行这些定时器watcher上的触发回调函数。

1.4定时器监控器的触发

最后看下在一个事件驱动器循环中是如何处理定时器监控器的。这里我们依然抛开其他的部分，
只找定时器相关的看。在“/ calculate blocking time /”块里面，我们看到计算blocking ti-
me的时候会先：
    if (timercnt) {
        ev_tstamp to = ANHE_at (timers [HEAP0]) - mn_now;
        if (waittime > to) waittime = to;
    }
如果有定时器，那么就从定时器堆（一个最小堆）timers中取得堆顶上最小的一个时间。这样就
保证了在这个时间前可以从backend_poll中出来。出来后执行timers_reify处理将pengding的定
时器。

在timers_reify中依次取最小堆的堆顶，如果其上的ANHE.at小于当前时间，表示该定时器watcher
超时了，那么将其压入一个数组中，由于在实际执行pendings二维数组上对应优先级上的watcher
是从尾往头方向的，因此这里先用一个数组依时间先后次存下到一个中间数组loop->rfeeds中。然
后将其逆序调用ev_invoke_pending插入到pendings二维数组中。这样在执行pending事件的触发动
作的时候就可以保证，时间靠前的定时器优先执行。函数 feed_reverse和 feed_reverse_done就是
将超时的定时器加入到loop->rfeeds暂存数组以及将暂存数组中的pending的watcher插入到pengdings
数组的操作。把pending的watcher加入到pendings数组，后续的操作就和之前的一样了。回依次执
行相应的回调函数。

这个过程中还判断定时器的 w->repeat 的值，如果不为0，那么会重置该定时器的时间，并将其压
入堆中正确的位置，这样在指定的时间过后又会被执行。如果其为0，那么调用ev_timer_stop关闭
该定时器。 其首先通过clear_pending置pendings数组中记录的该watcher上的回调函数为一个不执
行任何动作的哑动作。

总结一下定时器就是在backend_poll之前通过定时器堆顶的超时时间，保证blocking的时间不超过
最近的定时器时间，在backend_poll返回后，从定时器堆中取得超时的watcher放入到pendings二
维数组中，从而在后续处理中可以执行其上注册的触发动作。然后从定时器管理堆上删除该定时器
。最后调用和ev_start呼应的ev_stop修改驱动器loop的状态，即loop->activecnt减少一。并将该
watcher的active置零。

对于周期性的事件监控器是同样的处理过程。只是将timers_reify换成了periodics_reify。其内
部会对周期性事件监控器派生类的做类似定时器里面是否repeat的判断操作。判断是否重新调整时
间，或者是否重复等逻辑，这些看下代码比较容易理解，这里不再赘述。·

*/
