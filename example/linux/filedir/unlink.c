#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

int main(void)
{
    if (open("tempfile", O_RDWR) < 0){
        printf("open error");
		return -1;
    }	
    if (unlink("tempfile") < 0) {
        printf("unlink error");
		return -1;
    }
    printf("file unlinked\n");
    sleep(15);
    printf("done\n");
    exit(0);
}

/*
Running this program gives us
$ ls -l tempfile                      <---look at how big the file is
-rw-r----- 1 sar 413265408 Jan 21 07:14 tempfile
$ df /home                            <---check how much free space is available
Filesystem 1K-blocks Used Available Use% Mounted on
/dev/hda4 11021440 1956332 9065108 18% /home
$ ./a.out &                           <---run the program in the background
1364                                  <---the shell prints its process ID
$ file unlinked                       <---the file is unlinked
ls -l tempfile                        <---see if the filename is still there
ls: tempfile: No such file or directory the directory   <---entry is gone
$ df /home                            <---see if the space is available yet
Filesystem 1K-blocks Used Available Use% Mounted on
/dev/hda4 11021440 1956332 9065108 18% /home
$ done                                <---the program is done, all open files are closed
df /home                              <---now the disk space should be available
Filesystem 1K-blocks Used Available Use% Mounted on
/dev/hda4 11021440 1552352 9469088 15% /home
                                      <---now the 394.1 MB of disk space are available


This property of @unlink is often used by a program to ensure that a temporary file it 
creates won't be left around in case the program crashes. The process creates a file
using either open or creat and then immediately calls unlink. The file is not deleted,
however, because it is still open. Only when the process either closes the file or
terminates, which causes the kernel to close all its open files, is the file deleted.

If pathname is a symbolic link,@unlink removes the symbolic link,not the file referenced 
by the link. There is no function to remove the file referenced by a symbolic link given 
the name of the link.

The superuser can call @unlink with pathname specifying a directory if the file system 
supports it, but the function @rmdir should be used instead to unlink a directory

