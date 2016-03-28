
#include <stdio.h>
#include <wchar.h>
/*******************************************************************************
 @mode:
 negative,fwide will try to make the specified stream byte oriented.
 positive,fwide will try to make the specified stream wide oriented.
 zero,fwide will not try to set the orientation, but will still return a value 
 identifying the streams orientation.

 Note that @fwidewill not change the orientation of a stream that is already 
 oriented.Also note that there is no error return. Consider what would happen 
 if the stream is invalid. The only recourse we have is to clear errno before 
 calling @fwide and check the value of errno when we return.

 Returns: positive if stream is wide oriented, negative if stream is byte oriented, 
 or 0 if stream has no orientation
 *******************************************************************************/
int fwide(FILE *fp,int mode);


/*******************************************************************************
 设置流的缓冲类型
 @fp:
 @buf:point to a buffer of length BUFSIZ( defined in<stdio.h>)
 returns: 0 if OK, non zero on error

 With @setbuf, we can turn buffering on or off.  To enable buffering,@buf must 
 point to a buffer of length BUFSIZ,aconstant defined in<stdio.h>.Normally,the 
 stream is then fully buffered, but some systems may set line buffering if the 
 stream is associated with a terminal device.To disable buffering, we set @buf 
 to NULL.
 1 must be called after the stream has been opened
 2 before any other operation is performed on the stream.
 *******************************************************************************/
void setbuf(FILE *restrict fp,char *restrict buf);

/*******************************************************************************
 @fp  :
 @buf :缓冲区指针
 @mode:缓冲区模式
 @size:缓冲区大小
 function:设置流的缓冲类型
 return  :0 if OK, non zero on error

 mode argument:
 _IOFBF fully buffered
 _IOLBF line buffered
 _IONBF unbuffered

 If we specify an unbuffered stream, the @buf and @size arguments are ignored. 
 If we specify fully buffered or line buffered,@buf and @size can optionally 
 specify a buffer and its size.	If the stream	is buffered  and buf is NULL,the 
 standardI/O library will automatically allocate its own buffer	of the appropriate  
 size for the stream.
 By appropriate size, we mean the value specified by the constant BUFSIZ.
 *******************************************************************************/
int setvbuf(FILE *restrict fp,char *restrict buf,int mode, size_t size);

#include <stdio.h>
/*******************************************************************************
 The @fflush function causes any unwritten data for the stream to be passed to 
 the kernel. As a special case, if fp is NULL,@fflush causes all output streams 
 to be flushed.

 Returns: 0 if OK,EOF on error
*******************************************************************************/
int fflush(FILE *fp);

/*******************************************************************************

fdopen:
return: All three return file pointer if OK,NULL on error

Both fopen and freopen are part of ISO C;fdopen is part of POSIX.1, since ISO C doesn’t deal with file descriptors

---->关于type

*/
/*******************************************************************************
 function:opens a specified file. 
 return  :return file pointer if OK,NULL on error
 *******************************************************************************/
FILE *fopen(const char *restrict pathname,const char *restrict type);

/*******************************************************************************
 function:opens a specified file on a specified stream, closing the stream first 
          if it is already open. If the stream previously had an orientation,
          @freopen clears it. This function is typically used to open a specified 
          file as one of the predefined streams: standardinput, standardoutput, 
          or standarderror.
 return  :return file pointer if OK,NULL on error
 *******************************************************************************/
FILE *freopen(const char *restrict pathname,const char *restrict type,FILE *restrict fp);

/*******************************************************************************
 function:takes an existing file descriptor,which we could obtain from the open,
          dup,dup2,fcntl,pipe,socket,socketpair,or accept functions,and associates
          a standard I/O stream with the descriptor.This function is often used 
          with descriptors that are returned by the functions that create pipes 
          and network communication channels. Because these special types of files
          cannot be opened with the standard I/O fopen function, we have to call 
          the device-specific function to obtain a file descriptor,and then 
          associate this descriptor with a standardI/O stream usingfdopen.
 return  :return file pointer if OK,NULL on error
 *******************************************************************************/
