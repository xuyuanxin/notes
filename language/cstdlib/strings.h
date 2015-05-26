/*-----------------------------------------------------------------------------------
<strings.h> 不是C/C++的标准头文件，区别于string.h
http://blog.csdn.net/xin_yu_xin/article/details/38672137
strings.h头文件是从BSD系UNIX系统继承而来，里面定义了一些字符串函数，如bzero等。这些函
数曾经是posix标准的一部分，但是在POSIX.1-2001标准里面，这些函数被标记为了遗留函数而不
推荐使用。在POSIX.1-2008标准里已经没有这些函数了。  
-----------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------------
 The strcasecmp() function performs a byte-by-byte comparison of the strings s1 and -
 s2, ignoring the case of the characters. It returns an integer less than , equal to, 
 or greater than zero if s1 is found, respectively, to be less than , to match, or be 
 greater than s2. The strncasecmp() function is similar , except it compares only the
 first n bytes of s1.

 http://man7.org/linux/man-pages/man3/strncasecmp.3.html
-----------------------------------------------------------------------------------*/
int strcasecmp (const char *s1, const char *s2);
int strncasecmp(const char *s1, const char *s2, size_t n);


void bzero(void *, size_t); /* 用memset替代 */

/*-----------------------------------------------------------------------------------
func:
    copies @n bytes from @src to @dest. The result is correct, even when both areas -
    overlap.This function is deprecated (marked as LEGACY in POSIX.1-2001):use memcpy 
    or memmove in new programs.
-----------------------------------------------------------------------------------*/
void bcopy(const void *src, void *dest, size_t n);

