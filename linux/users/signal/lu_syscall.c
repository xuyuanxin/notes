/*

Handling Interrupted System Calls
    We used the term "slow system call" to describe @accept, and we use this term 
    for any system call that can block forever. That is, the system call need never 
    return. Most networking functions fall into this category.For example, there is 
    no guarantee that a server's call to accept will ever return, if there are no 
    clients that will connect to the server.

    The basic rule that applies here is that when a process is blocked in a slow 
    system call and the process catches a signal and the signal handler returns, 
    the system call can return an error of EINTR. Some kernels automatically 
    restart some interrupted system calls(some not). 

    Even if an implementation supports the SA_RESTART flag, not all interrupted 
    system calls may automatically be restarted.

