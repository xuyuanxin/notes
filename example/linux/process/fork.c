#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int  globvar = 6;
char  buf[]  = "a write to stdout\n";

/*-----------------------------------------------------------------------------------
 @write function is not buffered. Because @write is called before the fork, its data 
 is written once to standard output. The standard I/O library, however, is buffered. 
 standard output is line buffered if it's connected to a terminal device; otherwise, 
 it's fully buffered.

output:
$ ./a.exe                        <---- printf is line buffered
a write to stdout                                                                                                                   
print with newline                                                                                                                  
print no newline                                                                                                                    
child: pid: 2148 glob: 7 var: 89                                                                                                    
                                                                                                                                    
print no newline                                                                                                                    
parent: pid: 2147 glob: 6 var: 88


$ ./a.exe >out.txt               <---- printf is fully buffered
$ cat out.txt
a write to stdout                                                                                                                   
print with newline                                                                                                                  
print no newline                                                                                                                    
child: pid: 2198 glob: 7 var: 89                                                                                                    
                                                                                                                                    
print with newline                                                                                                                  
print no newline                                                                                                                    
parent: pid: 2197 glob: 6 var: 88 
-----------------------------------------------------------------------------------*/
int fork_eg01(void)
{
    int  var; 
    pid_t  pid;
    var = 88;
	
    if (write(STDOUT_FILENO, buf, sizeof(buf)-1) != sizeof(buf)-1) {
        printf("write error\n");
    }
	
    printf("print with newline\n");
    printf("print no newline"); 
	
    if ((pid = fork()) < 0) {
        printf("fork error \n");
		return 0;
    } else if (pid == 0) { /* child */
        printf("\n");
        globvar++;
        var++;
		printf("child: pid: %d glob: %d var: %d\n\n", (long)getpid(),globvar,var);
    } else {  /* parent */
        sleep(1);
		printf("\n");
        printf("parent: pid: %d glob: %d var: %d\n\n", (long)getpid(),globvar,var);
    }	
    exit(0);
}

int main()
{
    fork_eg01();
	return 0;
}
