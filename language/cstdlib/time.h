#ifndef __TIME_T
#define __TIME_T 
typedef long time_t; //²»È·¶¨
#endif

struct tm 
{
	int tm_sec;	  /* Seconds (0-60) */
	int tm_min;	  /* Minutes (0-59) */
	int tm_hour;  /* Hours (0-23) */
	int tm_mday;  /* Day of the month (1-31) */
	int tm_mon;   /* Month (0-11) */
	int tm_year;  /* Year - 1900 */
	int tm_wday;  /* Day of the week (0-6, Sunday = 0) */
	int tm_yday;  /* Day in the year (0-365, 1 Jan = 0) */
	int tm_isdst; /* Daylight saving time */
};


/*-----------------------------------------------------------------------------------
 @timep:
     Pointer to an object of type time_t that contains a time value. time_t is an al-
     ias of a fundamental arithmetic type capable of representing times as returned -
     by function @time.
 @func:
     Convert time_t to tm as local time. Uses the value pointed by @timep to fill a -
     tm structure with the values that represent the corresponding time, expressed f-
     or the local timezone.
 @Return Value
     A pointer to a tm structure with its members filled with the values that corres-
     pond to the local time representation of @timep.
 ----------------------------------------------------------------------------------*/
struct tm *localtime(const time_t *timep);


/*-----------------------------------------------------------------------------------
 time() returns the time as the number of seconds since the Epoch,                  -
 1970-01-01 00:00:00 +0000 (UTC). If t is non-NULL, the return value is also stored -
 in the memory pointed to by t.

 On success, the value of time in seconds since the Epoch is returned. On error,    -
 ((time_t) -1) is returned, and errno is set appropriately.
 ---------------------------------------------------------------------------------*/
time_t time(time_t *t);




#include <sys/time.h>
int gettimeofday(struct timeval *restrict tp, void *restrict tzp); /* linux syscall */


