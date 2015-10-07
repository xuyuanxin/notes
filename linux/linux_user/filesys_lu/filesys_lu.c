#include <sys/stat.h>

/*-----------------------------------------------------------------------------------
 @pathname:
 @buf     ;
    The @buf argument is a pointer to a structure that we must supply. The functions 
    fill in the structure. The definition of the structure can differ among implemen-
    tations, (struct stat) 
 @func
    Given a @pathname, the @stat function returns a structure of information about t-
    he named file. 
 @return   : 
    0 if OK,-1 on error

 example: stat_eg01()
-----------------------------------------------------------------------------------*/
int stat(const char *restrict pathname,struct stat *restrict buf);

/*----------------------------------------------------------------------------------- 
 @fd
 @buf
    the same as stat
 @func
    The @fstat function obtains information about the file that is already open on t-
    he descriptor @fd.
 @return
    0 if OK,-1 on error
-----------------------------------------------------------------------------------*/
int fstat(int fd,struct stat *buf);

/*-----------------------------------------------------------------------------------
 @pathname:
 @buf
    the same as stat
 @func :
    when the named file is asymbolic link, @lstat returns information about the symb-
    olic link, not the file referenced by the symbolic link.  
 @return   :
    0 if OK,-1 on error
-----------------------------------------------------------------------------------*/
int lstat(const char *restrict pathname,struct stat *restrict buf);

/*return: 0 if OK,-1 on error*/
int fstatat(intfd,const char *restrict pathname, struct stat *restrict buf,int flag);

/*return: 0 if OK, -1 on error*/
int faccessat(int fd, const char *pathname, int mode, int flag);


/*-----------------------------------------------------------------------------------
 @cmask : S_IRUSR ~ S_IXOTH
    Any bits that are on in the file mode creation mask are turned off in the file's 
    mode.
 @func
    sets the file mode creation mask for the process and returns the previous value. 
 @returns: 
    previous file mode creation mask

 example: umask_eg01()
-----------------------------------------------------------------------------------*/
mode_t umask(mode_t cmask);

#include <sys/stat.h>


/*-----------------------------------------------------------------------------------
 @mode:
    bitwise OR of the constants:S_ISUID S_ISGID S_ISVTX, S_IRUSR ~ S_IXOTH
 @return  : 
    0 if OK, -1 on error

 The @chmod, @fchmod, and @fchmodat functions allow us to change the file access per-
 missions for an existing file. The @chmod function operates on the specified file, 
 whereas the @fchmod function operates on a file that has already been opened. To ch-
 ange the permission bits of a file, the effective user ID of the process must be eq-
 ual to the owner ID of the file, or the process must have superuser permissions.

 example: chmod_eg01()
-----------------------------------------------------------------------------------*/
int chmod(const char *pathname, mode_t mode);
int fchmod(int fd, mode_t mode);
int fchmodat(int fd, const char *pathname, mode_t mode, int flag);


#include <unistd.h>
#define R_OK /*test for read permission*/
#define W_OK /*test for write permission*/
#define X_OK /*test for execute permission*/

/*-----------------------------------------------------------------------------------
 @mode : 
    The @mode is either the value F_OK to test if a file exists, or the bitwise OR of 
    any of the flags:R_OK W_OK X_OK
 return: 0 if OK, -1 on error
 功能  : 根据文件@pathname的实际用户ID，判断文件的权限

 when we open a file, the kernel performs its access tests based on the effective us-
 er and group IDs. Sometimes, however, a process wants to test accessibility based on 
 the real user and group IDs. This is useful when a process is running as someone el-
 se, using either the set-user-ID or the set-group-ID feature. Even though a process 
 might be set-user-ID to root, it might still want to verify that the real user can 
 access a given file. The @access and @faccessat functions base their tests on the r-
 eal user and group IDs. 

 example: access_eg01()
-----------------------------------------------------------------------------------*/
int access(const char *pathname, int mode);

/*******************************************************************************
 @owner  : -1表示不变
 @group  : -1表示不变
 function: 更改文件的所有者
 return  : 0 if OK, -1 on error
*******************************************************************************/
int chown(const char *pathname, uid_t owner, gid_t group);

/*return: 0 if OK, -1 on error*/
int fchown(int fd, uid_t owner, gid_t group);

/*return: 0 if OK, -1 on error*/
int fchownat(int fd, const char *pathname, uid_t owner, gid_t group,int flag);

