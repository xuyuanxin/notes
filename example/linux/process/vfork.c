#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int  globvar = 6;

/*-----------------------------------------------------------------------------------
 we don't need to have the parent call sleep, as we're guaranteed that it is put to -
 sleep by the kernel until the child calls either @exec or @exit

 Here, the incrementing of the variables done by the child changes the values  in the
 parent. Because the child runs in the address space of the parent. This behavior, h-
 owever, differs from the behavior of @fork.
 
 we call @_exit instead of @exit.@_exit does not perform any flushing of standard I/O 
 buffers. If we call @exit instead, the results are indeterminate. Depending on the -
 implementation of the standard I/O library, we might see no difference in the output, 
 or we might find that the output from the first printf in the parent has disappeared.
 
 If the child calls @exit,the implementation flushes the standard I/O streams.If this
 is the only action taken by the library, then we will see no difference from the ou-
 tput generated if the child called @_exit. If the implementation also closes the st-
 andard I/O streams, however, the memory representing the FILE object for the standa-
 rd output will be cleared out. Because the child is borrowing the parent's address -
 space, when the parent resumes and calls @printf , no output will appear and @printf 
 will return -1. Note that the parent's STDOUT_FILENO is still valid, as the child g-
 ets a copy of the parent's file descriptor array .

output:
./a.out
print with newline                                                                                                                  
print no newline                                                                                                                    
child pid = 17398, glob = 7, var = 89                                                                                               
                                                                                                                                    
parant pid = 17397, glob = 7, var = 89 
-----------------------------------------------------------------------------------*/
int vfork_eg01(void)
{
    int  var; 
    pid_t  pid;
    var = 88;
	
    printf("print with newline\n");
    printf("print no newline"); 
	
    if ((pid = vfork()) < 0) {
        printf("vfork error");
    } else if (pid == 0) { /* child */
        globvar++; 
        var++;
		printf("\nchild pid = %ld, glob = %d, var = %d\n", (long)getpid(), globvar,var);
        _exit(0);
    }
	
	/* parent */
    printf("\nparant pid = %ld, glob = %d, var = %d\n", (long)getpid(), globvar,var);
    exit(0);
}

int main()
{
    vfork_eg01();
	return 0;
}
