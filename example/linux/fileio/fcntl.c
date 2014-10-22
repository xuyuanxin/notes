#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>

int main(int argc, char *argv[])
{
	int val;
	
	if (argc != 2)
	{	
	    printf("usage: a.out <descriptor#>");
		return 1;
	}
	
	if ((val = fcntl(atoi(argv[1]), F_GETFL, 0)) < 0)
	{
	    printf("fcntl error for fd %d", atoi(argv[1]));
		return;
	}
	
	switch (val & O_ACCMODE) 
	{
	case O_RDONLY:
	    printf("read only");
	    break;
	case O_WRONLY:
	    printf("write only");
	    break;
	case O_RDWR:
	    printf("read write");
	    break;
	default:
	    printf("unknown access mode");
	}
	
	if (val & O_APPEND)
	    printf(", append");
	if (val & O_NONBLOCK)
	    printf(", nonblocking");
	if (val & O_SYNC)
	    printf(", synchronous writes");

	//if (val & O_FSYNC)
	    //printf(", synchronous writes");

	putchar('\n');
	exit(0);
}
