/*
----> 管道
1 一般是半双工的,有些系统提供全双工管道.
2 只能在具有公共祖先的进程之间使用,通常,管道由一个进程创建,然后该进程调用fork,此后父子进程之间就可应用该管道.
  父进程到子进程的管道:父进程关闭管道的读端(fd[0]),子进程关闭写端(fd[1]).
  子进程到父进程的管道:父进程关闭fd[1],子进程关闭fd[0].
3 读一个写端已被关闭的管道时,在所有数据都被读取后,read返回0,表示到达了文件结束处.
4 写一个读端已被关闭的管道,则产生信号SIGPIPE.如果忽略该信号或者从其信号处理程序返回,则write返回-1,errno设置为EPIPE.


管道可以将一个命令的输出导向另一个命令的输入，从而让两个(或者更多命令)像流水线一样连
续工作，不断地处理文本流。在命令行中，我们用|表示管道：

$cat < a.txt | wc 

wc命令代表word count，用于统计文本中的行、词以及字符的总数。a.txt中的文本先流到cat，
然后从cat的标准输出流到wc的标准输入，从而让wc知道自己要处理的是a.txt这个字符串。

----> fifo
FIFO (First in, First out)为一种特殊的文件类型，它在文件系统中有对应的路径。当一个进
程以读(r)的方式打开该文件，而另一个进程以写(w)的方式打开该文件，那么内核就会在这两个
进程之间建立管道，所以FIFO实际上也由内核管理，不与硬盘打交道。之所以叫FIFO，是因为管
道本质上是一个先进先出的队列数据结构，最早放入的数据被最先读出来(好像是传送带，一头放
货，一头取货)，从而保证信息交流的顺序。FIFO只是借用了文件系统(file system, 参考Linux
文件管理背景知识)来为管道命名。写模式的进程向FIFO文件中写入，而读模式的进程从FIFO文件
中读出。当删除FIFO文件时，管道连接也随之消失。FIFO的好处在于我们可以通过文件的路径来识
别管道，从而让没有亲缘关系的进程之间建立连接。

FIFO不同于管道之处在于它提供一个路径名与之关联，以FIFO的文件形式存在于文件系统中。这
样，即使与FIFO的创建进程不存在亲缘关系的进程，只要可以访问该路径，就能够彼此通过FIFO
相互通信（能够访问该路径的进程以及FIFO的创建进程之间），因此，通过FIFO不相关的进程也
能交换数据。值得注意的是，FIFO严格遵循先进先出（first in first out），对管道及FIFO的
读总是从开始处返回数据，对它们的写则把数据添加到末尾。它们不支持诸如lseek()等文件定位
操作。

FIFO的打开规则：open
    如果当前打开操作是为读而打开FIFO时，若已经有相应进程为写而打开该FIFO，则当前打开
    操作将成功返回；否则，可能阻塞直到有相应进程为写而打开该FIFO（当前打开操作设置了
    阻塞标志）；或者，成功返回（当前打开操作没有设置阻塞标志）。
    如果当前打开操作是为写而打开FIFO时，如果已经有相应进程为读而打开该FIFO，则当前打
    开操作将成功返回；否则，可能阻塞直到有相应进程为读而打开该FIFO（当前打开操作设置
    了阻塞标志）；或者，返回ENXIO错误（当前打开操作没有设置阻塞标志）。
    
从FIFO中读取数据：
    约定：如果一个进程为了从FIFO中读取数据而阻塞打开FIFO，那么称该进程内的读操作为设
    置了阻塞标志的读操作。
    如果有进程写打开FIFO，且当前FIFO内没有数据，则对于设置了阻塞标志的读操作来说，将
    一直阻塞。对于没有设置阻塞标志读操作来说则返回-1，当前errno值为EAGAIN， 提醒以后
    再试。
    
    对于设置了阻塞标志的读操作说，造成阻塞的原因有两种：当前FIFO内有数据，但有其它进
    程在读这些数据；另外就是FIFO内没有数据。解阻塞的原因则是FIFO中有新的数据写入，不
    论信写入数据量的大小，也不论读操作请求多少数据量。
    
    读打开的阻塞标志只对本进程第一个读操作施加作用，如果本进程内有多个读操作序列，则
    在第一个读操作被唤醒并完成读操作后，其它将要执行的读操作将不再阻塞，即使在执行读
    操作时，FIFO中没有数据也一样（此时，读操作返回0）。
    
    如果没有进程写打开FIFO，则设置了阻塞标志的读操作会阻塞。
    
    注：如果FIFO中有数据，则设置了阻塞标志的读操作不会因为FIFO中的字节数小于请求读的
    字节数而阻塞，此时，读操作会返回FIFO中现有的数据量。
    
向FIFO中写入数据：
    约定：如果一个进程为了向FIFO中写入数据而阻塞打开FIFO，那么称该进程内的写操作为设
    置了阻塞标志的写操作。
    
对于设置了阻塞标志的写操作：
    当要写入的数据量不大于PIPE_BUF时，linux将保证写入的原子性。 如果此时管道空闲缓冲
    区不足以容纳要写入的字节数，则进入睡眠，直到当缓冲区中能够容纳要写入的字节数时，
    才开始进行一次性写操作。
    
    当要写入的数据量大于PIPE_BUF时，linux将不再保证写入的原子性。 FIFO缓冲区一有空闲
    区域，写进程就会试图向管道写入数据，写操作在写完所有请求写的数据后返回。

对于没有设置阻塞标志的写操作：
    当要写入的数据量大于PIPE_BUF时，linux将不再保证写入的原子性。 在写满所有FIFO空闲
    缓冲区后，写操作返回。
    
    当要写入的数据量不大于PIPE_BUF时，linux将保证写入的原子性。 如果当前FIFO空闲缓冲
    区能够容纳请求写入的字节数，写完后成功返回；如果当前FIFO空闲缓冲区不能够容纳请求
    写入的字节数，则返回EAGAIN错误，提醒以后再写；    

