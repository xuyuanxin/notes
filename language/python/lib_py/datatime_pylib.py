'''                                                                                  |
http://www.cnblogs.com/lhj588/archive/2012/04/23/2466653.html                        |
Python提供了多个内置模块用于操作日期时间，像calendar，time，datetime。time模块我在之 |
前的文章已经有所介绍，它提供的接口与C标准库time.h基本一致。相比于time模块，datetime模|
块的接口则更直观、更容易调用。今天就来讲讲datetime模块。                             |
datetime模块定义了两个常量：datetime.MINYEAR和datetime.MAXYEAR，分别表示datetime所能 |
表示的最 小、最大年份。其中，MINYEAR = 1，MAXYEAR = 9999。                           |
                                                                                     |
datetime模块定义了下面这几个类：                                                     |
datetime.date：表示日期的类。常用的属性有year, month, day；
datetime.time：表示时间的类。常用的属性有hour, minute, second, microsecond；
datetime.datetime：表示日期时间。
datetime.timedelta：表示时间间隔，即两个时间点之间的长度。
datetime.tzinfo：与时区有关的相关信息。
注：上面这些类型的对象都是不可变（immutable）的。


Directive	Meaning	Example	Notes
%a	Weekday as locale’s abbreviated name.	
Sun, Mon, ..., Sat (en_US);
So, Mo, ..., Sa (de_DE)
(1)
%A	Weekday as locale’s full name.	
Sunday, Monday, ..., Saturday (en_US);
Sonntag, Montag, ..., Samstag (de_DE)
(1)
%w	Weekday as a decimal number, where 0 is Sunday and 6 is Saturday.	0, 1, ..., 6	 
%d	Day of the month as a zero-padded decimal number.	01, 02, ..., 31	 
%b	Month as locale’s abbreviated name.	
Jan, Feb, ..., Dec (en_US);
Jan, Feb, ..., Dez (de_DE)
(1)
%B	Month as locale’s full name.	
January, February, ..., December (en_US);
Januar, Februar, ..., Dezember (de_DE)
(1)

Directive  Meaning                                  Example  Notes
%m	       Month as a zero-padded decimal number.	01, 02, ..., 12	 
	 
%H	Hour (24-hour clock) as a zero-padded decimal number.	00, 01, ..., 23	 
%I	Hour (12-hour clock) as a zero-padded decimal number.	01, 02, ..., 12	 
%p	Locale’s equivalent of either AM or PM.	
AM, PM (en_US);
am, pm (de_DE)
(1), (2)
%M	Minute as a zero-padded decimal number.	00, 01, ..., 59	 
%S	Second as a zero-padded decimal number.	00, 01, ..., 59	(3)
%f	Microsecond as a decimal number, zero-padded on the left.	000000, 000001, ..., 999999	(4)
%z	UTC offset in the form +HHMM or -HHMM (empty string if the the object is naive).	(empty), +0000, -0400, +1030	(5)
%Z	Time zone name (empty string if the object is naive).	(empty), UTC, EST, CST	 
%j	Day of the year as a zero-padded decimal number.	001, 002, ..., 366	 
%U	Week number of the year (Sunday as the first day of the week) as a zero padded decimal number. All days in a new year preceding the first Sunday are considered to be in week 0.	00, 01, ..., 53	(6)
%W	Week number of the year (Monday as the first day of the week) as a decimal number. All days in a new year preceding the first Monday are considered to be in week 0.	00, 01, ..., 53	(6)
%c	Locale’s appropriate date and time representation.	
Tue Aug 16 21:30:00 1988 (en_US);
Di 16 Aug 21:30:00 1988 (de_DE)
(1)
%x	Locale’s appropriate date representation.	
08/16/88 (None);
08/16/1988 (en_US);
16.08.1988 (de_DE)
(1)
%X	Locale’s appropriate time representation.	
21:30:00 (en_US);
21:30:00 (de_DE)
(1)
%%	A literal '%' character.	%


----> format
 %y  Year without century as a zero-padded decimal number.  00, 01, ..., 99	 
 %Y  Year with century as a decimal number.  1970, 1988, 2001, 2013


'''

''' class datetime.date

'''
class date:
    def 

'''datetime.datetime
'''
class datetime:
    def
	
	
	
	
	

''' datetime.strftime(format)
Return a string representing the date and time, controlled by an explicit @format string.
>>> t.strftime("%H:%M:%S %Z")
'12:10:30 Europe/Prague'
'''
def strftime(format):
    pass

''' classmethod datetime.strptime(date_string, format)
Return a datetime corresponding to @date_string, parsed according to @format. 
>>> dt = datetime.strptime("21/11/06 16:30", "%d/%m/%y %H:%M")
>>> dt
datetime.datetime(2006, 11, 21, 16, 30)
'''
def strptime(date_string, format):
    pass