FILE *fdopen(int fd,const char *type);


/*******************************************************************************
 Three functions allow us to read one character at a time.
 The function getchar is defined to be equivalent to getc(stdin)
 @getc can be implemented as a macro,@fgetc cannot be implemented as a macro

 All three return: next character if OK,EOF on end of file or error
 ******************************************************************************/
int getc(FILE *fp);
int fgetc(FILE *fp);
int getchar(void);

/*******************************************************************************
 In most implementations, two flags are maintained for each stream in the FILE 
 object:An error flag An end-of-file flag
 @getc @fgetc @getchar return the same value whether an error occurs or the end
 of file is reached.To distinguish between the two, we must call either @ferror 
 or @feof.@ferror表示这个流出错返回，@feof遇到结束符返回

 Both return: nonzero(true) if condition is true, 0 (false) otherwise
 ******************************************************************************/
int ferror(FILE *fp);
int feof(FILE *fp);

/*******************************************************************************
 In most implementations, two flags are maintained for each stream in the FILE 
 object:An error flag An end-of-file flag
 Both flags are cleared by calling @clearerr.
 ******************************************************************************/
void clearerr(FILE *fp);

/*******************************************************************************
 从流中读取数据后可以调用@ungetc再压回流中。一次只能压回一个字符，可以多次压回。
 压回的字符不一定是刚读取得，可以是除EOF外的任意字符。压回多个字符再读取时，读取
 的顺序和压回的顺序相反。
 
 When we reach the end of file, however,we can push back a character.The next 
 read will return that character,and the read after that will return EOF.
 
 When we push characters back with @ungetc,they are not written back to the 
 underlying file or device. Instead, they are kept incore in the standardI/O 
 library's buffer for the stream.

 returns:c if OK,EOF on error 
 ******************************************************************************/
int ungetc(int c,FILE *fp);


/*******************************************************************************
 putchar(c) is equivalent to putc(c, stdout),
 @putc can be implemented as a macro, @fputc cannot be implemented as a macro.

 All three return:c if OK,EOF on error
 ******************************************************************************/
int putc(int c,FILE *fp);
int fputc(int c,FILE *fp);
int putchar(int c);

/*-----------------------------------------------------------------------------------
 @str
    Pointer to an array of chars where the string read is copied.
 @num
    Maximum number of characters to be copied into str (including the terminating   -
    null-character).
 @stream
    Pointer to a FILE object that identifies an input stream. @stdin can be used as -
    argument to read from the standard input.
 @return
    On success, the function returns @str. If the end-of-file is encountered while a-
    ttempting to read a character, the eof indicator is set (feof). If this happens -
    before any characters could be read, the pointer returned is a null pointer ( and 
    the contents of str remain unchanged). If a read error occurs, the error indicat-
    or (ferror) is set and a null pointer is also returned ( but the contents pointed 
    by str may have changed).

 #include <stdio.h>

 int main()
 {
    FILE * pFile;
    char mystring [100];

    pFile = fopen ("myfile.txt" , "r");
    if (pFile == NULL) 
    {
      perror ("Error opening file");
    } 
    else 
    {
      if ( fgets (mystring , 100 , pFile) != NULL )
        puts (mystring);
      fclose (pFile);
    }
    return 0;
 }

 This example reads the first line of myfile.txt or the first 99 characters, whichev-
 er comes first, and prints them on the screen. 

 example: fgets_eg()
 ----------------------------------------------------------------------------------*/
char *fgets ( char *str, int num, FILE *stream );

/*******************************************************************************
 @buf:存放读取的字符 reads from standard input
 return:buf if OK,NULL on end of file or erro

 gets:不推荐使用，可能造成缓冲区溢出。另外gets不读取换行符。
 ******************************************************************************/
char *gets(char *buf);


/*******************************************************************************
 writes the null-terminated string to the specified stream.The null byte at the 
 end is not written. 
 string need not contai  a newline as the last non-null character.

 return: non-negative value if OK,EOF on error
 ******************************************************************************/
