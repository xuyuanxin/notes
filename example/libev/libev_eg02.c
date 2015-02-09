#include <ev.h>
#include <stdio.h>
#include <signal.h>
#include <sys/unistd.h>

ev_io io_w;         /* IO事件 监控器(watcher) */
ev_timer timer_w;   /* 定时器事件 监控器(watcher) */
ev_signal signal_w; /* 信号事件 监控器(watcher) */

/*-----------------------------------------------------------------------------------
 在事件的触发动作里面。我加入了一个 ev_xxx_stop 函数，也就是把该监控器从事件驱动器里
 面注销掉。使其不再起作用。而在信号触发的动作中还加入了一个 ev_break 该函数可以使进程
 跳出 main_loop 事件驱动器循环,也就是关闭事件驱动器。结束这一逻辑。
-----------------------------------------------------------------------------------*/
void io_action(struct ev_loop *main_loop,ev_io *io_w,int e)
{
        int rst;
        char buf[1024] = {'\0'};
        puts("in io cb");
        read(STDIN_FILENO,buf,sizeof(buf));
        buf[1023] = '\0';
        printf("Read in a string %s",buf);
        ev_io_stop(main_loop,io_w);
}

void timer_action(struct ev_loop *main_loop,ev_timer *timer_w,int e)
{
        puts("in tiemr cb");
        ev_timer_stop(main_loop,timer_w);
}

void signal_action(struct ev_loop *main_loop,ev_signal signal_w,int e)
{
        puts("in signal cb");
        ev_signal_stop(main_loop,signal_w);
        ev_break(main_loop,EVBREAK_ALL);
}

/*-----------------------------------------------------------------------------------
 notes01
    首先定义了一个事件驱动器的结构 struct ev_loop *main_loop 这里调用 ev_default_loop(0) 
    生成一个预制的全局驱动器。然后依次初始化各个监控器以及设置监控器的触发条件。初始
    化监控器的过程是将相应的回调函数即触发时的动作注册到监控器上。设置触发条件则是该
    条件产生时才去执行注册到监控器上的动作。对于IO事件，一般是设置特定fd上的的可读或
    可写事件，定时器则是多久后触发。这里定时器的触发条件中还有第三参数，表示第一次触
    发后，是否循环，若为0则吧循环，否则按该值循环。信号触发器则是设置触发的信号。在初
    始化并设置好触发条件后，先调用ev_xxx_start 将监控器注册到事件驱动器上。接着调用 
    ev_run 开始事件驱动器。
*/
int main(int argc ,char *argv[])
{
        struct ev_loop *main_loop = ev_default_loop(0); /* notes01 */
        ev_init(&io_w,io_action);
        ev_io_set(&io_w,STDIN_FILENO,EV_READ);  
        ev_init(&timer_w,timer_action);
        ev_timer_set(&timer_w,2,0);       
        ev_init(&signal_w,signal_action);
        ev_signal_set(&signal_w,SIGINT); 

        ev_io_start(main_loop,&io_w);
        ev_timer_start(main_loop,&timer_w);
        ev_signal_start(main_loop,&signal_w);

        ev_run(main_loop,0);

    return 0;
}

