#include <ev.h>    // a single header file is required
#include <stdio.h> 

int main()
{
	ev_tstamp  curt,sleept=2.0;
	
    printf("version major:%d minor:%d\n", ev_version_major(),ev_version_minor());
	curt = ev_time();
	printf("CurTime:%f sleeping %fs \n",curt,sleept);
	ev_sleep(sleept);
	curt = ev_time();
	printf("Wakeup CurTime:%f\n",curt);

	return 0;

}

