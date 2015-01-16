#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/*
 l: execl,execlp,execle£¬
    means that the function takes a list of arguments and is mutually exclusive with 
    the letter v,  
*/
int execl_test(void)
{    
    printf("entering main process---\r\n"); 
	if(execl("/bin/ls","ls","-l",NULL) < 0){  /* no return on success */ 
		printf("execl error\r\n"); 
	}
	printf("exiting main process ----\r\n"); 
	return 0;
}

/*
  p: execlp,execvp
     means that the function takes a filename argument and uses the PATH environment
     variable to find the executable file.
*/
int execlp_test(void)
{    
    printf("entering main process---/n");
	execlp("ls","ls","-l",NULL);
	printf("exiting main process ----/n");    
	return 0;
}

/*
 v: execv,execvp
    means that it takes an argv[] vector.
*/
int execvp_test(void)
{
	int ret;	
	char *argv[] = {"ls","-l",NULL};	

    printf("entering main process---/n");	

	ret = execvp("ls",argv);	
	if(ret == -1){		 
		perror("execl error");
	}
	printf("exiting main process ----/n");	 
	return 0;
}

/*
 e: execle
    means that the function takes an envp[] array instead of using the current 
    environment.
*/

char *env_init[] ={"USER=unknown", "PATH=/tmp", NULL };

int execle_test(void)
{
    pid_t pid;
    if ((pid = fork()) < 0) {
        printf("fork error\r\n");
    } else if (pid == 0) { /* child */
        if (execle("/bin/echoall.exe","echoall","myarg1",(char *)0,env_init) < 0){
            printf("execle error\r\n");
        }	
    }
	
    if (waitpid(pid, NULL, 0) < 0) {
        printf("wait error\r\n");
    }	
	
    exit(0);
}

int main(int argc, char *argv[])
{
    execlp_test();
}
