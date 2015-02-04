/*----------------------- mutex lock ------------------------------*/
//pthread_mutex_init

/*----------------------- semaphore ------------------------------*/
#include <semaphore.h>

#define SEM_FAILED ((sem_t *)(-1))

/*-----------------------------------------------------------------------------------
 @oflag
    The oflag argument is either 0, 0_CREAT, or 0_CREAT|0-EXCL
 @mode @value
    If 0_CREAT is specified, then the third and fourth arguments are required : @mode 
    specifies the permission bits ,and @value specifies the initial value of the sem-
    aphore.This initial value cannot exceed SEM_VALUE_MAX,which must be at least 32767. 
    The function @sem_open creates  a new named  semaphore or opens an existing named 
    semaphore . A named semaphore can always be used to synchronize either threads or 
    processes.
    If 0_CREAT is specified (without specifying 0-EXCL), the semaphore is initialized
    only if it does not already exist. Specifying 0_CREAT if the semaphore already e-
    xists is not an error. This flag just means " create and initialize the semaphore 
    if it does not already exist . " But specifying 0_CREAT|0_EXCL is an error if the 
    semaphore already exists.
 @return
	pointer to semaphore if OK, SEM_FAILED on error
-----------------------------------------------------------------------------------*/
sem_t *sem_open(const char *name, int oflag,...); 

/*-----------------------------------------------------------------------------------
 @Returns: 
    0 if OK, -1 on error
    
 This semaphore close operation also occurs automatically  on process termination for 
 any named semaphore that is still open . This happens whether the process terminates 
 voluntarily (by calling exit or _exit), or involuntarily (by being killed by a sign-
 al). Closing a semaphore does not remove the semaphore from the system. That is, Po-
 six named semaphores are at least kernel-persistent: they retain their value even if 
 no process currently has the semaphore open.
-----------------------------------------------------------------------------------*/
int sem_close (sem_t *sem);

/*-----------------------------------------------------------------------------------
 @func
    A named semaphore is removed from the system by sem_unlink.
 @Returns: 
    0 if OK, -1 on error
    
 Semaphores have a reference count of how many times they are currently open (just l-
 ike files), and this function is similar to the @unlink function for a file: the na-
 me can be removed from the filesystem while its reference count is greater than 0, 
 but the destruction of the semaphore (versus removing its name from the filesystem ) 
 does not take place until the last @sem_close occurs.
-----------------------------------------------------------------------------------*/
int sem_unlink(const char *name);

/*-----------------------------------------------------------------------------------
 The @sem_wait function tests the value  of the specified semaphore, and if the value 
 is greater than 0, the value is decremented and the function returns immediately. If 
 the value is 0 when the function is called, the calling thread is put to sleep until 
 the semaphore value is greater than 0, at which time it will be decremented, and the 
 function then returns. We mentioned earlier that the "test and decrement " operation 
 must be atomic with regard to other threads accessing this semaphore.

 @sem_trywait does not put the calling thread to sleep if the current value of the s-
 emaphore is alread 0. Instead, an error of EAGAIN is returned. 

 @sem_wait can return prematurely if it is interrupted by a signal, returning an err-
 or of EINTR.
-----------------------------------------------------------------------------------*/
int sem_wait (sem_t *sem);
int sem_trywait(sem_t * sem);

/*-----------------------------------------------------------------------------------
 @renturn
    0 if OK, -1 on error
    
 @sem_post increments the value of the semaphore by 1 and wakes up any threads that 
 are waiting for the semaphore value to become positive. of the various synchronizat-
 ion techniques(mutexes, condition variables, read-write locks, semaphores), the only 
 function that can be called from a signal handler is @sem_post.

 @sem_getvalue returns the current value of the semaphore in the interger pointed to 
 by @valp. 
-----------------------------------------------------------------------------------*/

int sem_post(sem_t *sem);
int sem_getvalue(sem_t *sem,int *valp);


/*----------------------- shared memory ------------------------------*/
// mmap
