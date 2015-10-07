#include <sys/types.h>
#include <dirent.h>
#include <unistd.h>

int main()
{
    DIR * dir;
    struct dirent * ptr;
    int i;
    dir = opendir("/etc/rc.d");
    while((ptr = readdir(dir)) != NULL)
    {
        printf("d_name : %s\n", ptr->d_name);
    }
    closedir(dir);

	return 0;
}

/*
Ö´ÐÐ£º
d_name : .
d_name : ..
d_name : init.d
d_name : rc0.d
d_name : rc1.d
d_name : rc2.d
d_name : rc3.d
d_name : rc4.d
d_name : rc5.d
d_name : rc6.d
d_name : rc
d_name : rc.local
d_name : rc.sysinit
*/
