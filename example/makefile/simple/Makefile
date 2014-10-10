.PHONY: clean #定义假目标

CC = gcc
RM = rm

EXE = simple.exe

#wildcard:通配符函数。wildcard _pattern表示当前工作目录中满足_pattern模式的文件或目录名列表
#当前目录下有两个文件main.c foo.c，所以SRCS = main.c foo.c
#patsubst _pattern,_replacement,_text表示把名字列表_text中符合_pattern模式的名字替换成_replacement
SRCS = $(wildcard *.c)             #SRCS = main.c foo.c
OBJS = $(patsubst %.c,%.o,$(SRCS)) #OBJS = main.o foo.o

#$@:规则中的目标。这个规则的目标是simple.exe，所以$@是simple.exe
#$^:规则中的所有先决条件。
#-o:gcc编译结果改名选项，改名为simple.exe
#simple.exe ：main.o foo.o
#	gcc -o simple.exe main.o foo.o
$(EXE) : $(OBJS)
	$(CC) -o $@ $^
	
#-c:gcc会编译并汇编该代码，产生.o目标文件
%.o: %.c
	$(CC) -o $@ -c $^ 
clean:
	$(RM) -fr $(EXE) $(OBJS)

