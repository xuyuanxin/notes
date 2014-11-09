/*******************************************************************************
---->定义
信号是软件中断。信号提供了一种处理异步事件的方法，例如，终端用户键入终端键，则会
通过信号机制停止一个程序。每个信号都有一个名字(以SIG开头),信号都被定义为正整数，
不存在编号为0的信号。

信号可以:
a:由一个进程发给另外一个进程(或自身)
b:由内核发给某个进程
每个信号都有一个与之关联的处理(disposition),也称为行为(action).信号的处置有三种选择
1 捕获
2 忽略 SIG_IGN
3 默认处理 

产生信号的条件:
1 某些特定按键，引发终端产生信号。例如Ctrl+C通常产生中断信号(SIGINT)
2 硬件异常产生信号:These conditions are usually detected by the hardware, and the
  kernel is notified. The kernel then generates the appropriate signal for the
  process that was running at the time the condition occurred. For example,SIGSEGV 
  is generated for a process that executes an invalid memory reference.
3 kill命令
4 软件条件:Software conditions can generate signals when a process should be 
  notified of various events. These aren't hardware-generated conditions (as is 
  the divideby-0 condition), but software conditions. Examples are SIGURG 
  (generated when out-of-band data arrives over a network connection), SIGPIPE 
  (generated when a process writes to a pipe that has no reader), and SIGALRM 
  (generated when an alarm clock set by the process expires).

Program Start-Up
When a program is executed, the status of all signals is either default or ignore.
Normally,all signals are set to their default action, unless the process that 
calls exec is ignoring the signal. Specifically,the exec functions change the 
disposition of any signals being caught to their default action and leave the 
status of all other signals alone. (Naturally,asignal that is being caught by 
a process that calls exec cannot be caught by the same function in the new program, 
since the address of the signal catching function in the caller probably has no 
meaning in the new program file that is executed.)

Process Creation
When a process calls fork,the child inherits the parent's signal dispositions. 
Here,since the child starts off with a copy of the parent’s memory image, the 
address of a signal-catching function has meaning in the child.

---->一些概念
  generated    产生
  delivered    递交
  pending      悬挂
  blocking     阻塞
  signal mask  信号掩码

  generated: a signal is generated for a process (or sent to a process) when the 
event that causes the signal occurs. The event could be a hardware exception 
(e.g., divide by 0), a software condition (e.g., analarm timer expiring), a 
terminal-generated signal, or a call to the kill function.When the signal is 
generated, the kernel usually sets a flag of some form in the process table.

  delivered: We say thata signal is delivered to a process when the action for 
a signal is taken.

  pending: During the time between the generation of a signal and its delivery,
the signal is said to be pending.

  blocking:阻止是阻止信号的递交(delivery)。也就是使产生的信号处于pending状态。
If a signal that is blocked is generated for a process, and if the action for 
that signal is either the default action or to catch the signal, then the signal 
remains pending for the process until the process either (a) unblocks the signal 
or (b) changes the action to ignorethe signal. 
The system determines what to do with a blocked signal when the signal is delivered, 
not when it's generated. This allows the process to change the action for the signal 
before it's delivered. 

  signal mask: Each process has a signal mask that defines the set of signals 
currently blocked from delivery to that process. We can think of this mask as 
having one bit for each possible signal. If the bit is on for a given signal, 
that signal is currently blocked. A process can examine and	 change its current 
signal mask by calling @sigprocmask
  Since it is possible for the number of signals to exceed the number of bits in 
an integer,POSIX.1 defines a data type,called sigset_t,that holds a signal set.
The signal mask, for example,is	stored in one of these	signal sets. 

  阻塞期间不止产生一次该信号，如何处理:POSIX.1 allows the system to deliver the 
signal either once or more than  once. If the system delivers the signal more 
than once, we say that the signals are queued. Most UNIX systems, however,do not 
queue signals unless they support the real-time extensions to POSIX.1. Instead, 
the UNIX kernel simply delivers the signal once.

  同时产生多个信号，如何处理:POSIX.1 does not specify the order in which the signals  
are delivered to the process.The Rationale for POSIX.1 does suggest, however,that 
signals related to the current state of the process be delivered before other 
signals. (SIGSEGV is one such signal.)




*/
/******************************************************************************/

/******************************************************************************
 以下五个信号是作业控制信号
 Except for SIGCHLD,most application programs don't handle these signals

 There are some interactions between the job-control signals. When any of the four
 stop  signals (SIGTSTP, SIGSTOP, SIGTTIN,or SIGTTOU) is generated for a process,
 any pending SIGCONT signal for that process is discarded. Similarly,when the
 SIGCONT signal is generated for a process, any pending stop signals for that same
 process are discarded.
 Note that the default action for SIGCON Tis to continue the process, if it is stopped;
 otherwise, the signal is ignored. Normally, we don't have to do anything with this
 signal. When SIGCONT is generated for a process that is stopped, the process is
 continued, even if the signal is blocked or ignored.
 ******************************************************************************/

#define SIGCHLD /*Child process has stopped or terminated.*/
#define SIGCONT /*Continue process, if stopped.When we tell the shell to resume 
a job in the foreground or background, the shell sends all the processes in the 
job the SIGCONT signal.*/
#define SIGSTOP /*Stop signal (can't be caught or ignored).*/
#define SIGTSTP /*Interactive stop signal. 当键入挂起字符(通常是ctrl+z)时信号
被送到前台进程组的所有进程*/
#define SIGTTIN /*Read from controlling terminal by background process group member.*/
#define SIGTTOU /*Write to controlling terminal by a background process group member.
if SIGTTIN or SIGTTOU is delivered to a process, the process is stopped by default, and
the job-control shell recognizes this and notifies us.*/


#define SIGINT /*This signal is generated by the terminal driver when we press 
the interrupt key (often DELETE or Control-C). This signal is  sent to all processes 
in the foreground process group. This signal is often used to terminate a runaway
program, especially when it's generating a lot of unwanted output on the screen.*/
#define SIGUSR1 /*This is a user-defined signal, for use in application programs.*/
#define SIGUSR2 /*This is another user-defined signal,similar to SIGUSR1,for use 
in application programs.*/
#define SIGBUS /*This signal indicates an implementation-defined  hardware fault.
Implementations usually generate this signal on certain types of memory faults
如果访问映射区的某个部分,而在访问时这一部分实际上已经不存在，则产生SIGBUS信号*/
#define SIGSEGV /*the process has made an invalid memory reference (which is 
usually a sign that the program has a bug, such as dereferencing an uninitialized 
pointer).The name SEGV stands for "segmentation violation."*/
#define SIGPIPE /*If we write to a pipeline but the reader has terminated,SIGPIPE 
is generated.This signal is also generated when a process writes to a socket of 
type SOCK_STREAM that is no longer connected.*/
#define SIGTERM /*This is the termination signal sent by the kill(1) command by 
default.Because it can be caught by applications, using SIGTERM gives programs
a chance to terminate gracefully by cleaning up before exiting  (in contrast to 
SIGKILL,which can't be caught or ignored).*/

