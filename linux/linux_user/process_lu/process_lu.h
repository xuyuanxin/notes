/*
---->进程标识符
每个进程都有一个非负整数表示的唯一进程ID。
进程ID为0的进程:调度进程也被称为交换进程(swapper)
进程ID为1的进程:init进程
进程ID为2的进程:也守护进程(pagedaemon)。

---->进程退出
进程正常或异常终止时，内核就向其父进程发送SIGCHLD信号(异步信号，默认忽略)。

---->竞争条件(race conditions) 
a race condition occurs when multiple processes are trying to do something with 
shared data and the final outcome depends on the order in which the processes run. 

----> 进程状态
zombie
    The purpose of the zombie state is to maintain information about the child 
    for the parent to fetch at some later time. This information includes the 
    process ID of the child, its termination status, and information on the 
    resource utilization of the child (CPU time, memory, etc.). If a process 
    terminates, and that process has children in the zombie state, the parent 
    process ID of all the zombie children is set to 1 (the init process), which 
    will inherit the children and clean them up (i.e., init will wait for them, 
    which removes the zombie). Some Unix systems show the COMMAND column for a 
    zombie process as <defunct>.

    Obviously we do not want to leave zombies around. They take up space in the 
    kernel and eventually we can run out of processes. Whenever we fork children, 
    we must wait for them to prevent them from becoming zombies.


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
进程必定属于一个进程组，也只能属于一个进程组。 一个进程组中可以包含多个进程。 进程组的生命周期从被创建开始，到其内所有进程终止或离开该组。
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



