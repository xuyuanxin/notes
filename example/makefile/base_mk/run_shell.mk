-------------------------------------------------------------------------------------
# http://www.blogjava.net/jasmine214--love/archive/2012/01/10/368191.html
# 在Makefile中写shell代码有点诡异，和不同的shell语法不太一样，如果不了解，看Makefile会
# 莫名其妙。下面总结了一些。

# 1 Makefile文件的目标项冒号后的另起一行的代码才是shell代码。
# eg：
xx = xx1      # 这里是makefile代码
yy: xx = xx2  # 这是是makefile代码，makefile允许变量赋值时，'='号两边留空格
yy:
    xx=xx3    # 只有这里是shell代码 ，shell不允许‘=’号两边有空格哦。
# 有一个例外：
# xx=$(shell 这里的代码也是shell代码)

# 2 Makefile中的shell，每一行是一个进程，不同行之间变量值不能传递。所以，Makefile中的
# shell不管多长也要写在一行。
# eg：
SUBDIR=src example
all:
    @for subdir in $(SUBDIR); # 这里往下是一行shell
    do/
        echo "building " $$subdir; 
    done
3：Makefile中的变量以$开头， 所以，为了避免和shell的变量冲突，shell的变量以$$开头
eg1：从当前目录路径中提取出 /application 或 /base_class 之前的部分
PROJECT_ROOT_DIR = $(shell pwd | awk -F'/application|/base_class' '{print $$1}')
eg2：上例中$$subdir就是shell中的变量， 而$(SUBDIR)是Makefile的中的变量

=============================================================================================
1、在Makefile中只能在target中调用Shell脚本，其他地方是不能输出的。比如如下代码就是没有任何输出：

VAR="Hello"
echo "$VAR"

all:
   .....
以上代码任何时候都不会输出，没有在target内，如果上述代码改为如下：

VAR="Hello"

all:
    echo "$VAR"
    .....
以上代码，在make all的时候将会执行echo命令。

2、在Makefile中执行shell命令，一行创建一个进程来执行。这也是为什么很多Makefile中有很多行的末尾都是“;  \”，以此来保证代码是一行而不是多行，这样Makefile可以在一个进程中执行，例如：

SUBDIR=src example
all:
    @for subdir in $(SUBDIR); \
    do\
        echo "building "; \
    done
上述可以看出for循环中每行都是以”; \”结尾的。

3、Makefile中所有以$打头的单词都会被解释成Makefile中的变量。如果你需要调用shell中的变量（或者正则表达式中锚定句位$），都需要加两个$符号（$$）。实例如下：

PATH="/data/"

all:
    echo ${PATH}
    echo $$PATH
例子中的第一个${PATH}引用的是Makefile中的变量，而不是shell中的PATH环境变量，后者引用的事Shell中的PATH环境变量。

     以上三点的是Makefile调用shell应该注意的地方，写Makefile一定要注意。