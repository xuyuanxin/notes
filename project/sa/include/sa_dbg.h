#ifndef __SA_DBG_H__
#define __SA_DBG_H__

#include <stdio.h>


int dbg_flag;

#define sa_dbgp(format,args...) \
do{\
    if(1 == dbg_flag) \
        printf(format,##args);\
}while(0);
	

#endif
