/*libemu test*/
#include <emu/emu.h>
#include <emu/emu_shellcode.h>
#include <emu/emu_memory.h>

struct emu *emu;

char shellcode[] =  
    	"\xbe\x1f\x5e\x89\x76\x09\x31\xc0\x88\x46\x08\x89\x46\x0d\xb0\x0b"  
    	"\x89\xf3\x8d\x4e\x09\x8d\x56\x0d\xcd\x80\x31\xdb\x89\xd8\x40\xcd"  
    	"\x80\xe8\xdc\xff\xff\xff\x2f\x62\x69\x6e\x2f\x6c\x73\x00\xc9\xc3"; 

int main()
{
	emu = emu_new();
	if ( emu_shellcode_test(emu, (uint8_t *)shellcode, 48) >= 0 )
        {
        	fprintf(stderr, "suspecting shellcode\n");
        }
	emu_free(emu);
	return 0;
}

/*
git clone git://git.carnivore.it/libemu.git libemu
cd libemu
autoreconf -v -i
./configure --prefix=/opt/dionaea
make install
*/






















































/*
使用python检测shellcode
减小字体  增大字体
看到python东西就有一种莫名的兴奋，个人觉得编程越简单越好，在IT人员被定义成21世纪矿工的今天，代码写的越多只能代表你矿挖的多，但不代表你挖的矿有价值或是可以换取更多的价值。何况国内多少人是在挖人挖剩下的矿渣。

    读了DVLabs的一篇文章“Shellcode Detection Using Python”，便动手实践了一下。Dvlabs说:“他们收集了大量的文件和文档，要识别出这些文档那些是恶意的，需要大量的人工分析，他们为了减少工作量想采用了自动化分析的方法。自动化恶意文档分析的主要方法之一是shellcode检测，即检测文档中是否包含shellcode”。

    DVLabs文章中提到了两个python版的shellcode检测工具：Pylibemu、Pylibscizzle。

Pylibemu 封装了Libemu http://libemu.carnivore.it/，提供了更多的功能，但并没有增加使用的复杂程度。Pylibemu一个重要的功能函数是test(),这个函数可以看出shellcode调用windows API信息。

Pylibemu实际测试：

    安装Pylibemu，先下载https://github.com/buffer/pylibemu，再下载libemu

git clone git://git.carnivore.it/libemu.git

windows平台下git可使用msysgit（http://code.google.com/p/msysgit/downloads/list）

    我的测试环境是windows 7 ，在windows平台下使用libemu需要安装Cygwin，并需要以下包：

- gcc;

- make;

- automake;

- libtool;

- gettext-devel;

- python

    将下载好libemu放置的指定目录下，最好在windows下设置Cygwin的环境变量。

    在configure.ac中添加AC_CONFIG_MACRO_DIR([m4]),内容如下:

# -*- mode: m4; -*-

# -*- Autoconf -*-

# Process this file with autoconf to produce a configure script.

# $Id$

AC_CONFIG_MACRO_DIR([m4])

AC_PREREQ(2.59)

....

    在Cygwin命令行下切换至libemu目录输入autoreconf -v –i

    删除在configure.ac中添加的AC_CONFIG_MACRO_DIR([m4])

    在Cygwin命令行下输入./configure --prefix=/opt/libemu，最后会提示错误：

checking for cargos-lib.h... no

configure: creating ./config.status

.in'ig.status: error: cannot find input file: `Makefile

    解决办法是：先用notpad++将configure文件转换为windows格式，保存。在将configure文件转换会linux格式保存。

重新运行./configure --prefix=/opt/libemu

    运行make，又会出现如下错误：

cc1: warnings being treated as errors

userhooks.c: In function ‘append’:

userhooks.c:168:3: error: array subscript has type ‘char’

Makefile:365: recipe for target `sctest-userhooks.o' failed

make[3]: *** [sctest-userhooks.o] Error 1

make[3]: Leaving directory `/cygdrive/f/linux/libemu/tools/sctest'

Makefile:264: recipe for target `all-recursive' failed

make[2]: *** [all-recursive] Error 1

make[2]: Leaving directory `/cygdrive/f/linux/libemu/tools'

Makefile:353: recipe for target `all-recursive' failed

make[1]: *** [all-recursive] Error 1

make[1]: Leaving directory `/cygdrive/f/linux/libemu'

Makefile:260: recipe for target `all' failed

make: *** [all] Error 2

    解决方法：修改tools\sctest目录下userhooks.c的168行为

if ( isprint((int)data[i]))// || isblank(data[i]))

    运行make install

running build

running build_ext

    将Pylibeum解压到指定目录，在Cygwin命令行下

    运行python setup.py build

running build

running build_ext

    运行python setup.py install

running install

running build

running build_ext

building 'pylibemu' extension

...

copying build/lib.cygwin-1.7.9-i686-2.6/pylibemu.dll -> /usr/lib/python2.6/site-packages

running install_egg_info

Writing /usr/lib/python2.6/site-packages/pylibemu-0.1.4-py2.6.egg-info

    非常顺利的安装成功了,在cygwin下运行python,进入python交互式命令行运行

Import pylibemu

    悲剧的事情发生了,提示如下错误:

>>> import pylibemu

Traceback (most recent call last):

  File "<stdin>", line 1, in <module>

ImportError: No such file or directory

    这个问题花了我近一个下午的时间才解决,其实很多python的安装包在cygwin下会出现这个问题,如果仔细观看pylibemu的安装信息会发现,pylibemu只向site-packages目录下写了pylibemu-0.1.4-py2.6.egg-info和pylibemu.dll文件,也就是说实体文件只有pylibemu.dll,最后终于通过google搜到了一篇相关一点的文章,作者说对于只有dll的cygwin python模块出现No such file or directory原因可能是dll无法加载,通过提示有仔细看了一下ImportError,提示的是文件或目录不存在,而不是模块不存在。

运行cygcheck.exe /usr/lib/python2.6/site-packages/pylibemu.dll

    提示如下错误：

F:\cygwin\lib\python2.6\site-packages\pylibemu.dll

cygcheck: track_down: could not find cygemu-2.dll

    原来是无法找到cygemu-2.dll，导致pylibemu.dll无法加载。cygemu-2.dll是libemu在cygwin下编译的文件，该文件在/opt/libemu/bin目录下，可能是我没有加环境变量，我得做法不是加环境变量，而是将cygemu-2.dll考到cygwin的bin目录下一份。


*/
