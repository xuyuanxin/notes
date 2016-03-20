#include "sa_log.h"

int ut_log_main()
{
    log_st *utlog;

	utlog = log_init("/var/log/libsa",100000,3,0);

    log_debug(utlog,"libsa log test.");

	return 0;
}



