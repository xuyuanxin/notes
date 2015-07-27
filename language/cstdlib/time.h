#ifndef __TIME_T
#define __TIME_T 
typedef long time_t; //²»È·¶¨
#endif

/*-----------------------------------------------------------------------------------
 time() returns the time as the number of seconds since the Epoch,                  -
 1970-01-01 00:00:00 +0000 (UTC). If t is non-NULL, the return value is also stored -
 in the memory pointed to by t.

 On success, the value of time in seconds since the Epoch is returned. On error,    -
 ((time_t) -1) is returned, and errno is set appropriately.
 ---------------------------------------------------------------------------------*/
time_t time(time_t *t);




#include <sys/time.h>
int gettimeofday(struct timeval *restrict tp, void *restrict tzp);


