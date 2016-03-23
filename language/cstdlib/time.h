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
 @timer
    Pointer to an object of type time_t that contains a time value. time_t is an ali-
    as of a fundamental arithmetic type capable of representing times as returned  by 
    function @time.
 @func:
    Convert time_t value to string. Interprets the value pointed by @timer as a cale-
    ndar time and converts it to a C-string containing a human-readable version of t-
    he corresponding time and date, in terms of local time.
 @return
    A C-string containing the date and time information in a human-readable format. -
    The returned value points to an internal array whose validity or value may be al-
    tered by any subsequent call to asctime or ctime.

 The returned string has the following format: Www Mmm dd hh:mm:ss yyyy. Where Www i-
 s the weekday, Mmm the month (in letters), dd the day of the month, hh:mm:ss the ti-
 me, and yyyy the year. The string is followed by a new-line character ('\n') and te-
 rminated with a null-character.
 
 This function is equivalent to: 
  
 asctime(localtime(timer))
 
 For an alternative with custom date formatting, see strftime.

 #include <stdio.h>      //printf 
 #include <time.h>       //time_t, time, ctime
 
 int main ()
 {
   time_t rawtime;
 
   time (&rawtime);
   printf ("The current local time is: %s", ctime (&rawtime));
 
   return 0;
 }

 Output: 
 The current local time is: Wed Feb 13 16:06:10 2013

 http://bbs.csdn.net/topics/390345116
 ---------------------------------------------------------------------------------*/
char* ctime (const time_t * timer);

/*-----------------------------------------------------------------------------------
 @timer
    Pointer to an object of type time_t, where the time value is stored. Alternative-
    ly, this parameter can be a null pointer, in which case the parameter is not used 
    (the function still returns a value of type time_t with the result).
 @return
    The current calendar time as a time_t object. If the argument is not a null poin-
    ter, the return value is the same as the one stored in the location pointed by a-
    rgument timer. If the function could not retrieve the calendar time, it returns -
    a value of -1. time_t is an alias of a fundamental arithmetic type capable of re-
    presenting times.

 Get current time. Get the current calendar time as a value of type time_t. The func-
 tion returns this value, and if the argument is not a null pointer, it also sets th-
 is value to the object pointed by timer.

 The value returned generally represents the number of seconds since 00:00 hours, Ja-
 n 1, 1970 UTC (i.e., the current unix timestamp). Although libraries may use a diff-
 erent representation of time: Portable programs should not use the value returned by 
 this function directly, but always rely on calls to other elements of the standard -
 library to translate them to portable types (such as localtime, gmtime or difftime).

 // time example 
 #include <stdio.h>      // printf 
 #include <time.h>       // time_t, struct tm, difftime, time, mktime 

 int main ()
 {
   time_t timer;
   struct tm y2k = {0};
   double seconds;

   y2k.tm_hour = 0;   y2k.tm_min = 0; y2k.tm_sec = 0;
   y2k.tm_year = 100; y2k.tm_mon = 0; y2k.tm_mday = 1;

   time(&timer);  // get current time; same as: timer = time(NULL)  

   seconds = difftime(timer,mktime(&y2k));

   printf ("%.f seconds since January 1, 2000 in the current timezone", seconds);

   return 0;
 }
 
 Possible output:
 414086872 seconds since January 1, 2000 in the current timezone
-----------------------------------------------------------------------------------*/
time_t time (time_t* timer);


#include <sys/time.h>
int gettimeofday(struct timeval *restrict tp, void *restrict tzp); /* linux syscall */


