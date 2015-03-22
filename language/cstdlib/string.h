/*-----------------------------------------------------------------------------------
功能：把src所指由NULL结束的字符串的前n个字节复制到dst所指的数组中。
返回：返回指向dst的指针（该指向dst的最后一个元素）
说明：如果src的前n个字节不含NULL字符，则结果不会以NULL字符结束。        
      如果src的长度小于n个字节，则以NULL填充dest直到复制完n个字节(所以拷贝效率低些)。        
      src和dest所指内存区域不可以重叠且dest必须有足够的空间来容纳src的字符串。        
-----------------------------------------------------------------------------------*/
char *strncpy(char *dst, const char *src, size_t n);


/*-----------------------------------------------------------------------------------
 @str1
    C string to be compared.
 @str2
    C string to be compared.
 @ret
    Returns an integral value indicating the relationship between the strings:
    return value  indicates
      <0          the first character that does not match has a lower value in ptr1 
                  than in ptr2
       0          the contents of both strings are equal
      >0          the first character that does not match has a greater value in ptr1 
                  than in ptr2
-----------------------------------------------------------------------------------*/
int strcmp ( const char * str1, const char * str2 );

/*-----------------------------------------------------------------------------------
 @strcat: string catenate
 @destination
    Pointer to  the  destination array, which should contain a C string, and be large 
    enough to contain the concatenated resulting string.
 @source
    C string to be appended. This should not overlap destination.
 @ret 
    @destination is returned.
 @func
    Appends a copy of the @source string to the @destination  string. The terminating 
    null character in @destination is overwritten by the  first character of @source, 
    and a null-character is included at the end of the new string formed by the conc-
    atenation of both in @destination. @destination and @source shall not overlap.   
-----------------------------------------------------------------------------------*/
char * strcat ( char * destination, const char * source );


/*-----------------------------------------------------------------------------------
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
-----------------------------------------------------------------------------------*/
void * memset ( void * ptr, int value, size_t num );

/*-----------------------------------------------------------------------------------
 @errnum
    Error number.
 @fun
    Get pointer to error message string
 @ret
    A pointer to the error string describing error errnum.

 Interprets the value of errnum, generating a string with a message that describes t-
 he error condition as if set to errno by a function of the library. The returned po-
 inter points to a statically allocated string, which shall not be modified by the p-
 rogram. Further calls to this function may overwrite its content (particular library 
 implementations are not required to avoid data races). The error strings produced by 
 strerror may be specific to each system and library implementation.
-----------------------------------------------------------------------------------*/
char * strerror ( int errnum );


/*-----------------------------------------------------------------------------------
 @str
    C string.
 @character
    Character to be located. It  is passed as its int promotion, but it is internally 
    converted back to char for the comparison.
 @func
    Locate first occurrence of @character in string
 @ret
    A pointer to the first occurrence of @character in @str. If the @character is not 
    found, the function returns a null pointer.

 The terminating null-character is considered part of the C string. Therefore, it can 
 also be located in order to retrieve a pointer to the end of a string.    
-----------------------------------------------------------------------------------*/
const char * strchr ( const char * str, int character ); /* C++ */
	  char * strchr (		char * str, int character );  /* C++ */
	  char * strchr ( const char *, int ); /* C */

/*-----------------------------------------------------------------------------------
 @destination
    Pointer to the destination array where the content is to be copied, type-casted -
    to a pointer of type void*.
 @source
    Pointer to the source of data to be copied, type-casted to a pointer of type con-
    st void*.
 @num
    Number of bytes to copy.
 @func
    Move block of memory
 @ret
    @destination is returned.

 Copies the values of @num bytes from the location pointed by @source to the memory -
 block pointed by @destination. Copying takes place as if an intermediate buffer were 
 used, allowing the @destination and @source to overlap.
 The underlying type of the objects pointed by both the @source and @destination poi-
 nters are irrelevant for this function; The result is a binary copy of the data.
 The function does not check for any terminating null character in @source - it alwa-
 ys copies exactly num bytes.
 To avoid overflows, the size of the arrays pointed by both the @destination and @so-
 urce parameters, shall be at least @num bytes.    
-----------------------------------------------------------------------------------*/
void * memmove ( void * destination, const void * source, size_t num );


void *memcpy(void *dest, const void *src, size_t n);

