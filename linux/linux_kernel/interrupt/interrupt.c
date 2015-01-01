/*
========================== x86中断的初始化 ==========================
setup_idt       初始化中断描述符表 head_32.S
trap_init       设置中断描述符表
init_IRQ
init_ISA_irqs   初始化中断请求队列

========================== 中断外部接口 ==========================
request_irq     往中断队列中挂处理函数
free_irq        释放中断线

========================== 中断机制内部实现 ==========================
irq_desc_t 中断线控制结构，一个中断线对应一个结构
irq_desc   结构数组，数组中的一个结构管理一个中断线

---->中断处理过程
处理器特定引脚(INTR)收到中断信号后
1 处理器停止当前工作，关闭中断系统，然后调转到内存中预定义的位置。
2 对于每条中断线，处理器都会调转到对应的一个唯一的位置。
3 获取IRQ号，保存当前处理器状态，然后跳转到do_IRQ()。
4 do_IRQ()调用mask_and_ack_8259A()对接收的中断进行应答，禁止这条中断线上的中断传递。
5 do_IRQ()调用handle_IRQ_event()来运行这条中断线上安装的中断处理函数(如果有的话)。

---->中断控制
local_irq_enable()  Enables local interrupt delivery
local_irq_save()  Saves the current state of local interrupt delivery and then disables it
local_irq_restore()  Restores local interrupt delivery to the given state
disable_irq()  Disables the given interrupt line and ensures no handler on the line is executing before returning
disable_irq_nosync()  Disables the given interrupt line
enable_irq()  Enables the given interrupt line
irqs_disabled()  Returns nonzero if local interrupt delivery is disabled; otherwise returns zero
in_interrupt()  Returns nonzero if in interrupt context and zero if in process context
in_irq()  Returns nonzero if currently executing an interrupt handler and zero otherwise


========================== 中断基础知识(针对X86) =========================
---->中断:
一般由外部硬件产生，不过软件也可以通过指令int n 产生中断。
---->异常:
处理器执行指令时，检测到一个出错条件是就会触发异常，例如除以0就是一个出错条件，会引发异常。
这种检测是处理器自动执行的，只要出现了处理器预定义好的那些错误，自动引发相应的异常。
异常发生后内核向发生异常的进程发送一个信号，进程将采取必要的措施来恢复或者终止运行。
---->向量号:
是一个数字(范围是0~255)，用来区分不同的中断和异常。
0~31:X86处理器保留，用来标识处理器定义的异常和中断。
32~255:用于用户定义的中断，通常用于I/O设备。

----> 中断来源:
1 外部硬件产生的中断
  处理器有两个引脚(INTR和NMI)用于接收中断。当引脚INTR接收到中断后，处理器就会从系统总线上读取中断向量号(这个向量号是中断控制器(如8259A)提供的)。
  当引脚NMI接收到中断后，就产生一个非屏蔽中断，它使用固定的中断向量号2。
2 软件产生的中断
  int n指令用于从软件中产生中断。n可以是0到255中的任意一个数。
----> 异常来源:
1 处理器检测到的程序错误
  x86处理器为其检测到的每个异常定义了一个向量号，当检测到程序错误时就会触发异常。
2 软件产生的异常
  int n 指令
---->异常分类
1 故障fault
  可以纠正的异常。异常处理程序的返回地址是产生fault的指令。异常处理程序返回后重新执行这个指令。如缺页异常
2 陷阱trap
  trap异常处理程序的返回地址是引起trap指令的下一条指令，程序返回后执行引起trap指令的下一条指令。
3 中止abort
  用于报告严重的错误，此时已经无法报告导致异常指令的精确位置，并且不允许导致异常的程序重新执行。
---->开启和禁止中断
标志寄存器EFLAGS的中断允许标志IF(interrupt enable flag)
IF==1 处理器引脚INTR引起的中断会被处理
IF==0 处理器引脚INTR引起的中断不会被处理
但IF标志不影响NMI引脚，也不影响处理器产生的异常。
---->中断描述符表 IDT表
IDT表是一块内存，共有256个表项，每个向量号对应一个表项，每个表项8个字节。IDTR寄存器存储着这块内存的基地址和长度。
一个8字节的表项就是一个IDT描述符，IDT表可以有三种类型的门描述符:中断门描述符、陷阱门描述符、任务门描述符。
1 中断门描述符
2 陷阱门描述符
3 任务门描述符

---->IRQ
每个能够发出中断的硬件设备都有一条名为IRQ(Interrupt ReQuest)的输出线。这条线和中断控制器相连，通过它向cpu发送中断。
IRQ线从0开始编号，IRQ0、IRQ1等。与IRQn关联的Intel的缺省向量号是n+32。



---->
  
      

     

