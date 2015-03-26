#------------------------------------------------------------------------------------
.PHONY: clean

simple.exe: main.o foo.o
	gcc -o simple.exe main.o foo.o
main.o: main.c
	gcc -o main.o -c main.c
foo.o: foo.c
	gcc -o foo.o -c foo.c
clean:
	rm simple.exe main.o foo.o
	
#makefile的3个关键概念: 目标 依赖关系(先决条件) 命令
#目标
#目标就是要干什么，或者运行make后生成什么。
#依赖
#依赖是指明目标所依赖的其它目标。
#命令
#命令则告诉make如何生成目标。
#规则
#一个规则由目标、先决条件和命令组成。
#
#上例中simple.exe就是目标，它依赖main.o和foo.o这两个目标。
#gcc -o simple.exe main.o foo.o 就是命令。
#以上的意思就是:
#我的目标是生成simple.exe文件，但是生成这个文件前，必须首先生成main.o 和 foo.o这两个文
#件。我不关心main.o和foo.o如何生成，只要这两个文件存在，我就用我的命令生成simple.exe。
#如果main.o不存在，那么一定有其它的目标用来生成这个文件，于是先去做成这个目标，再来完
#成我的目标。
#
#----> 先决条件的顺序
#从左到右
#
#
#----> .PHONY 的作用
#
#----> 默认目标
#
#----> 多个目标
#all test:
#----> 启动一个目标  make main.o 
#----> 启动多个目标  make main.o foo.o
#从左到右的运行目标


