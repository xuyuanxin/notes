#include <sys/stat.h>


/************************************************************************************
                          struct stat @st_mode
 ************************************************************************************
 the set-user-ID bit and the set-group-ID bit are contained in the file's st_mode value. 
 These two bits can be tested against the constants S_ISUID and S_ISGID, respectively.
************************************************************************************/
/* 文件类型(八进制)*/
#define S_IFMT	  0170000   /* 文件类型位域掩码 */
#define S_IFSOCK  0140000   /* 套接口 */
#define S_IFLNK   0120000   /* 符号链接 */
#define S_IFREG	  0100000   /* 普通文件 */
#define S_IFBLK   0060000   /* 块设备 */
#define S_IFDIR   0040000   /* 目录 */
#define S_IFCHR   0020000   /* 字符设备 */
#define S_IFIFO   0010000   /* FIFO */
/**/
#define S_ISUID   0004000   /* set-user-ID on execution */
#define S_ISGID   0002000   /* set-group-ID on execution */
#define S_ISVTX   0001000   /* saved-text (sticky bit) */

/*st_mode也包含了文件的访问权限位,下面是9个访问权限位*/
#define S_IRUSR   0000400   /* (S_IREAD)  read by user (owner) */
#define S_IREAD
#define S_IWUSR   0000200   /* (S_IWRITE) write by user (owner) */
#define S_IWRITE
#define S_IXUSR   0000100   /* (S_IEXEC)  execute by user (owner) */
#define S_IEXEC
#define S_IRGRP   0000040   /* read by group */
#define S_IWGRP   0000020   /* write by group */
#define S_IXGRP   0000010   /* execute by group */
#define S_IROTH   0000004   /* read by other (world) */
#define S_IWOTH   0000002   /* write by other (world) */
#define S_IXOTH   0000001   /* execute by other (world) */

/* Linux系统中还定义了几个权限组合：*/
#define S_IRWXU  (S_IRUSR|S_IWUSR|S_IXUSR) /* read, write, and execute by user (owner) */
#define S_IRWXO  (S_IWGRP|S_IWGRP|S_IXGRP) /* read, write, and execute by other (world) */
#define S_IRWXG  (S_IROTH|S_IWOTH|S_IXOTH) /* read, write, and execute by group */

/*以下宏的参数是stat结构中的st_mode*/
#define S_ISREG()  /*regular file*/
#define S_ISDIR()  /*directory file*/
#define S_ISCHR()  /*character special file*/
#define S_ISBLK()  /*block special file*/
#define S_ISFIFO() /*pipe or FIFO*/
#define S_ISLNK()  /*symbolic link*/
#define S_ISSOCK() /*socket*/

/*以下宏的参数是stat结构指针 */
#define S_TYPEISMQ()  /* message queue */
#define S_TYPEISSEM() /* semaphore */
#define S_TYPEISSHM() /* shared memory object */



/*
  若一目录具有sticky位(S_ISVTX)，则表示在此目录下的文件只能被该文件所有者、此目录所有
  者或root来删除或改名，在linux中，最典型的就是这个/tmp目录啦。
*/
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


/*******************************************************************************
 The dirent structure defined in <dirent.h> is implementation dependent.
 Implementations define the structure to contain at least the following two members:
 *******************************************************************************/
struct dirent
{
    ino_t d_ino; /* i-node number */
    char d_name[]; /* null-terminated filename */
}

/*DIR 结构体的原型为：struct_dirstream
  在linux系统中：*/
typedef struct __dirstream DIR;
struct __dirstream
{
    void *__fd; /* `struct hurd_fd' pointer for descriptor.   */
    char *__data; /* Directory block.   */
    int __entry_data; /* Entry number `__data' corresponds to.   */
    char *__ptr; /* Current pointer into the block.   */
    int __entry_ptr; /* Entry number `__ptr' corresponds to.   */
    size_t __allocation; /* Space allocated for the block.   */
    size_t __size; /* Total valid data in the block.   */
    __libc_lock_define (, __lock) /* Mutex lock for this structure.   */
};


#include <unistd.h>
#define F_OK 0 /* test if a file exists */
#define X_OK 1 /* test for execute permission */
#define W_OK 2 /* test for write permission */
#define R_OK 4 /* test for read permission */