/*******************************************************************************
 @owner  : -1表示不变
 @group  : -1表示不变
 function: 更改文件的所有者
 return  : 0 if OK, -1 on error

 如果文件是符号链，@lchown更改符号链接本身的所有者。
*******************************************************************************/
int lchown(const char *pathname, uid_t owner, gid_t group);



#include <unistd.h>
/*******************************************************************************
return: 0 if OK,-1 on error
These two functions truncate an existing file to @length bytes. If the previous 
size of the file was greater than length,the data beyond @length is no longer 
accessible. Otherwise, if the previous size was less than @length,the file size 
will increase and the data between the old end of file and the new end of file 
will read as 0 (i.e., a hole is probably created in the file).
*******************************************************************************/
int truncate(const char *pathname,off_t length);

/*return: 0 if OK,-1 on error*/
int ftruncate(int fd,off_t length);


#include <unistd.h>
/************************************************************************************
 @function:
    create a new directory entry, @newpath, that references the existing file 
    @existingpath. (hard link)
 @return: 
    0 if OK, -1 on error

 a file can have multiple directory entries pointing to its i-node. We can use either 
 the @link function or the @linkat function to create a link to an existing file.

 1 If the @newpath already exists, an error is returned
 2 Only the last component of the @newpath is created.The rest of the path must already 
   exist.
 3 创建新目录项及增加链接计数应当是个原子操作
 4 大多数实现要求这两个路径名在同一个文件系统中
 5 如果支持创建指向目录的硬链接，也仅限于超级用户这样做，这样做可能在文件系统中
   形成循环，因此很多文件系统不允许对与目录的硬链接
************************************************************************************/
int link(const char *existingpath, const char *newpath);

/*******************************************************************************
 return: 0 if OK, -1 on error
*******************************************************************************/
int linkat(int efd, const char *existingpath, int nfd, const char *newpath,int flag);


/************************************************************************************
 @function: 
    remove the directory entry and decrement the link count of the file referenced by 
    @pathname. If there are other links to the file, the data in the file is still 
    accessible through the other links. The file is not changed if an error occurs.
 @return  :
    0 if OK, -1 on error

 1 @unlink删除目录项，并将由@pathname所引用文件的链接计数减1
 2 为了解除对文件的链接，必须对包含该目录项的目录具有写和执行权限。if the sticky bit 
   is set in this directory we must have write permission for the directory and meet 
   one of the following criteria:
   a) Own the file
   b) Own the directory
   c) Have superuser privileges
 3 如果@pathname是符号链接，@unlink删除该符号链接，而不会删除由该链接所引用的文件。
 4 The superuser can call @unlink with pathname specifying a directory if the file
   system supports it, but the function rmdir should be used instead to unlink a 
   directory
 5 Only when the link count reaches 0 can the contents of the file be deleted.One other 
   condition prevents the contents of a file from being deleted:as long as some process 
   has the file open, its contents will not be deleted.When a file is closed,the kernel 
   first checks the count  of the number of processes  that have the file open. If this 
   count has  reached 0, the kernel then  checks the link count; if it is 0, the file's 
   contents are deleted.
 ***********************************************************************************/
int unlink(const char *pathname);

/*return: 0 if OK, -1 on error*/
int unlinkat(int fd, const char *pathname, int flag);


#include <stdio.h>
/*******************************************************************************
 We can also unlink a file or a directory with the @remove function. For a file,
 @remove is identical to @unlink. For a directory, @remove is identical to @rmdir.

 returns: 0 if OK, -1 on error
*******************************************************************************/
int remove(const char *pathname);

#include <stdio.h>
/*******************************************************************************
 return: 0 if OK, -1 on error
*******************************************************************************/
int rename(const char *oldname, const char *newname);

/*return: 0 if OK, -1 on error*/
int renameat(int oldfd, const char *oldname, int newfd, const char *newname);


#include <unistd.h>
/*return: 0 if OK, -1 on error*/
int symlink(const char *actualpath, const char *sympath);

/*return: 0 if OK, -1 on error*/
int symlinkat(const char *actualpath, int fd, const char *sympath);

#include <unistd.h>
/*return: number of bytes read if OK, -1 on error*/
ssize_t readlink(const char* restrict pathname, char *restrict buf,size_t bufsize);

/*return: number of bytes read if OK, -1 on error*/
ssize_t readlinkat(int fd, const char* restrict pathname,char *restrict buf, size_t bufsize);

