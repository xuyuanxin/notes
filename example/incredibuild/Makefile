.PHONY: clean #定义假目标

CC = gcc
RM = rm

EXE = all

#SRCS = main.c test.c test1.c test2.c test3.c test4.c test5.c test6.c test7.c
SRCS = $(wildcard *.c)       
OBJS = $(patsubst %.c,%.o,$(SRCS))


$(EXE) : $(OBJS)
	$(CC) -o $@ main.o test.o test1.o test2.o test3.o test4.o test5.o test6.o test7.o

%.o: %.c
	$(CC) -o $@ -c $^ 
clean:
	$(RM) -fr $(EXE) $(OBJS)

