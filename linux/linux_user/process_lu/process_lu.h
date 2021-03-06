
//typedef int pid_t  /* linux */

/*-----------------------------------------------------------------------------------
 +------------------------+ high address
 | command-line arguments |
 | environment variables  |
 |------------------------|
 |          stack         |
 |                        |
 |                        |
 |          heap          |
 |------------------------|
 |          bbs           | initialized to zero bye exec
 |------------------------|
 |     initialized data   | read from program file by exec
 |------------------------|
 |          text          | read from program file by exec
 +------------------------+


       environ 
 +---------------------+
 | environment pointer | ----->  environment      environment    
 +---------------------+         list             strings
                                 +-------+
                                 | point | ----> HOME=/home/sar
                                 |-------|
                                 | point | ----> PATH=:/bin:/usr/bin
                                 |-------|
                                 | point | ----> SHELL=/bin/bash
                                 |-------|
                                 | point | ----> USER=sar
                                 |-------|
                                 | point | ----> LOGNAME=sar
                                 |-------|
                                 | NULL  |
                                 +-------+
                                 
main Function
    A C program starts execution with a function called @main . The prototype for the
    main function is
            int main(int argc,char *argv[]);
    where @argc is the number of command-line arguments, and @argv is an array of po-
    inters to the arguments.

    When a C program is executed by the kernel(by one of the exec functions), a spec-
    ial start-up routine is called before the main function is called. The executable 
    program file specifies this routine as the starting address for the program; this 
    is set up by the link editor when it is invoked by the C compiler. This start-up 
    routine takes values from the kernel (the command-line arguments and the environ-
    ment) and sets things up so that the main function is called as shown earlier.

Process Termination
    Thereare eight ways for a process to terminate. Normal termination occurs in five
    ways:
    1. Return from main
    2. Calling exit
    3. Calling _exit or _Exit
    4. Return of the last thread from its start routine 
    5. Calling pthread_exit from the last thread
    
    Abnormal termination occurs in three ways:
    6. Calling abort 
    7. Receipt of a signal 
    8. Response of the last thread to a cancellation request

    The start-up routine that we mentioned in the previous section is also written so 
    that if the main function returns, the exit function is called. If the start-up -
    routine were coded in C (it is often coded in assembly language) the call to main 
    could look like
            exit(main(argc, argv));
    Returning an integer value from the main function is equivalent to calling exit -
    with the same value. Thus exit(0);is the same as return(0);from the main function.
    
what happens if the parent terminates before the child
    the init process becomes the parent process of any process whose parent terminat-
    es. In such a case, we say that the process has been inherited by init. What nor-
    mally happens is that whenever  a process terminates, the kernel goes through all
    active processes to see whether the terminating process is the parent of any pro-
    cess that still exists. If so , the parent process ID of the surviving process is 
    changed to be 1 (the process ID of init). This way, we're guaranteed that every -
    process has a parent.
    
when a child terminates before its parent. 
    The kernel keeps a small amount of information for every terminating process , so 
    that the information is available when the parent of the terminating process cal-
    ls @wait or @waitpid. Minimally, this information consists of the process ID, the
    termination status of the process, and the amount of CPU time taken by the proce-
    ss. The kernel can discard all  the memory used by the process and close its open 
    files. In UNIX System terminology,a process that has terminated, but whose parent 
    has not yet waited for it, is called a zombie. The ps(1) command prints the state 
    of a zombie process as Z. 
    
What happens when a process that has been inherited by init terminates
    init is written so that whenever one of its children terminates,init calls one of 
    the wait functions to fetch the termination status.  By doing this, init prevents 
    the system from being clogged by zombies. When we say "one of init's children," -
    we mean either a process that init generates directly(such as getty) or a process 
    whose parent has terminated and has been subsequently inherited by init

Process Identifiers
    Every process has a unique process ID, a non-negative integer . Most UNIX systems 
    implement algorithms to delay reuse, however, so that newly created processes are 
    assigned IDs different from those used by processes that terminated recently.

    There are some special processes, but the details differ from implementation to -
    implementation. Process ID  0 is usually the scheduler process and is often known 
    as the swapper. No program on disk corresponds to this process , which is part of 
    the kernel and is known as a system process. Process ID 1 is usually the init pr-
    ocess and is invoked by the kernel at the end of the bootstrap procedure. The pr-
    ogram file for this process was /etc/init in older versions of the UNIX System a-
    nd is /sbin/init in newer versions. This process is responsible for bringing up a 
    UNIX system after the kernel has been bootstrapped. init usually reads the system
    -dependent initialization files (the /etc/rc* files or /etc/inittab and the files 
    in /etc/init.d) and brings the system to a certain state , such as multiuser. The 
    init process never dies. It is a normal user process, not a system process within 
    the kernel, like the swapper, although it does run with superuser privileges.

    Each UNIX System implementation has  its own set of kernel processes that provide
    operating system services. For example, on some virtual memory implementations of
    the UNIX System, process ID  2 is the pagedaemon. This process is responsible for
    supporting the paging of the virtual memory system.


---->进程退出
进程正常或异常终止时，内核就向其父进程发送SIGCHLD信号(异步信号，默认忽略)。

---->竞争条件(race conditions) 
a race condition occurs when multiple processes are trying to do something with 
shared data and the final outcome depends on the order in which the processes run. 

 ----> 进程状态
 zombie
     The purpose of the zombie state is to maintain information about the child for -
     the parent to fetch at some later time. This information includes the process  -
     ID of the child, its termination status, and information on the resource utiliz-
     ation of the child (CPU time, memory, etc.). If a process terminates, and that -
     process has children in the zombie state, the parent process ID of all the zomb-
     ie children is set to 1 (the init process), which will inherit the children  and 
     clean them up (i.e., init will wait for them, which removes the zombie). Some U-
     nix systems show the COMMAND column for a zombie process as <defunct>.

     Obviously we do not want to leave zombies around. They take up space in the ker-
     nel and eventually we can run out of processes. Whenever we fork children, we m-
     ust wait for them to prevent them from becoming zombies.


----> 僵死(zombie)进程 孤儿进程
unix提供了一种机制可以保证只要父进程想知道子进程结束时的状态信息， 就可以得到。
这种机制就是: 在每个进程退出的时候,内核释放该进程所有的资源,包括打开的文件,占
用的内存等。 但是仍然为其保留一定的信息(包括进程号the process ID,退出状态the 
termination status of the process,运行时间the amount of CPU time taken by the 
process等)。直到父进程通过wait / waitpid来取时才释放。

孤儿进程：一个父进程退出，而它的一个或多个子进程还在运行，那么那些子进程将成为
孤儿进程。孤儿进程将被init进程(进程号为1)所收养，并由init进程对它们完成状态收集
工作。

僵尸进程：一个进程使用fork创建子进程，如果子进程退出，而父进程并没有调用wait或
waitpid获取子进程的状态信息，那么子进程的进程描述符仍然保存在系统中。这种进程称
之为僵死进程。


----> 进程组:
进程组就是一些进程的组合,他们彼此之间或者存在父子、兄弟关系，或者在功能上有相近的联系。
进程必定属于一个进程组，也只能属于一个进程组。 一个进程组中可以包含多个进程。 进程组的
生命周期从被创建开始，到其内所有进程终止或离开该组。
----> 进程组的作用:
进程组就是为了方便对进程进行管理。假设要完成一个任务，需要同时并发100个进程。
当用户处于某种原因要终止这个任务时，要是没有进程组，就需要手动的一个个去杀死这100个进程，
并且必须要严格按照进程间父子兄弟关系顺序，否则会扰乱进程树。有了进程组，
就可以将这100个进程设置为一个进程组，它们共有1个组号（pgrp），
并且有选取一个进程作为组长（通常是“辈分”最高的那个，通常该进程的ID也就作为进程组的ID）。
现在就可以通过杀死整个进程组，来关闭这100个进程，并且是严格有序的。
----> 组长进程
组长进程标识: 其进程组ID==其进程ID
组长进程可以创建一个进程组，创建该进程组中的进程，然后终止
只要进程组中有一个进程存在，进程组就存在，与组长进程是否终止无关
进程组生存期: 进程组创建到最后一个进程离开(终止或转移到另一个进程组)
----> 会话:
一个或多个进程组的集合,开始于用户登录,终止与用户退出.
由于Linux是多用户多任务的分时系统，所以必须要支持多个用户同时使用一个操作系统。
当一个用户登录一次系统就形成一次会话。每个会话都有一个会话首领（leader），即创建会话的进程。
一个会话可包含多个进程组，但只能有一个前台进程组。




User Identification

User ID
    The user ID from our entry in the password file is a numeric value that identifi-
    es us to the system. This user ID is assigned by the system administrator when o-
    ur login name is assigned, and we cannot change it. The user ID is normally assi-
    gned to be unique for every user.
    
    We call the user whose user ID is 0 either root or the superuser. The entry in t-
    he password file normally has a login name of root, and we refer to the special -
    privileges of this user as superuser privileges.

Group ID
    Our entry in the password file also specifies our numeric group ID. This, too, is 
    assigned by the system administrator when our login name is assigned. Typically,-
    the password file contains multiple entries that specify the same group ID. Grou-
    ps are normally used to collect users together into projects or departments. Thi-
    s allows the sharing of resources, such as files, among members of the same group. 

Supplementary Group IDs
    most versions of the UNIX System allow a user to belong to other groups. This pr-
    actice started with 4.2BSD, which allowed a user to belong to up to 16 additional 
    groups. These supplementary group IDs are obtained at login time by reading the -
    file /etc/group and finding the first 16 entries that list the user as a member. 
    As we shall see in the next chapter, POSIX requires that a system support at lea-
    st 8 supplementary groups per process, but most systems support at least 16.

 Every process has a set of associated numeric user identifiers (UIDs) and group ide-
 ntifiers (GIDs). Sometimes, these are referred to as process credentials. These ide-
 ntifiers are as follows:
 1 real user ID and group ID;
 2 effective user ID and group ID;
 3 saved set-user-ID and saved set-group-ID;
 4 file-system user ID and group ID (Linux-specific); and
 5 supplementary group IDs.

Real User ID and Real Group ID
    The real user ID and group ID identify the user and group to which the process b-
    elongs . As part of the login process, a login shell gets its real user and group 
    IDs from the third and fourth fields of the user's password record in the /etc/p-
    asswd file. When a new process is created (e.g., when the shell executes a progr-
    am), it inherits these identifiers from its parent.
Effective User ID and Effective Group ID
    the effective user ID and group ID, in conjunction with the supplementary group -
    IDs, are used to determine the permissions  granted to a process when it tries to 
    perform various operations (i.e., system calls). Normally, the effective user and 
    group IDs have the same values as the corresponding real IDs, but there are two -
    ways in which the effective IDs can assume different values. One way is through -
    the use of system calls. The second way is through the execution of set-user-ID -
    and set-group-ID programs.
Set-User-ID and Set-Group-ID Programs
    A set-user-ID program allows a process to gain privileges it would not normally -
    have, by setting the process's effective user ID to the same value as the user ID 
    (owner) of the executable file. A set-group-ID program performs the analogous ta-
    sk for the process's effective group ID. (The terms set-user-ID program and set-group-ID 
    program are sometimes abbreviated as set-UID program and set-GID program.)
Saved Set-User-ID and Saved Set-Group-ID
    The saved set-user-ID and saved set-group-ID are designed for use with set-user-ID
    and set-group-ID programs. When a program is executed, the following steps ( among 
    many others) occur:
    1 If the set-user-ID (set-group-ID ) permission bit is enabled on the executable,
      then the effective user (group) ID of the process is made the same as the owner
      of the executable. If the set-user-ID (set-group-ID) bit is not set, then no c-
      hange is made to the effective user (group) ID of the process.
    2 The values for the saved set-user-ID and saved set-group-ID are copied from the 
      corresponding effective IDs. This copying occurs regardless of whether the set-user-ID 
      or set-group-ID bit is set on the file being executed.
       
    As an example of the effect of the above steps, suppose that a process whose real 
    user ID,effective user ID, and saved set-user-ID are all 1000 execs a set-user-ID 
    program owned by root (user ID 0). After the exec, the user IDs of the process w-
    ill be changed as follows:
            real=1000 effective=0 saved=0
    Various system calls allow a set-user-ID program to switch  its effective user ID 
    between the values of the real user ID and the saved set-user-ID.Analogous system
    calls allow a set-group-ID program to modify its effective group ID. In this man-
    ner, the program can temporarily drop and regain whatever privileges are associa-
    ted with the user (group) ID of the execed file. 

Supplementary Group IDs
    The supplementary group IDs are a set of additional groups to which a process be-
    longs. A new process inherits these IDs from its parent.A login shell obtains its
    supplementary group IDs from the system group file. As noted above, these IDs are
    used in conjunction with the effective and file-system IDs to determine permissi-
    ons for accessing files, System V IPC objects, and other system resources.



gcc -static hello1.c                <---- prevent gcc from using shared libraries


