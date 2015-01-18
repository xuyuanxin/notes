#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>


/*
 打开文件"log.txt"(没有则创建)，并获取文件描述符oldfd。调用dup2函数，参数为oldfd和1，
 这会导致用我们新打开的文件描述符替换掉由1代表的文件描述符（即stdout，因为标准输出文
 件的id为1）。任何写到stdout的东西，现在都将改为写入名为"log.txt"的文件中。需要注意的
 是，dup2函数在复制了oldfd之后，会立即将其关闭，但不会关掉新近打开的文件描述符，因为
 文件描述符1现在也指向它。
*/
int dup2_eg01()
{
	int oldfd;
	oldfd = open("log.txt", (O_RDWR | O_CREAT), 0644 );
	if(oldfd < 0){
		printf("open fail!\r\n");
		return -1;
	}
	dup2( oldfd, 1 ); /* stdout */
	close( oldfd );
	printf("abcd\r\n"); /* output to file "log.txt"*/
	return 0;
}

int dup2_eg02()
{
    int pfds[2]; /* 0:read 1:write*/
	pid_t pid;
	int nbytes;
	char buf[1000] = {0};

    if ( pipe(pfds) < 0 ) {
        printf("pipe error \r\n");
		return -1;
    }
	pid = fork();
	if(pid < 0){
		printf("fork error \r\n");
	}
/*
 子进程关闭标准输出，把管道的写端复制到标准输出，相当于原来输出到标准输出的内容现在要
 写入管道。父进程读取管道里的数据，整个过程是子进程执行命令ls -l 的输出写入管道，父进
 程读取。
*/	
    if ( pid == 0 ) {

        close(1); /* STDOUT_FILENO */
        dup2( pfds[1], 1 );
        close( pfds[0] );
        if(execlp( "ls", "ls", "-l", NULL ) < 0){
			printf("execlp error");
			exit(0);
        }
    } else {
        #if 0
        close(0);
        dup2( pfds[0], 0 ); /* STDIN_FILENO */
        close( pfds[1] );
		//if (waitpid(pid, NULL, 0) < 0) {
            //printf("wait error\r\n");
        //}
		execlp( "wc", "wc", "-l", NULL );
        return 0;
		#else
		while(1) {
			close( pfds[1] );
		    nbytes = read(pfds[0],buf,sizeof(buf));
			if(nbytes <= 0){
				printf("father read %d bytes\r\n",nbytes);
				break;
			}
			printf("----> father read %d bytes:\r\n",nbytes);
			printf(buf);
		}	
		#endif
    }
}

int main()
{
    dup2_eg02();
}

/*
 http://hi.baidu.com/flikecn/item/e82e14bef06e8a412aebe38a

 3 CGI中dup2
 写过CGI程序的人都清楚，当浏览器使用post方法提交表单数据时，CGI读数据是从标准

输入stdin, 写数据是写到标准输出stdout(c语言利用printf函数)。按照我们正常的理

解，printf的输出应该在终端显示，原来CGI程序使用dup2函数将STDOUT_FINLENO(这个

宏在unitstd.h定义，为１)这个文件描述符重定向到了连接套接字。

dup2(connfd, STDOUT_FILENO)；　实际情况还涉及到了管道，不是本文的重点

如第一节所说，　一个进程默认的文件描述符１(STDOUT_FILENO)是和标准输出stdout相

关联的，对于内核而言，所有打开的文件都通过文件描述符引用，而内核并不知道流的

存在(比如stdin、stdout)，所以printf函数输出到stdout的数据最后都写到了文件描述

符１里面。至于文件描述符0、１、2与标准输入、标准输出、标准错误输出相关联，这

只是shell以及很多应用程序的惯例，而与内核无关。

用下面的流图可以说明问题:(ps: 虽然不是流图关系，但是还是有助于理解)

printf －> stdout －> STDOUT_FILENO(1) －> 终端(tty)

printf最后的输出到了终端设备，文件描述符１指向当前的终端可以这么理解：

STDOUT_FILENO = open("/dev/tty", O_RDWR);

使用dup2之后STDOUT_FILENO不再指向终端设备，　而是指向connfd, 所以printf的

输出最后写到了connfd。是不是很优美？:)

4. 如何在CGI程序的fork子进程中还原STDOUT_FILENO

如果你能看到这里，感谢你的耐心，　我知道很多人可能感觉有点复杂，　其实

复杂的问题就是一个个小问题的集合。所以弄清楚每个小问题就OK了，第三节中

说道，STDOUT_FILENO被重定向到了connfd套接字，　有时候我们可能想在CGI程序

中调用后台脚本执行，而这些脚本中难免会有一些输入输出，　我们知道fork之后，

子进程继承了父进程的所有文件描述符，所以这些脚本的输入输出并不会如我们愿

输出到终端设备，而是和connfd想关联了，这个显然会扰乱网页的输出。那么如何

恢复STDOUT_FILENO和终端关联呢？

方法１：在dup2之前保存原有的文件描述符，然后恢复。

代码实现如下：

savefd = dup(STDOUT_FILENO);　avefd此时指向终端

dup2(connfd, STDOUT_FILENO);   STDOUT_FILENO(1) 被重新指向connfd

..... 处理一些事情

dup2(savefd, STDOUT_FILENO); STDOUT_FILENO(1)　恢复指向savefd


很遗憾CGI程序无法使用这种方法，　因为dup2这些不是在CGI程序中完成的，而是在

web server中实现的，修改web server并不是个好主意。

方法2: 追本溯源，打开当前终端恢复STDOUT_FILENO。

分析第三节的流图，　STDOUT_FILENO是如何和终端关联的？　我们重头做一遍不就行

了，　代码实现如下：

ttyfd = open("/dev/tty", O_RDWR);

dup2(ttyfd, STDOUT_FILENO);

close(ttyfd);

/dev/tty是程序运行所在的终端，　这个应该通过一种方法获得。实践证明这种方法

是可行的，但是我总感觉有些不妥，不知道为什么，可能一些潜在的问题还没出现。

目前我就想到这两种方法，　不知道你有什么好的想法？　有的话希望告诉我:)


终于收尾了，一早上过来写，没想到写了两个小时才写完，好久没有写原创了，又重拾

了以前那美妙的感觉:)


*/
