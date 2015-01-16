#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void)
{
    pid_t pid;
	char *path = "htdocs/color.cgi";
    if ((pid = fork()) < 0) {
        printf("fork error\r\n");
    } else if (pid == 0) { /* child */
        if (execl(path, path, NULL) < 0){
            printf("execl error\r\n");
			perror("execl error");
        }	
    }
	
    if (waitpid(pid, NULL, 0) < 0) {
        printf("wait error\r\n");
    }	
	
    exit(0);
}
