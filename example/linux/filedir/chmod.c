#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>

/*-----------------------------------------------------------------------------------
$ ls -l foo bar
-rw------- 1 sar 0 Dec 7 21:20 bar
-rw-rw-rw- 1 sar 0 Dec 7 21:20 foo

$ ls -l foo bar
-rw-r--r-- 1 sar 0 Dec 7 21:20 bar
-rw-rwSrw- 1 sar 0 Dec 7 21:20 foo

 In this example, we have set the permissions of the file @bar to an absolute value ,
 regardless of the current permission bits. For the file @foo, we set the permissions
 relative to their current state. To do this, we first call @stat to obtain the curr-
 ent permissions and then modify them. We have explicitly turned on the set-group-ID 
 bit and turned off the group-execute bit. Note that the @ls command lists the group-
 execute permission as S to signify that the set-group-ID bit is set without the gro-
 up-execute bit being set.

 note that the time and date listed by the @ls command did not change after we ran t-
 he program. @chmod  function updates only the time that the i-node was last changed. 
 By default, the ls -l lists the time when the contents of the file were last modifi-
 ed.
-----------------------------------------------------------------------------------*/
int chmod_eg01()
{
    struct stat statbuf;
    
    /* turn on set-group-ID and turn off group-execute */
    if (stat("foo", &statbuf) < 0)
        printf("stat error for foo \r\n");
    
    if (chmod("foo", (statbuf.st_mode & ~S_IXGRP) | S_ISGID) < 0)
        printf("chmod error for foo \r\n");
    
    /* set absolute mode to "rw-r--r--" */
    if (chmod("bar", S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH) < 0)
        printf("chmod error for bar");
    
    return 0;
}

int main(void)
{
    chmod_eg01();
    exit(0);
}

