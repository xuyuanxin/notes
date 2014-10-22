#include <sys/stat.h>

/*******************************************************************************
 @pathname:文件名
 @buf     ;返回文件的相关信息
 return   : 0 if OK,-1 on error
*******************************************************************************/
int stat(const char *restrict pathname,struct stat *restrict buf);

/*******************************************************************************  
 @buf    ;返回文件的相关信息
 function:根据描述符@fd获取文件信息
 return  :0 if OK,-1 on error
*******************************************************************************/
int fstat(int fd,struct stat *buf);

/*******************************************************************************
 @pathname:文件名
 @buf     ;返回文件的相关信息
 function :when the named file is asymbolic link, @lstat returns information about 
           the symbolic link, not the file referenced by the symbolic link.  
 return   :0 if OK,-1 on error
*******************************************************************************/
int lstat(const char *restrict pathname,struct stat *restrict buf);

/*return: 0 if OK,-1 on error*/
int fstatat(intfd,const char *restrict pathname, struct stat *restrict buf,int flag);


#include <unistd.h>
/*return: 0 if OK,-1 on error
These two functions truncate an existing file to @length bytes. If the previous size of the
file was greater than length,the data beyond @length is no longer accessible. Otherwise, if
the previous size was less than @length,the file size will increase and the data between
the old end of file and the new end of file will read as 0 (i.e., a hole is probably created
in the file).*/
int truncate(const char *pathname,off_t length);

/*return: 0 if OK,-1 on error*/
int ftruncate(int fd,off_t length);



