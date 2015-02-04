#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/mman.h>

int global_cnt = 0;

int mmap_eg_sharemem(int argc, char **argv)
{
	int	fd, zero = 0;
	int	*ptr;	
	pid_t pid;

	if (argc != 2) {
		printf("usage:  <pathname> ");
	}
		
	fd = open(argv[1], O_RDWR | O_CREAT, (S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH));
	write(fd, &zero, sizeof(int)); /* open file, initialize to 0, map into memory */
	ptr = mmap(NULL, sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
	close(fd);
	setbuf(stdout, NULL);	/* stdout is unbuffered */
	pid = fork();
	if(pid < 0) {
		printf("fork error\n");
		return -1;
	}
	if (pid == 0) {		/* child */
	    (*ptr)++;
		global_cnt++;
		exit(0);
	}
	
	if (waitpid(pid, NULL, 0) < 0) {
		printf("wait error\r\n");
	}

    printf("parent: global_cnt:%d sharemem:%d\n", global_cnt,(*ptr)++);
	exit(0);
}

int main(int argc, char **argv)
{
    mmap_eg_sharemem(argc,argv);
	return 0;
}

