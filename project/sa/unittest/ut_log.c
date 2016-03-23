#include <stdio.h>

#include "sa_log.h"

int ut_log_main()
{
    log_st *utlog;
    int i;

	utlog = log_init("/var/log/libsa","libsa.log",1000);

    for(i = 0; i < 20; i++) {
        log_debug(utlog,"%d ttttt.\n",i);
    }
	
	return 0;
}



