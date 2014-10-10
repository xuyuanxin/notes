/*
====================== 下半部 ======================
下半部是操作系统通用词汇，用于指代中断处理流程中推后执行的那一部分。
有三种机制用来实现将工作推后执行:软中断 tasklet 工作队列

====================== 软中断 ======================
软中断是在编译期间静态确定的，最多有32个软中断。
软中断(甚至是相同类型的软中断)可以在其它处理器上同时执行
唯一可以抢占软中断的就是中断处理程序
softirq_vec    结构体数组用来描述32个软中断

---->执行软中断
1 从一个硬件中断返回时
2 在ksoftirq内核线程中，当大量软中断出现时，内核会唤醒一组内核线程来处理这些负载。
  每个处理器都会有一个这样的线程，名字叫ksoftirqd/n(n表示处理器编号)，函数是ksoftirqd。
3 在那些显示检测盒执行待处理的软中断的代码中，如网络子系统中
无论哪种情况都会调用 do_softirq()。

---->使用软中断
1 添加索引 HI_SOFTIRQ
2 注册处理程序 open_softirq()
3 触发软中断 raise_softirq()

====================== tasklet ======================
tasklet是基于软中断的一种下半部机制。与其相关的两个软中断 HI_SOFTIRQ和TASKLET_SOFTIRQ，处理函数在softirq_init()中注册。
tasklet is running only on one CPU simultaneously.different tasklets may be run simultaneously on different CPUs.

tasklet_struct  结构体，代表一个tasklet，就是一个要推后执行的工作，每一个工作对应一个tasklet_struct结构。
TASKLET_STATE_SCHED

---->tasklet工作原理
两个链表tasklet_ver和tasklet_hi_vec都是由tasklet_struct结构体构成的链表，每个tasklet_struct代表一个tasklet。
tasklet_schedule 把一个tasklet挂到链表tasklet_ver中，然后触发软中断。
tasklet_hi_schedule 把一个tasklet挂到链表tasklet_hi_vec中，然后触发软中断。
这两个调度函数只是负责触发在softirq_init()中注册的软中断处理函数。软中断处理函数具体的负责执行tasklet。
---->taskle使用
1 创建一个tasklet
  DECLARE_TASKLET和tasklet_init()
2 tasklet处理函数
  处理函数不能睡眠。
3 调度自己的tasklet(运行tasklet处理函数)
  tasklet_schedule()标记tasklet为挂起状态(TASKLET_STATE_SCHED等待执行)。
  tasklet_disable()
  tasklet_enable()
  tasklet_kill()
====================== 工作队列 ======================
工作队列把推后的工作交给一个内核线程去执行，这是唯一能在进程上下文中运行的下半部机制。
这个推后工作的具体处理函数就可以睡眠了。

工    作: 推后执行的工作，用结构体work_struct表示。
工作线程: 内核线程，负责执行内核其它部分排到队列的任务。用结构体workqueue_struct表示。都执行worker_thread()函数。
工作队列: 每个工作线程对应一个队列。

缺省的工作线程叫做events/n，这里的n是处理器的编号。其对应的工作队列是events队列。

---->工作队列使用
1 创建工作线程
  系统有默认的工作线程(init_workqueues())，不过也可以创建一个新的。
  create_workqueue() 创建一个新的工作线程和工作队列，每个处理器都会创建。
  工作线程会不停的扫描自己的工作队列，如果有工作就会执行工作处理函数，然后从队列中删除工作。
2 创建工作
  DECLARE_WORK  INIT_WORK
3 工作调度
  queue_work 把工作加入指定的工作队列。
  queue_delayed_work 把工作加入指定的工作队列。但延时一段时候后再执行。
  schedule_work 把工作加入默认的工作队列。
  schedule_delayed_work 把工作加入默认的工作队列。但延时一段时候后再执行。
4 刷新队列
  如果继续下一步工作之前必须保证一些操作已经执行完毕，可以使用刷新队列。
  flush_scheduled_work 函数会一直等待，直到默认队列中的工作执行完毕。
  flush_workqueue 函数会一直等待，直到指定队列中的工作执行完毕。
5 取消工作
  cancel_delayed_work 

====================== 禁止下半部 ======================
 1 local_bh_disable
   禁止本地处理器的软中断和tasklet的处理。但不能禁止工作队列的执行。
 2 local_bh_enable
   使能本地处理器的软中断和tasklet的处理。
 3 使用说明
   这两个函数时嵌套使用的，调用了N次local_bh_disable，需要调用N次local_bh_enable()才能真正使能。