struct stat 
{
    mode_t  st_mode; /* file type & mode (permissions) */
    ino_t  st_ino; /* i-node number (serial number) */
    dev_t  st_dev; /* device number (file system) */
    dev_t  st_rdev; /* device number for special files */
    nlink_t  st_nlink; /* number of links */
    uid_t  st_uid; /* user ID of owner */
    gid_t  st_gid; /* group ID of owner */
    off_t  st_size; /* size in bytes, for regular files */
    struct timespec st_atim; /* time of last access */
    struct timespec st_mtim; /* time of last modification */
    struct timespec st_ctim; /* time of last file status change */
    blksize_t  st_blksize; /* best I/O block size */
    blkcnt_t  st_blocks; /* number of disk blocks allocated */
};


/*

UNIX下可以用ls -l 命令来看到文件的权限。用ls命令所得到的表示法的格式是类似这样的：-rwxr-xr-x 。
这种表示方法一共有十位：

9 8 7 6 5 4 3 2 1 0 
- r w x r - x r - x

第9位表示文件类型,可以为p、d、l、s、c、b和-：
p表示命名管道文件 
d表示目录文件 
l表示符号连接文件 
-表示普通文件 
s表示socket文件 
c表示字符设备文件 
b表示块设备文件

第8-6位、5-3位、2-0位分别表示文件所有者的权限，同组用户的权限，其他用户的权限，其形式为rwx：
r表示可读，可以读出文件的内容
w表示可写，可以修改文件的内容
x表示可执行，可运行这个程序
没有权限的位置用-表示

如果一个文件被设置了SUID或SGID位，会分别表现在所有者或同组用户的权限的可执行位上。例如：
1、-rwsr-xr-x 表示SUID和所有者权限中可执行位被设置
2、-rwSr--r-- 表示SUID被设置，但所有者权限中可执行位没有被设置
3、-rwxr-sr-x 表示SGID和同组用户权限中可执行位被设置
4、-rw-r-Sr-- 表示SGID被设置，但同组用户权限中可执行位没有被社

其实在UNIX的实现中，文件权限用12个二进制位表示，如果该位置上的值是1，表示有相应的权限：

11 10 9 8 7 6 5 4 3 2 1 0 
S G T r w x r w x r w x

第11位为SUID位，第10位为SGID位，第9位为sticky位，第8-0位对应于上面的三组rwx位。
11 10 9 8 7 6 5 4 3 2 1 0

上面的-rwsr-xr-x的值为： 1 0 0 1 1 1 1 0 1 1 0 1
      -rw-r-Sr--的值为： 0 1 0 1 1 0 1 0 0 1 0 0

---->用户ID
用户ID是个整型数
实际用户ID(RUID), 用于在系统中标识一个用户是谁，当用户使用用户名和密码成功登录后一个UNIX系统后就唯一确定了他的RUID.
有效用户ID(RUID), 用于系统决定用户对系统资源的访问权限，通常情况下等于RUID。
设置用户ID(SUID)，用于对外权限的开放。跟RUID及EUID是用一个用户绑定不同，它是跟文件而不是跟用户绑定。

进程在运行的时候，有一些属性，其中包括 实际用户ID,实际组ID,有效用户ID,有效组ID等。 
实际用户ID和实际组ID标识我们是谁，谁在运行这个程序,一般这2个字段在登陆时决定，在一个登陆会话期间，这些值基本上不改变。
而有效用户ID和有效组ID则决定了进程在运行时的权限。内核在决定进程是否有文件存取权限时，是采用了进程的有效用户ID来进行判断的。
当一个程序设置了为SUID位时，内核就知道了运行这个程序的时候，应该认为是文件的所有者在运行这个程序。即该程序运行的时候，有效用户ID是该程序的所有者。
*/
/*
---->文件访问权限
u:表示用户(所有者)
g:表示组
o:表示其它
*/
#define S_IRUSR /*user-read*/
#define S_IWUSR /*user-write*/
#define S_IXUSR /*user-execute*/
#define S_IRGRP /*group-read*/
#define S_IWGRP /*group-write*/
#define S_IXGRP /*group-execute*/
#define S_IROTH /*other-read*/
#define S_IWOTH /*other-write*/
#define S_IXOTH /*other-execute*/


