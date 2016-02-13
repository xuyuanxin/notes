'''
https://docs.python.org/2/library/time.html
                                                                               |
This module provides various time-related functions. For related functionality, see -
also the datetime and calendar modules. Although this module is always available, not 
all functions are available on all platforms. Most of the functions defined in this -
module call platform C library functions with the same name. It may sometimes be hel-
pful to consult the platform documentation, because the semantics of these  functions 
varies among platforms.
'''


class time.struct_time: #class time.struct_time
  '''
  The type of the time value sequence returned by gmtime(), localtime(), and        -
  strptime(). It is an object with a named tuple interface: values can be accessed by
  index and by attribute name. The following values are present:

  Index    Attribute    Values
  0        tm_year      (for example, 1993)
  1        tm_mon       range [1, 12]
  2        tm_mday      range [1, 31]
  3        tm_hour      range [0, 23]
  4        tm_min       range [0, 59]
  5        tm_sec       range [0, 61]; see (2) in strftime() description
  6        tm_wday      range [0, 6], Monday is 0
  7        tm_yday      range [1, 366]
  8        tm_isdst     0, 1 or -1; see below
  New in version 2.2.
  Note that unlike the C structure, the month value is a range of [1, 12], not      -
  [0, 11]. A year value will be handled as described under "Year 2000 (Y2K) issues" -
  above. A -1 argument as the daylight savings flag, passed to mktime() will  usually 
  result in the correct daylight savings state to be filled in.

  When a tuple with an incorrect length is passed to a function expecting a         -
  struct_time, or having elements of the wrong type, a TypeError is raised.
  '''  

def localtime([secs]): #time.localtime
  '''
  Like gmtime() but converts to local time. If @secs is not provided or None, the cu-
  rrent time as returned by time() is used. The dst flag is set to 1 when DST applies  
  to the given time.
  
  >>> a = time.time()
  >>> a
  1449756656.962
  >>> b = time.localtime(a)
  >>> b
  time.struct_time(tm_year=2015, tm_mon=12, tm_mday=10, tm_hour=22, tm_min=10, tm_sec=56, tm_wday=3, tm_yday=344, tm_isdst=0)
  '''
  pass

def time(): # time.time()
  ''' 
  Return the time in seconds since the epoch as a floating point number. Note that e-
  ven though the time is always returned as a floating point number, not all  systems 
  provide time with a better precision than 1 second. While this function normally r-
  eturns non-decreasing values, it can return a lower value than a previous call if -
  the system clock has been set back between the two calls.
  
  #!/usr/bin/python
  import time;  # This is required to include time module.

  ticks = time.time()
  print "Number of ticks since 12:00am, January 1, 1970:", ticks
  
  output:
  Number of ticks since 12:00am, January 1, 1970: 7186862.73399
  '''
  pass


