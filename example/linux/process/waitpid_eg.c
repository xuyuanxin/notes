#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>

/*-----------------------------------------------------------------------------------
 If we want to write a process so that it forks a child but we don't want to wait for 
 the child to complete and we don't want the child to become a zombie until we termi-
 nate, the trick is to call @fork twice.

notes01
    We're the second child; our parent becomes init as soon as our real parent calls 
    @exit in the statement above. Here's where we'd continue executing, knowing that 
    when we're done, init will reap our status.
notes02
    We're the parent (the original process); we continue executing, knowing that we're 
    not the parent of the second child.
-----------------------------------------------------------------------------------*/
int waitpid_eg01(void)
{
    pid_t pid;
    if ((pid = fork()) < 0) {
        printf("fork error");
    } else if (pid == 0) { /* first child */
        if ((pid = fork()) < 0) {
            printf("fork error");
        } else if (pid == 0) {
			sleep(2); /* notes01 */
			printf("second child, parent pid = %ld\n", (long)getppid());
			exit(0);
        } else {
            exit(0);
        }
    } else {
        if (waitpid(pid, NULL, 0) != pid) /* wait for first child */
            printf("waitpid error");
        return (0); /* notes02 */
    }
}

int main()
{
    waitpid_eg01();
	return 0;
}
