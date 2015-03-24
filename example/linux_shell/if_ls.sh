#!/bin/bash
#------------------------------------------------------------------------------------
#The if statement has the following syntax:
#if commands; then
#commands
#[elif commands; then
#commands...]
#[else
#commands]
#fi
#
#
#位置参数 $1， $2,..., $N，$#代表了命令行的参数数量， $0代表了脚本的名字，
if [ ! $#==2 ]; then
    echo "Usage: $0 para1 para2"
    exit 0
fi
#
if [$para1 -le $para2]; then
    echo "para1 <= para2"
else
    echo "para > para2"
fi
#
#shell 编程中使用到得if语句内判断参数
#–b 当file存在并且是块文件时返回真
#-c 当file存在并且是字符文件时返回真
#-d 当pathname存在并且是一个目录时返回真
#-e 当pathname指定的文件或目录存在时返回真
#-f 当file存在并且是正规文件时返回真
#-g 当由pathname指定的文件或目录存在并且设置了SGID位时返回为真
#-h 当file存在并且是符号链接文件时返回真，该选项在一些老系统上无效
#-k 当由pathname指定的文件或目录存在并且设置了“粘滞”位时返回真
#-p 当file存在并且是命令管道时返回为真
#-r 当由pathname指定的文件或目录存在并且可读时返回为真
#-s 当file存在文件大小大于0时返回真
#-u 当由pathname指定的文件或目录存在并且设置了SUID位时返回真
#-w 当由pathname指定的文件或目录存在并且可执行时返回真。一个目录为了它的内容被访问必然
#   是可执行的。
#-o 当由pathname指定的文件或目录存在并且被子当前进程的有效用户ID所指定的用户拥有时返回
#   真。

#UNIX Shell 里面比较字符写法：
#-eq   等于
#-ne    不等于
#-gt    大于
#-lt    小于
#-le    小于等于
#-ge   大于等于
#-z    空串
#=    两个字符相等
#!=    两个字符不等
#-n    非空串
#-------------------------------------------------------------------------
#更为详细的说明：
#运算符                     描述                          示例

#文件比较运算符
#-e filename     如果 filename 存在，则为真            [ -e /var/log/syslog ]
#-d filename     如果 filename 为目录，则为真          [ -d /tmp/mydir ]
#-f filename     如果 filename 为常规文件，则为真      [ -f /usr/bin/grep ]
#-L filename     如果 filename 为符号链接，则为真      [ -L /usr/bin/grep ]
#-r filename     如果 filename 可读，则为真            [ -r /var/log/syslog ]
#-w filename     如果 filename 可写，则为真            [ -w /var/mytmp.txt ]
#-x filename     如果 filename 可执行，则为真          [ -L /usr/bin/grep ]

#filename1 -nt filename2 如果 filename1 比 filename2 新，则为真 
#[ /tmp/install/etc/services -nt /etc/services ]
#filename1 -ot filename2   如果 filename1 比 filename2 旧，则为真  
#[ /boot/bzImage -ot arch/i386/boot/bzImage ]

#字符串比较运算符 （请注意引号的使用，这是防止空格扰乱代码的好方法）
#-z string           如果 string 长度为零，则为真         [ -z $myvar ]
#-n string           如果 string 长度非零，则为真         [ -n $myvar ]
#string1 = string2   如果 string1 与 string2 相同，则为真 [ $myvar = one two three ]
#string1 != string2  如果 string1 与 string2 不同，则为真 [ $myvar != one two three ]

#算术比较运算符
#num1 -eq num2       等于        [ 3 -eq $mynum ]
#num1 -ne num2       不等于      [ 3 -ne $mynum ]
#num1 -lt num2       小于        [ 3 -lt $mynum ]
#num1 -le num2       小于或等于  [ 3 -le $mynum ]
#num1 -gt num2       大于        [ 3 -gt $mynum ]
#num1 -ge num2       大于或等于  [ 3 -ge $mynum ]