#include <sys/stat.h>
/*return: 0 if OK, -1 on error*/
int futimens(int fd, const struct timespec times[2]);

/*return: 0 if OK, -1 on error*/
int utimensat(int fd, const char *path, const struct timespec times[2],int flag);


#include <sys/time.h>
/*Returns: 0 if OK, -1 on error*/
int utimes(const char *pathname, const struct timeval times[2]);

#include <sys/stat.h>
/*******************************************************************************
 function: create a new, empty directory. The entries for dot and dot-dot are
           created automatically. 
 return  : 0 if OK, -1 on error
 *******************************************************************************/
int mkdir(const char *pathname, mode_t mode);


int mkdirat(int fd, const char *pathname, mode_t mode);


#include <unistd.h>
/*******************************************************************************
 function: An empty directory is deleted with the rmdir function. Recall that an 
           empty directory is one that contains entries only for dot and dot-dot.
 return  : 0 if OK, -1 on error
 
 If the link count of the directory becomes 0 with this call, and if no other 
 process has the directory open, then the space occupied by the directory is 
 freed. If one or more processes have the directory open when the link count 
 reaches 0, the last link is removed and the dot and dot-dot entries are removed 
 before this function returns.Additionally, no new files can be created in the 
 directory. The directory is not freed,however, until the last process closes it. 
 (Even though some other process has the directory open, it can’t be doing much 
 in the directory, as the directory had to be empty for the rmdir function to 
 succeed.)
 *******************************************************************************/
int rmdir(const char *pathname);



#include <dirent.h>


/*******************************************************************************
 The DIR structure is an internal structure used by these seven functions to 
 maintain information about the directory being read. The purpose of the DIR 
 structure is similar to that of the FILE structure maintained by the standard 
 I/O library, which we describe in Chapter 5.
*******************************************************************************/

/*-----------------------------------------------------------------------------------
 The opendir() function opens a directory stream corresponding to the directory     -
 @pathname, and returns a pointer to the directory stream. The stream is positioned -
 at the first entry in the directory.

 return: pointer if OK, NULL on error
-----------------------------------------------------------------------------------*/
DIR *opendir(const char *pathname);

/*return: pointer if OK, NULL on error*/
DIR *fdopendir(int fd);

/*-----------------------------------------------------------------------------------
 The readdir() function returns a pointer to a @dirent structure representing the ne-
 xt directory entry in the directory stream pointed to by @dp. It returns NULL on re-
 aching the end of the directory stream or if an error occurred.
 ----------------------------------------------------------------------------------*/
struct dirent *readdir(DIR *dp);

void rewinddir(DIR *dp);

/*-----------------------------------------------------------------------------------
 The closedir() function closes the directory stream associated with @dp. A successf-
 ul call to closedir() also closes the underlying file descriptor associated with @dp
 . The directory stream descriptor @dp is not available after this call. The function 
 returns 0 on success.  On error, -1 is returned, and errno is set appropriately.
 ----------------------------------------------------------------------------------*/
int closedir(DIR *dp);

/*Returns: current location in directory associated with dp*/
long telldir(DIR *dp);

void seekdir(DIR *dp, long loc);

#include <unistd.h>
/*******************************************************************************
 function: 更改当前工作目录为@pathname
 return  : 0 if OK, -1 on error
 ******************************************************************************/
int chdir(const char *pathname);

/*******************************************************************************
 function: 更改当前工作目录为@fd
 return: 0 if OK, -1 on error
 ******************************************************************************/
int fchdir(int fd);


#include <unistd.h>

/*******************************************************************************
 @buf   : 存放当前工作目录(据对路径)
 @size  : @buf的长度
 returns: buf if OK, NULL on error
 
 pass to this function the address of a buffer, @buf, and its size (in bytes). 
 The buffer must be large enough to accommodate the absolute pathname plus a 
 terminating null byte, or else an error will be returned.

 What we need is a function that starts at the current working directory (dot) 
 and works its way up the directory hierarchy, using dot-dot to move up one 
 level. At each level, the function reads the directory entries until it finds 
 the name that corresponds to the i-node of the directory that it just came 
 from. Repeating this procedure until the root is encountered yields the entire
 absolute pathname of the current working directory. Fortunately, a function 
 already exists that does this work for us.
 ******************************************************************************/
char *getcwd(char *buf, size_t size);



