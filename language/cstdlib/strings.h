/*
  <strings.h> 不是C/C++的标准头文件，区别于string.h
*/

/*
 @func
    比较参数s1和s2字符串，比较时会自动忽略大小写的差异。
 @ret
    若参数s1和s2字符串相等则返回0。s1大于s2则返回大于0 的值，s1 小于s2 则返回小于0的值。
*/
int strcasecmp (const char *s1, const char *s2);

