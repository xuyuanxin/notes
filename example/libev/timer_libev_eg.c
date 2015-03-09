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


