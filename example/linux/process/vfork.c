#include <unistd.h>
#include<stdio.h>
#include<stdlib.h>

int  globvar=6;

int main(void)
{
    int  var; 
    pid_t  pid;
    var = 88;
    printf("before vfork\n"); /* we don't flush stdio */
	
    if ((pid = vfork()) < 0) 
	{
        printf("vfork error");
    }
	else if (pid == 0)  /* child */
	{
        globvar++; 
        var++;
		
		printf("child pid = %ld, glob = %d, var = %d\n", (long)getpid(), globvar,var);
        _exit(0);
    }
	
	sleep(2);  /* parent */
    printf("parant pid = %ld, glob = %d, var = %d\n", (long)getpid(), globvar,var);
    exit(0);
}

/*
$ ./a.exe
before vfork
child pid = 12116, glob = 7, var = 89
parant pid = 8660, glob = 6, var = 88

*/
