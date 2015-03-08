#include <ev.h>    // a single header file is required
#include <stdio.h> 

int main()
{
	ev_tstamp  curt,sleept=1.0;
	unsigned int be_flags = 0;
	
    printf("version major:%d minor:%d\n", ev_version_major(),ev_version_minor());
	be_flags = ev_supported_backends();
	printf("Backend Flags:0x%x 0x%x 0x%x\n",be_flags,ev_recommended_backends(),ev_embeddable_backends());
	//ev_feed_signal(); ev_feed_event();
	
	curt = ev_time();
	printf("CurTime:%f sleeping %fs \n",curt,sleept);
	ev_sleep(sleept);
	curt = ev_time();
	printf("Wakeup CurTime:%f\n",curt);

	return 0;

}


int tmp01()
{
    ev_default_loop (EVBACKEND_POLL | EVBACKEND_SELECT | EVFLAG_NOENV);
}

