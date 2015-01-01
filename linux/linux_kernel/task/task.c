

struct task_struct

struct pid   /*内核对PID的内部表示*/
struct upid  /*特定命名空间可见的信息*/

pid_hash 
attach_pid
task_pid
pid_nr_ns
pid_vnr    /*返回该ID所属的命名空间所看到的局部PID*/
pid_nr     /*获取从init进程看到的全局PID*/
task_pid_nr_ns

find_pid_ns  /*由局部数字PID和关联的命名空间获得pid实例(这是PID的内核表示)*/
find_task_by_pid_ns

alloc_pidmap /*分配PID*/
free_pidmap  /*释放PID*/
alloc_pid    /*每个命名空间生成一个局部PID*/


/*pid hash*/
pidhash_init
pid_hashfn
attach_pid
alloc_pid
find_pid_ns

alloc_pidmap






/*

init_tss  init_task.c
INIT_TSS

---->进程线程概念
进程:程序+资源

---->用户态和核心态
用户态:进程通常处于用户态,只能访问自身的数据.如果想访问系统数据或功能需要切换到核心态.
用户态切换到核心态
1 通过系统调用  主动切换
2 中断触发      被动切换  虽然中断导致进程切换到核心态，但中断的执行通常和进程无关.当前进程也察觉不到中断的运行.

---->内核抢占
1 普通进程总是可能被抢占，甚至是被其它进程抢占.
2 系统处于核心态并正在处理系统调用,那么其它进程无法抢占,但中断可以中止系统调用.

---->僵尸进程

---->进程ID号
线程ID:
  每个线程应该有自己的ID，就是线程ID，在linux kernel中，每一个thread分配一个task_struct，该结构中的pid成员就是线程ID。在POSIX标准中，定义了pthread_self
  来获取线程ID，linux kernel采用了gettid的系统调用来获取调用者的线程ID。在linux kernel中，定义如下：
            asmlinkage long sys_gettid(void)
            {
                   return current->pid;
            }
  POSIX规定线程ID在所属进程中是唯一的，不过在linux kernel的实现中，thread ID是全系统唯一的，当然，考虑到可移植性，Application software不应该假设这一点。
  
TGID:线程组ID
    多线程的进程中第一个线程（主线程，group leader）的pid等于tgid，之后，该线程组中的线程都有自己的pid，但是共享tgid，也就是传统意义上的进程ID。

PID:进程总会分配一个号码用于在其命名空间中唯一地标识他们,该号码成为进程ID号,简称PID.
    进程是有一个或者多个thread组成（POSIX规定多个thread要共享一个进程ID）。
    多线程的进程中第一个线程（主线程，group leader）的pid等于tgid，之后，该线程组中的线程都有自己的pid，但是共享tgid，也就是传统意义上的进程ID。
    系统定义了getpid(sys_getpid)函数来获取一个进程的process ID。
    asmlinkage long sys_getpid(void)
    {
       return current->tgid;
    }
进程组ID:
    每个进程属于一个进程组，每个进程组有一个Leader进程，也就是进程ID等于进程组ID的那个进程。
    进程组有生命周期，它的生命周期开始于进程组leader创建进程组，结束于进程组内的最后一个进程离开进程组

SID :会话ID
    和进程属于进程组类似，每个进程组都属于一个session，每个session有一个Leader进程，也就是创建session的那个进程，
    session leader的ID就等于该session的ID。Session概念的提出和用户登录相关


某些进程有多个PID,凡可以看到该进程的命名空间,都会为其分配一个PID


---->命名空间
命名空间:轻量级的虚拟化

struct nsproxy         通过这个结构体管理
CLONE_NEWUTS           等表示用来表示是否创建新的uts等命名空间
struct task_struct->nsproxy 变量指向进程所属的命名空间
init_nsproxy           这个全局变量定义了初始的全局命名空间

UTS命名空间
struct uts_namespace   管理结构
init_uts_ns            初始信息
copy_utsname           创建ust命名空间,fork是调用

用户命名空间
struct user_namespace  管理结构
clone_user_ns          创建用户命名空间

PID命名空间
struct pid_namespace   管理结构
struct pid             内核对pid的内部表示
struct upid            特定的命名空间中可见的信息

pid_hash               pidhash_init中初始化
attach_pid

task_pid_nr_ns        由进程和其所属命名空间获得局部ID
  task_pid            由进程获得获得task_struct关联的pid
  pid_nr_ns           有pid和命名空间获得局部ID
pid_vnr              返回该ID所属的命名空间所看到的局部PID
pid_nr               获取从init进程看到的全局PID

find_task_by_pid_type_ns  由局部ID和对应的命名空间获得二元组表述的task_struct
  find_pid_ns             由局部数字PID和关联的命名空间(用户空间的pid表示)获得pid实例(pid的内核表示)
  pid_task
  
find_task_by_pid_ns       通过数字PID和所属的命名空间获得task_struct实例  
  find_task_by_pid_type_ns
  
find_task_by_vpid         通过局部pid查找进程
find_task_by_pid          通过全局pid查找进程

alloc_pid



---->进程创建
用户态API    fork vfork clone
libc库       fork vfork clone
               system_call            128号中断从用户态切换到内核态,进入系统调用处理程序
      sys_fork sys_clone sys_vfork    根据系统调用号调用对应的服务例程 系统调用号在linux/include/asm-i386/unistd.h中定义
               do_fork


long do_fork(unsigned long clone_flags,     最低的一个字节为子进程结束时发送给父进程的信号代码，通常为SIGCHLD；剩余的三个字节则是各种clone标志的组合
	        unsigned long stack_start,     子进程用户态堆栈的地址
	        struct pt_regs *regs,          指向pt_regs结构体的指针。当系统发生系统调用，即用户进程从用户态切换到内核态时，该结构体保存通用寄存器中的值，并被存放于内核态的堆栈中
	        unsigned long stack_size,      未被使用，通常被赋值为0
	        int __user *parent_tidptr,     父进程在用户态下pid的地址，该参数在CLONE_PARENT_SETTID标志被设定时有意义
	        int __user *child_tidptr)      子进程在用户态下pid的地址，该参数在CLONE_CHILD_SETTID标志被设定时有意义
do_fork
  copy_process
    标志检查
    dup_task_struct
    copy_flags
    sched_fork  初始化调度相关
    copy_thread 设置子进程的寄存器初始值，包括内核堆栈位置
    attach_pid  将pid插入到hlist



kernel_thread   创建内核线程


execve









