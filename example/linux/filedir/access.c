#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>


int access_eg01(int argc, char *argv[])
{
    if (argc != 2) {
        printf("usage: a.out <pathname>");
        return 1;
    }
    
    if (access(argv[1], R_OK) < 0) {
        printf("access error for %s", argv[1]);
    } else {
        printf("read access OK\n");
    }
    
    if (open(argv[1], O_RDONLY) < 0) {
        printf("open error for %s", argv[1]);
    } else {
        printf("open for reading OK\n");
    }
    
    exit(0);
}

int main(int argc, char *argv[])
{
    access_eg01(argc,argv);    
    exit(0);
}

/*
$ ./a.exe  a.exe
read access OK
open for reading OK

*/