/*
********************************************************************************
---->目录的读取
  Directories can be read by anyone who has access permission to read the 
directory. But only the kernel can write to a directory, to preserve file system 
sanity. the write permission bits and execute permission bits for a directory
determine if we can create new files in the directory and remove files from the
directory — they don't specify if we can write to the directory itself.
  The actual format of a directory depends on the UNIX System implementation and
the design of the file system. Earlier systems, such as Version 7, had a simple 
structure:each directory entry was 16 bytes, with 14 bytes for the filename and 
2 bytes for the i-node number. When longer filenames were added to 4.2BSD, each 
entry became variable length, which means that any program that reads a directory 
is now system dependent. To simplify the process of reading a directory, a set of 
directory routines were developed and are part of POSIX.1. Many implementations 
prevent applications from using the read function to access the contents of 
directories, thereby further isolating applications from the implementation-specific 
details of directory formats.
********************************************************************************
文件类型
1 普通文件(regular file)  
2 目录文件(directory file) 
  这种文件包含了其他文件的名字以及指向与这些文件有关信息的指针。
3 块特殊文件(block special file)
  这种文件类型提供对设备(例如磁盘)带缓冲的访问，每次访问固定长度为单位进行
4 字符特殊文件(character special file)
  这种文件类型提供对设备不带缓冲的访问，每次访问长度可变。
5 FIFO
6 套接字(socket)
7 符号链接(symbolic link)
  



********************************************************************************
UNIX下可以用ls -l 命令来看到文件的权限。用ls命令所得到的表示法的格式是类似这样的：
-rwxr-xr-x 。

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

第8-6位、5-3位、2-0位分别表示文件所有者的权限，同组用户的权限，其他用户的权限，其
形式为 rwx
r表示可读，可以读出文件的内容
w表示可写，可以修改文件的内容
x表示可执行，可运行这个程序
没有权限的位置用-表示

如果一个文件被设置了SUID或SGID位，会分别表现在所有者或同组用户的权限的可执行位上。
例如：
1、-rwsr-xr-x 表示SUID和所有者权限中可执行位被设置
2、-rwSr--r-- 表示SUID被设置，但所有者权限中可执行位没有被设置
3、-rwxr-sr-x 表示SGID和同组用户权限中可执行位被设置
4、-rw-r-Sr-- 表示SGID被设置，但同组用户权限中可执行位没有被设置

其实在UNIX的实现中，文件权限用12个二进制位表示，如果该位置上的值是1，表示有相应的
权限：
11  10  9  8 7 6  5 4 3  2 1 0 
 S   G  T  r w x  r w x  r w x

第11位为SUID位，第10位为SGID位，第9位为sticky位，第8-0位对应于上面的三组rwx位。
11 10 9 8 7 6 5 4 3 2 1 0

上面的-rwsr-xr-x的值为： 1 0 0 1 1 1 1 0 1 1 0 1
      -rw-r-Sr--的值为： 0 1 0 1 1 0 1 0 0 1 0 0

---->用户ID 用户ID是个整型数
实际用户ID(RUID):
    用于在系统中标识一个用户是谁，当用户使用用户名和密码成功登录后一个UNIX系统后就唯
    一确定了他的RUID.
有效用户ID(RUID):
    用于系统决定用户对系统资源的访问权限，通常情况下等于RUID。
设置用户ID(SUID):
    When we execute a program file, the effective user ID of the process is usually 
    the real user ID, and the effective group ID is usually the real group ID. Howev-
    er, we can also set a special flag in the file's mode word (st_mode) that says: "
    When this file is executed, set the effective user ID of the process to be the o-
    wner of the file (st_uid). " Similarly, we can set another bit in the file's mode 
    word that causes the effective group ID to be the group owner of the file (st_gid
    ). These two bits in the file's mode word are called the set-user-ID bit and the 
    set-group-ID bit.
    
   For example, if the owner of the file is the superuser and if the file's set-user-
   ID bit is set, then while that program file is running as a process, it has super-
   user privileges. This happens regardless of the real user ID of the process that 
   executes the file. 

   As an example, the UNIX System program that allows anyone to change his or her pa-
   ssword, passwd(1), is a set-user-ID program. This is required so that the program 
   can write the new password to the password file, typically either /etc/passwd or 
   /etc/shadow, files that should be writable only by the superuser. Because a proce-
   ss that is running set-user-ID to some other user usually assumes extra permissio-
   ns, it must be written carefully. 


实际组ID
有效组ID
设置组ID
附加组ID

进程在运行的时候，有一些属性，其中包括实际用户ID,实际组ID,有效用户ID,有效组ID等。
实际用户ID和实际组ID标识我们是谁，谁在运行这个程序,一般这2个字段在登陆时决定，在
一个登陆会话期间，这些值基本上不改变。而有效用户ID和有效组ID则决定了进程在运行时
的权限。内核在决定进程是否有文件存取权限时，是采用了进程的有效用户ID来进行判断的。
当一个程序设置了为SUID位时，内核就知道了运行这个程序的时候，应该认为是文件的所有
者在运行这个程序。即该程序运行的时候，有效用户ID是该程序的所有者。

---->
Every file has an owner and a group owner. The owner is specified by the st_uid memb-
er of the stat structure; the group owner, by the st_gid member.


---->文件访问权限
u:表示用户(所有者)
g:表示组
o:表示其它

*************************************************************************************
1 The first rule is that whenever we want to open any type of file by name, we   must 
  have execute permission in each directory mentioned in the name, including the cur-
  rent directory, if it is implied. This is why the execute permission bit for a dir-
  ectory is often called the search bit.

  For example, to open the file /usr/include/stdio.h, we need execute permission in 
  the directory /, execute permission in the directory /usr, and execute permission 
  in the directory /usr/include. We then need appropriate permission for the file it-
  self, depending on how we're trying to open it: read-only, read–write, and so on.
  
 If the current directory is /usr/include, then we need execute permission in the cu-
 rrent directory to open the file stdio.h. This is an example of the current directo-
 ry being implied, not specifically mentioned. It is identical to our opening the fi-
 le ./stdio.h.

 Note that read permission for a directory and execute permission for a directory me-
 an different things. Read permission lets us read the directory, obtaining a list of
 all the filenames in the directory. Execute permission lets us pass through the dir-
 ectory when it is a component of a pathname that we are trying to access.(We need to 
 search the directory to look for a specific filename.)

 Another example of an implicit directory reference is if the PATH environment varia-
 ble, specifies a directory that does not have execute permission enabled. In this c-
 ase, the shell will never find executable files in that directory.
 
2 The read permission for a file determines whether we can open an existing  file for 
  reading: the O_RDONLY and O_RDWR flags for the open function.
3 The write permission for a file determines whether we can open an existing file for 
  writing: the O_WRONLY and O_RDWR flags for the open function.
4 We must have write permission for a file to specify the O_TRUNC flag in the open f-
  unction.
5 We cannot create a new file in a directory unless we have write permission and exe-
  cute permission in the directory.
6 To delete an existing file, we need write permission and execute permission  in the 
  directory containing the file. We do not need read permission  or  write permission 
  for the file itself.
7 Execute permission for a file must be on  if we want to execute the file  using any 
  of the seven @exec functions. The file also has to be a regular file.

 The file access tests that the kernel performs each time a process opens, creates,or
 deletes a file depend on the owners of the file ( st_uid and st_gid ), the effective 
 IDs of the process (effective user ID and effective group ID), and the supplementary 
 group IDs of the process, if supported. The two owner IDs are properties of the file, 
 whereas the two effective IDs and the supplementary group IDs are properties of  the 
 process. The tests performed by the kernel are as follows:
 1 If the effective user ID of the process is 0 ( the superuser ), access is allowed. 
   This gives the superuser free rein throughout the entire file system.
 2 If the effective user ID of the process equals the owner ID of the file (i.e., th-
   e process owns the file), access is allowed if the appropriate user access permis-
   sion bit is set. Otherwise, permission is denied. By appropriate access permission 
   bit, we mean that if the process is opening the file for reading,the user-read bit 
   must be on. If the process is opening the file for writing,the user-write bit must 
   be on. If the process is executing the file, the user-execute bit must be on.
 3 If the effective group ID of the process or one of the supplementary group IDs  of 
   the process equals the group ID of the file, access is allowed if  the appropriate 
   group access permission bit is set. Otherwise, permission is denied.
 4 If the appropriate other access permission bit is set, access is allowed. Otherwi-
   se, permission is denied.
  
 These four steps are tried in sequence. Note that if the process owns the file (step 
 2), access is granted or denied based only on the user access permissions; the group 
 permissions are never looked at. Similarly, if the process does not own the file but 
 belongs to an appropriate group, access is granted or denied based only on the group 
 access permissions; the other permissions are not looked at.

********************************************************************************
Ownership of New Files and Directories
    The rules for the ownership of a new directory are identical to the rules in this 
    section for the ownership of a new file.

    The user ID of a new file is set to the effective user ID of the process. POSIX.1 
    allows an implementation to choose one of the following options to determine  the 
    group ID of a new file:
    1 The group ID of a new file can be the effective group ID of the process.
    2 The group ID of a new file can be the group ID of the directory in which the f-
      ile is being created.
  
    Using the second option—inheriting the directory's group ID—assures us that all 
    files and directories created in that directory will have the same group ID as t-
    he directory.This group ownership of files and directories will then propagate d-
    own the hierarchy from that point. This is used in the Linux directory /var/mail, 
    for example.
********************************************************************************
---->i节点
每一个新创建的文件分配一个Inode(索引结点),每个文件都有一个惟一的inode号
i节点中存放着:文件的所有者、文件所属的组、文件大小、文件数据块在盘上的位置等信息


---->目录项
目录项包括两个内容: i节点号和文件名

********************************************************************************
---->文件的三个时间字段
Field     Description                           Example       ls(1) option
st_atim   last-access time of file data         read          -u
st_mtim   last-modification time of file data   write         default
st_ctim   last-change time of i-node status     chmod,chown   -c

S_ISVTX bit
    The S_ISVTX bit has an interesting history. On versions of the UNIX System   that 
    predated demand paging, this bit was known as the sticky bit. If it was set   for 
    an executable program file, then the first time the program was executed, a  copy 
    of the program's text was saved in the swap area when the process terminated.(The 
    text portion of a program is the machine instructions.) The program would then l-
    oad into memory more quickly the next time it was executed, because the swap area 
    was handled as a contiguous file, as compared to the possibly random location  of 
    data blocks in a normal UNIX file system. The sticky bit was often set for common
    application programs, such as the text editor and the passes of the C compiler. N
    aturally, there was a limit to the number of sticky files that could be contained 
    in the swap area before running out of swap space, but it was a useful technique. 
    The name sticky came about because the text  portion  of the file stuck around in 
    the swap area until the system was rebooted. Later versions of the UNIX System r-
    eferred to this as the saved-text bit; hence the constant S_ISVTX. With today's n
    ewer UNIX systems, most of which have a virtual memory system and a faster file s
    ystem, the need for this technique has disappeared.
    
    On contemporary systems, the use of the sticky bit has been extended. The  Single
    UNIX Specification allows the sticky bit to be set for a directory. If the bit is 
    set for a directory, a file in the directory can be removed or renamed only if t-
    he user has write permission for the directory and meets one of the following cr-
    iteria:
        Owns the file 
        Owns the directory
        Is the superuser

    The directories /tmp and /var/tmp are typical candidates for the sticky bit—they 
    are directories in which any user can typically create files. The permissions for 
    these two directories are often read, write, and execute for everyone (user,group, 
    and other).But users should not be able to delete or rename files owned by others.
*************************************************************************************
硬链接的定义
    Linux 文件系统最重要的特点之一是它的文件链接。链接是对文件的引用，这样您可以让文件
    在文件系统中多处被看到。不过，在 Linux 中，链接可以如同原始文件一样来对待。链接可
    以与普通的文件一样被执行、编辑和访问。对系统中的其他应用程序而言，链接就是它所对应
    的原始文件。当您通过链接对文件进行编辑时，您编辑的实际上是原始文件。链接不是副本。
    有两种类型的链接：硬链接和符号链接(软链接)。硬链接只能引用同一文件系统中的文件。它
    引用的是文件在文件系统中的物理索引(也称为 inode)。当您移动或删除原始文件时，硬链接
    不会被破坏，因为它所引用的是文件的物理数据而不是文件在文件结构中的位置。硬链接的文
    件不需要用户有访问原始文件的权限，也不会显示原始文件的位置，这样有助于文件的安全。
    如果您删除的文件有相应的硬链接，那么这个文件依然会保留，直到所有对它的引用都被删除。
硬链接与软链接的区别
    在Linux的文件系统中，保存在磁盘分区中的文件不管是什么类型都给它分配一个编号，称为
    索引节点号inode 。软连接，其实就是新建立一个文件，这个文件就是专门用来指向别的文件
    的（那就和windows 下的快捷方式的那个文件有很接近的意味）。软链接产生的是一个新的文
    件，但这个文件的作用就是专门指向某个文件的，删了这个软连接文件，那就等于不需要这个
    连接，和原来的存在的实体原文件没有任何关系，但删除原来的文件，则相应的软连接不可用
    （cat那个软链接文件，则提示“没有该文件或目录“）
    硬连接是不会建立inode的，他只是在文件原来的inode link count域再增加1而已，也因此硬
    链接是不可以跨越文件系统的。相反都是软连接会重新建立一个inode，当然inode的结构跟其
    他的不一样，他只是一个指明源文件的字符串信息。一旦删除源文件，那么软连接将变得毫无
    意义。而硬链接删除的时候，系统调用会检查inode link count的数值，如果他大于等于1，那
    么inode不会被回收。因此文件的内容不会被删除。
    硬链接实际上是为文件建一个别名，链接文件和原文件实际上是同一个文件。可以通过ls -i来
    查看一下，这两个文件的inode号是同一个，说明它们是同一个文件；而软链接建立的是一个指
    向，即链接文件内的内容是指向原文件的指针，它们是两个文件。
    软链接可以跨文件系统，硬链接不可以；软链接可以对一个不存在的文件名(filename)进行链接
    （当然此时如果你vi这个软链接文件，linux会自动新建一个文件名为filename的文件）,硬链接
    不可以（其文件必须存在，inode必须存在）；软链接可以对目录进行连接，硬链接不可以。两种
    链接都可以通过命令 ln 来创建。ln 默认创建的是硬链接。使用 -s 开关可以创建软链接。

