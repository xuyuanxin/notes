/*-----------------------------------------------------------------------------------
<strings.h> 不是C/C++的标准头文件，区别于string.h
http://blog.csdn.net/xin_yu_xin/article/details/38672137
strings.h头文件是从BSD系UNIX系统继承而来，里面定义了一些字符串函数，如bzero等。这些函
数曾经是posix标准的一部分，但是在POSIX.1-2001标准里面，这些函数被标记为了遗留函数而不
推荐使用。在POSIX.1-2008标准里已经没有这些函数了。  
-----------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------------
 @func
    比较参数s1和s2字符串，比较时会自动忽略大小写的差异。
 @ret
    若参数s1和s2字符串相等则返回0。s1大于s2则返回大于0 的值，s1 小于s2 则返回小于0的值。
-----------------------------------------------------------------------------------*/
int strcasecmp (const char *s1, const char *s2);


void bzero(void *, size_t); /* 用memset替代 */

/*-----------------------------------------------------------------------------------
func:
    copies @n bytes from @src to @dest. The result is correct, even when both areas -
    overlap.This function is deprecated (marked as LEGACY in POSIX.1-2001):use memcpy 
    or memmove in new programs.
-----------------------------------------------------------------------------------*/
void bcopy(const void *src, void *dest, size_t n);

