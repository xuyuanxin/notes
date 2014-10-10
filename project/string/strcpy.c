/*
  功  能:把src字符串拷贝到dst参数。
  返回值:返回dst，即指向目标字符的指针。
  
  注  意:
  1 此函数不会考虑dst所指内存的大小。它会把src字符完整的拷贝(包括最后的NUL字节)。
  2 二者所指的内存有重叠，其结果是未定义的。
*/

char  *strcpy( char *dst, char const *src ); /*C库原型*/