int fputs(const char *restrict str,FILE *restrict fp);

/*******************************************************************************
 writes the null-terminated string to the standard output, without writing the 
 null byte. But @puts then writes a newline character to the standard output.
 string need not contai  a newline as the last non-null character.

 return: non-negative value if OK,EOF on error
 ******************************************************************************/
int puts(const char *str);


/*-----------------------------------------------------------------------------------
 The function fileno converts a standard I/O file pointer into its corresponding des-
 criptor.
 ----------------------------------------------------------------------------------*/
int fileno( FILE *stream );

/*******************************************************************************
 @ptr:
 function:以结构为单位读
 return: number of objects read

 For the read case,return value can be less than @nobj if an error occurs or if 
 the end of file is encountered. 
 ******************************************************************************/
size_t fread(void *restrict ptr,size_t size,size_t nobj,FILE *restrict fp);

/*******************************************************************************
 @ptr    : 存放要写的数据
 @size   : 一个结构的大小
 @nobj   : 要写的结构的个数
 function: 以结构为单位写
 return: number of objects written

 1 如果返回值小于@nobj认为出错

 A fundamental problem with binary I/O is that it can be used to read only data 
 that has been written on the same system. This was OK many years ago, when all 
 the UNIX systems were PDP-11s, but the norm today is to have heterogeneous 
 systems connected together with networks. It is common to want to write data 
 on one system and process it on another.These two functions won't work, for 
 two reasons.
 1 The offset of a	 member within a  structure can differ between compilers and
 systems because of different alignment requirements.Indeed,some compilers have 
 an option allowing structures to be packed tightly,to save space with a possible 
 runtime	performance penalty,or aligned accurately, to optimize runtime access 
 of each member.This means that even on a single system, the binary layout of a 
 structurecan differ,depending on compiler options.
 2.  The binary formats used to	store multibyte integers and  floating-point values
 differ among machine architectures. We'll touch on some of these issues when we 
 discuss sockets. The real solution for exchanging binary data among different 
 systems is to use an agreed-upon canonical format. 
 *******************************************************************************/
size_t fwrite(const void *restrict ptr,size_t size,size_t nobj,FILE *restrict fp);

/*Returns: current file position indicator if OK,-1L on error*/
long ftell(FILE *fp);

/*******************************************************************************
 @whence: lseek
 *******************************************************************************/
int fseek(FILE *fp,long offset,int whence);

/*******************************************************************************
 功能:将文件内部的位置指针重新指向一个流（数据流/文件）的开头

 Returns: 0 if OK,-1 on error
 ******************************************************************************/
void rewind(FILE *fp);

/*Returns: current file position indicator if OK,(off_t)-1 on error*/
off_t ftello(FILE *fp);

/*Returns: 0 if OK,-1 on error*/
int fseeko(FILE *fp,off_t offset,int whence);

/*return: 0 if OK, nonzero on error*/
int fgetpos(FILE *restrict fp,fpos_t *restrict pos);

/*return: 0 if OK, nonzero on error*/
int fsetpos(FILE *fp,const fpos_t *pos);

#define L_tmpnam
#define TMP_MAX

/*******************************************************************************
 @ptr;@tmpnam创建一个临时文件，ptr存放这个文件的名字
 returns: pointer to unique pathname

 1 每次调用都会产生一个新的文件，最多调用TMP_MAX次
 2 @ptr可以为NULL，所产生的路径名放在一个静态区中，返回值是这个静态区的地址，再
   次用NULL调用@tmpnam时，会重写该静态区
 3 若@ptr不是NULL，则认为它指向长度至少是L_tmpnam个字符的数组
 ******************************************************************************/
char *tmpnam(char *ptr);

/*******************************************************************************
 功能: 创建一个临时二进制文件(类型wb+)，关闭该文件或程序结束时自动删除。
 Returns: file pointer if OK, NULL on error
 ******************************************************************************/
FILE *tmpfile(void);

