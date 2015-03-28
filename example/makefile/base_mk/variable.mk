#$ make -f variable.mk
#取变量名: $(name) or ${name}
.PHONY: all

all1 all2:
	@echo "\$$@=$@"
	@echo "MAKE=$(MAKE)"
	@echo "MAKECMDGOALS=$(MAKECMDGOALS)"

all3: first second third
	@echo "\$$@=$@"
	@echo "$$^=$^"
	@echo "$$<=$<"
	
first second third: 
	
#
#$ make -f variable.mk
#$@=all1
#MAKE=make
#MAKECMDGOALS=

#
#$ make -f variable.mk all1
#$@=all1
#MAKE=make
#MAKECMDGOALS=all1

#
#$ make -f variable.mk all2
#$@=all2
#MAKE=make
#MAKECMDGOALS=all2

#
#$ make -f variable.mk all1 all2
#$@=all1
#MAKE=make
#MAKECMDGOALS=all1 all2
#$@=all2
#MAKE=make
#MAKECMDGOALS=all1 all2

#
#$ make -f variable.mk all3
#$@=all3
#$^=first second third
#$<=first


#----> 变量的赋值
#----> = 递归扩展变量(recursively expanded variable)
foo=$(bar)
bar=$(ugh)
ugh=Huh?
all4:
	@echo $(foo)
#make
#Huh?

deaploop:
	abc=$(abc)

#----> := 简单扩展变量(simply expanded variable) 只进行一次扩展
x=before
y=$(x) x
x=later

xx:=before
yy:=$(xx) xx
xx:=later
all5:
	@echo "y=$(y) , yy=$(yy)"
#$ make -f variable.mk all5
#y=later x , yy=before xx

#----> ?= 条件赋值
va=haha
va?=aaa
vb?=haha
all6:
	@echo "va=$(va) , vb=$(vb)"
#$ make -f variable.mk all6
#va=haha , vb=haha

#----> += 追加赋值
objects=main.o foo.o
objects+=bar.o
all7:
	@echo $(objects)
#$ make -f variable.mk all7
#main.o foo.o bar.o


#----> 变量的来源
#1 上下文
#例如上面的几个例子，all6等。
#2 命令行
#make bar=x
#可以覆盖makefile文件中定义的变量
#如果不想被覆盖，可以这样定义
#override foo=y
#3 shell环境
#export bar=x
#
#----> 
ffo=a.c b.c
ffo:=$(ffo:.c=.o)
all8:
	@echo "ffo=$(ffo)"
#$ make -f variable.mk all8
#ffo=a.o b.o
