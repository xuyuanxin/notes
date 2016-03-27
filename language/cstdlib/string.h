/*
http://baike.baidu.com/link?url=MgMV10yNWGeHr7g2BISO1HYk-P_3EwKXqIUSyUx_tWY2ug5MrRnNfdFOzbiuJqAFfzrKfAU5Uzalb3e4EZtiia#5_9
https://en.wikipedia.org/wiki/C_string_handling


*/

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
 Returns the length of the C string @str. The length of a C string is determined by -
 the terminating null-character: A C string is as long as the number of characters b-
 etween the beginning of the string and the terminating null character (without inclu-
 ding the terminating null character itself).
 ----------------------------------------------------------------------------------*/
size_t strlen ( const char *str );

/*-----------------------------------------------------------------------------------
功能：把src所指由NULL结束的字符串的前n个字节复制到dst所指的数组中。
返回：返回指向dst的指针（该指向dst的最后一个元素）
说明：如果src的前n个字节不含NULL字符，则结果不会以NULL字符结束。        
      如果src的长度小于n个字节，则以NULL填充dest直到复制完n个字节(所以拷贝效率低些)。        
      src和dest所指内存区域不可以重叠且dest必须有足够的空间来容纳src的字符串。        
-----------------------------------------------------------------------------------*/
char *strncpy(char *dst, const char *src, size_t n);

/*-----------------------------------------------------------------------------------
 @str1: C string to be compared.
 @str2: C string to be compared.
 @num : Maximum number of characters to compare.
 @Return
 return value	 indicates
 <0  the first character that does not match has a lower value in str1 than in str2
 =0	 the contents of both strings are equal
 >0  the first character that does not match has a greater value in str1 than in str2

 Compare characters of two strings. Compares up to @num characters of the C string  -
 @str1 to those of the C string @str2. This function starts comparing the first char-
 acter of each string. If they are equal to each other, it continues with the follow-
 ing pairs until the characters differ,until a terminating null-character is reached, 
 or until num characters match in both strings, whichever happens first.
 ----------------------------------------------------------------------------------*/
int strncmp ( const char * str1, const char * str2, size_t num );


/*-----------------------------------------------------------------------------------
 @str
    C string to truncate. Notice that this string is modified by being broken into s-
    maller strings (tokens). Alternativelly, a null pointer may be specified, in whi-
    ch case the function continues scanning where a previous successful call to the -
    function ended.
 @delimiters
    C string containing the delimiter characters. These can be different from one ca-
    ll to another.
 @return
    If a token is found, a pointer to the beginning of the token. Otherwise, a null -
    pointer. A null pointer is always returned when the end of the string (i.e., a n-
    ull character) is reached in the string being scanned.

 Split string into tokens. A sequence of calls to this function split @str into toke-
 ns, which are sequences of contiguous characters separated by any of the  characters 
 that are part of @delimiters. On a first call, the function expects a C string as a-
 rgument for @str, whose first character is used as the starting location to scan for 
 tokens. In subsequent calls, the function expects a null pointer and uses the posit-
 ion right after the end of the last token as the new starting location for scanning.

 To determine the beginning and the end of a token, the function first scans from the 
 starting location for the first character not contained in @delimiters (which becom-
 es the beginning of the token). And then scans starting from this beginning of the -
 token for the first character contained in @delimiters, which becomes the end of the 
 token. The scan also stops if the terminating null character is found.

 This end of the token is automatically replaced by a null-character, and the beginn-
 ing of the token is returned by the function. Once the terminating null character of
 @str is found in a call to strtok,all subsequent calls to this function (with a null 
 pointer as the first argument) return a null pointer.

 The point where the last token was found is kept internally by the function to be u-
 sed on the next call (particular library implementations are not required to avoid -
 data races).

 //strtok example 
 #include <stdio.h>
 #include <string.h>

 int main ()
 {
   char str[] ="- This, a sample string.";
   char * pch;
   printf ("Splitting string \"%s\" into tokens:\n",str);
   pch = strtok (str," ,.-");
   while (pch != NULL)
   {
     printf ("%s\n",pch);
     pch = strtok (NULL, " ,.-");
   }
   return 0;
 }

 Output:
 Splitting string "- This, a sample string." into tokens:
 This
 a
 sample
 string
 ----------------------------------------------------------------------------------*/
char *strtok( char * str, const char * delimiters );



/* strstr */
char *strcasestr(const char *haystack, const char *needle);

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
void *memset ( void *ptr, int value, size_t num );

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

 eg: strchr_eg()
-----------------------------------------------------------------------------------*/
const char * strchr ( const char * str, int character ); /* C++ */
	  char * strchr (		char * str, int character );  /* C++ */
	  char * strchr ( const char *, int ); /* C */

/*-----------------------------------------------------------------------------------
 The strstr() function finds the first occurrence of the substring @needle in the st-
 ring @haystack. The terminating null bytes ('\0') are not compared.

 The strcasestr() function is like strstr(), but ignores the case of both arguments.

 return a pointer to the beginning of the located substring, or NULL if the substring 
 is not found.
 ----------------------------------------------------------------------------------*/
char *strstr(const char *haystack, const char *needle);

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


/*-----------------------------------------------------------------------------------
http://pubs.opengroup.org/onlinepubs/009695399/functions/strdup.html
The strdup() function shall return a pointer to a new string, which is a duplicate of 
the string pointed to by s1. The returned pointer can be passed to free(). A null po-
inter is returned if the new string cannot be created.
-----------------------------------------------------------------------------------*/
char *strdup(const char *s1);







/*----------------------------------------------------------------------------------- 
 strlwr()和strupr()不是标准库函数，只能在windows下（VC、MinGW等）使用，Linux GCC中需
 要自己定义。
 strupr()用于将字符串中的字符转换为小写
 strlwr()用于将字符串中的字符转换为小写

 http://c.biancheng.net/cpp/html/2716.html
 -----------------------------------------------------------------------------------*/
char *strupr(char *str);
char *strlwr(char *str);

/*

 


*/
