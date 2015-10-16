'''
1 thread_pylib_eg.py

This module provides low-level primitives for working with multiple threads (also ca-
lled light-weight processes or tasks) — multiple threads of control sharing their gl-
obal data space.

Python通过两个标准库thread和threading提供对线程的支持。thread提供了低级别的、原始的线程以及一个简单的锁。
thread 模块提供的其他方法：
threading.currentThread(): 返回当前的线程变量。
threading.enumerate(): 返回一个包含正在运行的线程的list。正在运行指线程启动后、结束前，不包括启动前和终止后的线程。
threading.activeCount(): 返回正在运行的线程数量，与len(threading.enumerate())有相同的结果。
除了使用方法外，线程模块同样提供了Thread类来处理线程，Thread类提供了以下方法:
run(): 用以表示线程活动的方法。
start():启动线程活动。
join([time]): 等待至线程中止。这阻塞调用线程直至线程的join() 方法被调用中止-正常退出或者抛出未处理的异常-或者是可选的超时发生。
isAlive(): 返回线程是否活动的。
getName(): 返回线程名。
setName(): 设置线程名。
'''



def start_new_thread(function, args[, kwargs])
   '''thread.start_new_thread
   Start a new thread and return its identifier. The thread executes the function   -
   @function with the argument list args (which must be a tuple). The optional kwargs 
   argument specifies a dictionary of keyword arguments. When the function returns, -
   the thread silently exits. When the function terminates with an unhandled excepti-
   on, a stack trace is printed and then the thread exits (but other threads continu-
   e to run).
   '''