#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

#define RWRWRW (S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP|S_IROTH|S_IWOTH)

/*-----------------------------------------------------------------------------------
 The program creates two files: one with a umask of 0 and one with a umask that disa-
 bles all the group and other permission bits.

$ umask                 <---- first print the current file mode creation mask
002
$ ./a.out
$ ls -l foo bar
-rw------- 1 sar 0 Dec 7 21:20 bar
-rw-rw-rw- 1 sar 0 Dec 7 21:20 foo
$ umask                <---- see if the file mode creation mask changed
002

 we use the shell's umask command to print the file mode creation mask both before we 
 run the program and after it completes. This shows us that changing the file mode c-
 reation mask of a process doesn't affect the mask of its parent (often a shell). All 
 of the shells have a built-in umask command that we can use to set or print the cur-
 rent file mode creation mask.
-----------------------------------------------------------------------------------*/
int umask_eg01()
{
    umask(0);
	
    if (creat("foo", RWRWRW) < 0)
        printf("creat error for foo");
	
    umask(S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
	
    if (creat("bar", RWRWRW) < 0)
        printf("creat error for bar");
	
	return 0;
}

int main(void)
{
	umask_eg01();	
    exit(0);
}