/*return: number of characters output if OK, negative value if output error*/
int printf(const char *restrict format, . ..);

/*return: number of characters output if OK, negative value if output error*/
int fprintf(FILE *restrict fp, const char *restrict format, . ..);

/*return: number of characters output if OK, negative value if output error*/
int dprintf(int fd, const char *restrict format, . ..);

/*Returns: number of characters stored in array if OK, negative value if encoding error*/
int sprintf(char *restrict buf, const char *restrict format, . ..);

/*-----------------------------------------------------------------------------------
 The snprintf function returns the number of characters that would have been  written 
 to the buffer had it been big enough. As with sprintf, the return value doesn't inc-
 lude the terminating null byte. If snprintf returns a positive value less than the -
 buffer size @n, then the output was not truncated. If an encoding error occurs,    -
 snprintf returns a negative value.
 ----------------------------------------------------------------------------------*/
int snprintf(char *restrict buf, size_t n,const char *restrict format, . ..);

#include <stdarg.h>
#include <stdio.h>
/*return: number of characters output if OK, negative value if output error*/
int vprintf(const char *restrict format, va_list arg);

/*return: number of characters output if OK, negative value if output error*/
int vfprintf(FILE *restrict fp, const char *restrict format,va_list arg);

/*return: number of characters output if OK, negative value if output error*/
int vdprintf(int fd, const char *restrict format, va_list arg);

/*Returns: number of characters stored in array if OK, negative value if encoding error*/
int vsprintf(char *restrict buf, const char *restrict format,va_list arg);

/*-----------------------------------------------------------------------------------
 @s
    Pointer to a buffer where the resulting C-string is stored. The buffer should ha-
    ve a size of at least n characters.
 @n
    Maximum number of bytes to be used in the buffer. The generated string has a len-
    gth of at most n-1, leaving space for the additional terminating null character.
 @format
    C string that contains a format string that follows the same specifications as f-
    ormat in printf (see printf for details).
 @arg
    A value identifying a variable arguments list initialized with va_start.
 @return
    The number of characters that would have been written if n had been  sufficiently 
    large, not counting the terminating null character. If an encoding error  occurs, 
    a negative number is returned. Notice that only when this returned value is     -
    non-negative and less than n, the string has been completely written.

 Write formatted data from variable argument list to sized buffer

 {
	va_list ap;
	int n=0;
	va_start(ap, fmt); //获得可变参数列表
	n=vsnprintf (s, size, fmt, ap); //写入字符串s
	va_end(ap); //释放资源
	return n; //返回写入的字符个数
 }

 example: sa_log.c
 -----------------------------------------------------------------------------------*/
int vsnprintf (char * s, size_t n, const char * format, va_list arg );

#include <stdio.h>
/*return: number of input items assigned,
EOF if input error or end of file before any conversion*/
int scanf(const char *restrict format, . ..);

/*return: number of input items assigned,
EOF if input error or end of file before any conversion*/
int fscanf(FILE *restrict fp, const char *restrict format, . ..);

/*return: number of input items assigned,
EOF if input error or end of file before any conversion*/
int sscanf(const char *restrict buf, const char *restrict format, . ..);



#include <stdarg.h>
#include <stdio.h>
/*return: number of input items assigned,
EOF if input error or end of file before any conversion*/
int vscanf(const char *restrict format, va_list arg);

/*return: number of input items assigned,
EOF if input error or end of file before any conversion*/
int vfscanf(FILE *restrict fp, const char *restrict format,va_list arg);

/*return: number of input items assigned,
EOF if input error or end of file before any conversion*/
int vsscanf(const char *restrict buf, const char *restrict format,va_list arg);

#include <stdio.h>
/************************************************************************************
 The @perror function produces an error message on the standard error, based on the 
 current value of @errno, and returns.
 It outputs the string pointed to by @msg, followed by a colon and a space, followed 
 by the error message corresponding to the value of @errno, followed by a newline.
************************************************************************************/
void perror(const char *msg);

