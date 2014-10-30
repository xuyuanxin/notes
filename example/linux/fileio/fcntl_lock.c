#include "apue.h"
#include <fcntl.h>

#define read_lock(fd, offset, whence, len) \
    lock_reg((fd), F_SETLK, F_RDLCK, (offset), (whence), (len))

#define readw_lock(fd, offset, whence, len) \
    lock_reg((fd), F_SETLKW, F_RDLCK, (offset), (whence), (len))

#define write_lock(fd, offset, whence, len) \
    lock_reg((fd), F_SETLK, F_WRLCK, (offset), (whence), (len))

#define writew_lock(fd, offset, whence, len) \
    lock_reg((fd), F_SETLKW, F_WRLCK, (offset), (whence), (len))

#define un_lock(fd, offset, whence, len) \
    lock_reg((fd), F_SETLK, F_UNLCK, (offset), (whence), (len))

#define is_read_lockable(fd, offset, whence, len) \
    (lock_test((fd), F_RDLCK, (offset), (whence), (len)) == 0)
    
#define is_write_lockable(fd, offset, whence, len) \
    (lock_test((fd), F_WRLCK, (offset), (whence), (len)) == 0)

int lock_reg(int fd, int cmd, int type, off_t offset, int whence, off_t len)
{
	struct flock lock;
	lock.l_type = type; /* F_RDLCK, F_WRLCK, F_UNLCK */
	lock.l_start = offset; /* byte offset, relative to l_whence */
	lock.l_whence = whence; /* SEEK_SET, SEEK_CUR, SEEK_END */
	lock.l_len = len; /* #bytes (0 means to EOF) */
	
	return(fcntl(fd, cmd, &lock));
}

pid_t lock_test(int fd, int type, off_t offset, int whence, off_t len)
{
	struct flock lock;
	lock.l_type = type; /* F_RDLCK or F_WRLCK */
	lock.l_start = offset; /* byte offset, relative to l_whence */
	lock.l_whence = whence; /* SEEK_SET, SEEK_CUR, SEEK_END */
	lock.l_len = len; /* #bytes (0 means to EOF) */
	
	if (fcntl(fd, F_GETLK, &lock) < 0)
	{
	    printf("fcntl error");
		return 1;
	}
	
	if (lock.l_type == F_UNLCK)
	    return(0);  /* false, region isn't locked by another proc */
	
	return(lock.l_pid); /* true, return pid of lock owner */
}

//#define lockfile(fd) write_lock((fd), 0, SEEK_SET, 0)

int lockfile(int fd)
{
	struct flock fl;
	
	fl.l_type = F_WRLCK;
	fl.l_start = 0;
	fl.l_whence = SEEK_SET;
	fl.l_len = 0;
	
	return(fcntl(fd, F_SETLK, &fl));
}



static void lockabyte(const char *name, int fd, off_t offset)
{
    if (writew_lock(fd, offset, SEEK_SET, 1) < 0)
        printf("%s: writew_lock error", name);
	
    printf("%s: got the lock, byte %lld\n", name, (long long)offset);
}

int main(void)
{
	int  fd;
	pid_t  pid;
	
	/*
	*Create a file and write two bytes to it.
	*/
	if ((fd = creat("templock", (S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH))) < 0)
	{
	    printf("creat error");
	}
	
	if (write(fd, "ab", 2) != 2)
	    printf("write error");
	
	TELL_WAIT();
	
	if ((pid = fork()) < 0) 
	{
	    printf("fork error");
	}
	else if (pid == 0) /* child */
	{ 
	    lockabyte("child", fd, 0);
	    TELL_PARENT(getppid());
	    WAIT_PARENT();
	    lockabyte("child", fd, 1);
	}
	else /* parent */
	{ 
	    lockabyte("parent", fd, 1);
	    TELL_CHILD(pid);
	    WAIT_CHILD();
	    lockabyte("parent", fd, 0);
	}
	
	exit(0);
}

