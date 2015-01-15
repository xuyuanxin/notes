/*
功能：把src所指由NULL结束的字符串的前n个字节复制到dst所指的数组中。
返回：返回指向dst的指针（该指向dst的最后一个元素）
说明：如果src的前n个字节不含NULL字符，则结果不会以NULL字符结束。        
      如果src的长度小于n个字节，则以NULL填充dest直到复制完n个字节(所以拷贝效率低些)。        
      src和dest所指内存区域不可以重叠且dest必须有足够的空间来容纳src的字符串。        
*/
char *strncpy(char *dst, const char *src, size_t n);


/*
 @str1
    C string to be compared.
 @str2
    C string to be compared.
*/
int strcmp ( const char * str1, const char * str2 );




/*
 @destination
    Pointer to the destination array, which should contain a C string, and be large 
    enough to contain the concatenated resulting string.
 @source
    C string to be appended. This should not overlap destination.
 @ret 
    @destination is returned.
 @func
    Appends a copy of the @source string to the @destination string. The terminating 
    null character in @destination is overwritten by the first character of source, and 
    a null-character is included at the end of the new string formed by the concatenation 
    of both in destination. @destination and @source shall not overlap.
*/
char * strcat ( char * destination, const char * source );


/*
 @ptr
    Pointer to the block of memory to fill.
 @value
    Value to be set. The value is passed as an int, but the function fills the block 
    of memory using the unsigned char conversion of this value.
 @num
    Number of bytes to be set to the value.size_t is an unsigned integral type.
 @ret
    @ptr is returned.
 @func
    Sets the first @num bytes of the block of memory pointed by @ptr to the specified 
    @value (interpreted as an unsigned char).
*/
void * memset ( void * ptr, int value, size_t num );


