https://docs.python.org/2/howto/argparse.html#id1  Argparse Tutorial
https://docs.python.org/2/library/argparse.html#module-argparse   API

http://www.tuicool.com/articles/ZF3y6b  Python命令行解析库argparse

					
def add_argument(name or flags...[, action][, nargs][, const][, default]\
  [, type][, choices][, required][, help][, metavar][, dest]):
  '''
  ArgumentParser.add_argument
  
  parser.add_argument("-v", "--verbosity", type=int, choices=[0, 1, 2],
                    help="increase output verbosity")
  python prog.py -v 2
  
  parser.add_argument("-v", "--verbosity", action="count", default=0,
                    help="increase output verbosity")
  python prog.py -vv 
  if args.verbosity == 2:
  
  parser.add_argument("square", type=int,
                    help="display a square of a given number")
  python prog.py 2
  '''
  pass

  
  
  
  
  
  
  
Python命令行解析库argparse - 再见紫罗兰
时间 2014-08-13 05:48:00  Python_博客园
原文  http://www.cnblogs.com/linxiyue/p/3908623.html
主题 Python
2.7之后python不再对optparse模块进行扩展，python标准库推荐使用argparse模块对命令行进行解析。

1.example

有一道面试题：编写一个脚本main.py，使用方式如下：

main.py -u http://www.sohu.com  -d 'a=1,b=2,c=3' -o /tmp/index.html

功能要求：打开-u指定的页面，将页面中所有的链接后面增加参数a=1&b=2&c=3(需要考虑链接中已经存在指定的参数的问题), 然后保存到-o指定的文件中。

import argparse
import urllib
from pyquery import PyQuery as pq
def getArgs():
  parse=argparse.ArgumentParser()
  parse.add_argument('-u',type=str)
  parse.add_argument('-d',type=str)
  parse.add_argument('-o',type=str)
  args=parse.parse_args()
  return vars(args)
def urlAddQuery(url,query):
  query=query.replace(',','&')  
  if '?' in url:
    return url.replace('?','?'+query+'&')
  else:
    return url+'?'+query
def getHref():
  args=getArgs()
  url=args['u']
  query=args['d'].strip("\'")
  fileName=args['o']
  doc=pq(url=url)
  with open(fileName,'w') as f:
    for a in doc('a'):
      a=pq(a)
      href=a.attr('href')
      if href:
        newurl=urlAddQuery(href,query)
        f.write(newurl+'\n')
if __name__=='__main__':
  getHref()
2.创建解析器

import argparse
parser = argparse.ArgumentParser()
class ArgumentParser (prog=None, usage=None, description=None, epilog=None, parents=[], formatter_class=argparse.HelpFormatter, prefix_chars='-', fromfile_prefix_chars=None, argument_default=None, conflict_handler='error', add_help=True)

创建一个ArgumentParser实例对象，ArgumentParser对象的参数都为关键字参数。

prog ：程序的名字，默认为sys.argv[0]，用来在help信息中描述程序的名称。

>>> parser = argparse.ArgumentParser(prog='myprogram')
>>> parser.print_help()
usage: myprogram [-h]

optional arguments:
 -h, --help  show this help message and exit
usage ：描述程序用途的字符串

>>> parser = argparse.ArgumentParser(prog='PROG', usage='%(prog)s [options]')
>>> parser.add_argument('--foo', nargs='?', help='foo help')
>>> parser.add_argument('bar', nargs='+', help='bar help')
>>> parser.print_help()
usage: PROG [options]

positional arguments:
 bar          bar help

optional arguments:
 -h, --help   show this help message and exit
 --foo [FOO]  foo help
description ：help信息前的文字。

epilog ：help信息之后的信息

>>> parser = argparse.ArgumentParser(
...     description='A foo that bars',
...     epilog="And that's how you'd foo a bar")
>>> parser.print_help()
usage: argparse.py [-h]

A foo that bars

optional arguments:
 -h, --help  show this help message and exit

And that's how you'd foo a bar
parents ：由ArgumentParser对象组成的列表，它们的arguments选项会被包含到新ArgumentParser对象中。

>>> parent_parser = argparse.ArgumentParser(add_help=False)
>>> parent_parser.add_argument('--parent', type=int)

>>> foo_parser = argparse.ArgumentParser(parents=[parent_parser])
>>> foo_parser.add_argument('foo')
>>> foo_parser.parse_args(['--parent', '2', 'XXX'])
Namespace(foo='XXX', parent=2)
formatter_class ：help信息输出的格式,

prefix_chars ：参数前缀，默认为'-'

>>> parser = argparse.ArgumentParser(prog='PROG', prefix_chars='-+')
>>> parser.add_argument('+f')
>>> parser.add_argument('++bar')
>>> parser.parse_args('+f X ++bar Y'.split())
Namespace(bar='Y', f='X')
fromfile_prefix_chars ：前缀字符，放在文件名之前

>>> with open('args.txt', 'w') as fp:
...    fp.write('-f\nbar')
>>> parser = argparse.ArgumentParser(fromfile_prefix_chars='@')
>>> parser.add_argument('-f')
>>> parser.parse_args(['-f', 'foo', '@args.txt'])
Namespace(f='bar')
当参数过多时，可以将参数放到文件中读取，例子中parser.parse_args(['-f', 'foo', '@args.txt'])解析时会从文件args.txt读取，相当于 ['-f',  'foo',  '-f',  'bar']。

argument_default ：参数的全局默认值。例如，要禁止parse_args时的参数默认添加，我们可以：

>>> parser = argparse.ArgumentParser(argument_default=argparse.SUPPRESS)
>>> parser.add_argument('--foo')
>>> parser.add_argument('bar', nargs='?')
>>> parser.parse_args(['--foo', '1', 'BAR'])
Namespace(bar='BAR', foo='1')
>>> parser.parse_args()
Namespace()
当parser.parse_args()时不会自动解析foo和bar了。

conflict_handler ：解决冲突的策略，默认情况下冲突会发生错误：

>>> parser = argparse.ArgumentParser(prog='PROG')
>>> parser.add_argument('-f', '--foo', help='old foo help')
>>> parser.add_argument('--foo', help='new foo help')
Traceback (most recent call last):
 ..
ArgumentError: argument --foo: conflicting option string(s): --foo
我们可以设定冲突解决策略：

>>> parser = argparse.ArgumentParser(prog='PROG', conflict_handler='resolve')
>>> parser.add_argument('-f', '--foo', help='old foo help')
>>> parser.add_argument('--foo', help='new foo help')
>>> parser.print_help()
usage: PROG [-h] [-f FOO] [--foo FOO]

optional arguments:
 -h, --help  show this help message and exit
 -f FOO      old foo help
 --foo FOO   new foo help
　 add_help ：设为False时，help信息里面不再显示-h --help信息。

3.添加参数选项

>>> parser.add_argument('integers', metavar='N', type=int, nargs='+',
...                     help='an integer for the accumulator')
>>> parser.add_argument('--sum', dest='accumulate', action='store_const',
...                     const=sum, default=max,
...                     help='sum the integers (default: find the max)')
add_argument (name or flags...[, action][, nargs][, const][, default][, type][, choices][, required][, help][, metavar][, dest])

name or flags ：参数有两种，可选参数和位置参数。

添加可选参数：

>>> parser.add_argument('-f', '--foo')
添加位置参数：

>>> parser.add_argument('bar')
parse_args()运行时，会用'-'来认证可选参数，剩下的即为位置参数。

>>> parser = argparse.ArgumentParser(prog='PROG')
>>> parser.add_argument('-f', '--foo')
>>> parser.add_argument('bar')
>>> parser.parse_args(['BAR'])
Namespace(bar='BAR', foo=None)
>>> parser.parse_args(['BAR', '--foo', 'FOO'])
Namespace(bar='BAR', foo='FOO')
>>> parser.parse_args(['--foo', 'FOO'])
usage: PROG [-h] [-f FOO] bar
PROG: error: too few arguments
解析时没有位置参数就会报错了。

action: 默认为store

store_const，值存放在const中：

>>> parser = argparse.ArgumentParser()
>>> parser.add_argument('--foo', action='store_const', const=42)
>>> parser.parse_args('--foo'.split())
Namespace(foo=42)
store_true和store_false，值存为True或False

>>> parser = argparse.ArgumentParser()
>>> parser.add_argument('--foo', action='store_true')
>>> parser.add_argument('--bar', action='store_false')
>>> parser.add_argument('--baz', action='store_false')
>>> parser.parse_args('--foo --bar'.split())
Namespace(bar=False, baz=True, foo=True)
append：存为列表

>>> parser = argparse.ArgumentParser()
>>> parser.add_argument('--foo', action='append')
>>> parser.parse_args('--foo 1 --foo 2'.split())
Namespace(foo=['1', '2'])
append_const：存为列表，会根据const关键参数进行添加：

>>> parser = argparse.ArgumentParser()
>>> parser.add_argument('--str', dest='types', action='append_const', const=str)
>>> parser.add_argument('--int', dest='types', action='append_const', const=int)
>>> parser.parse_args('--str --int'.split())
Namespace(types=[<type 'str'>, <type 'int'>])
count：统计参数出现的次数

>>> parser = argparse.ArgumentParser()
>>> parser.add_argument('--verbose', '-v', action='count')
>>> parser.parse_args('-vvv'.split())
Namespace(verbose=3)
help：help信息

version：版本

>>> import argparse
>>> parser = argparse.ArgumentParser(prog='PROG')
>>> parser.add_argument('--version', action='version', version='%(prog)s 2.0')
>>> parser.parse_args(['--version'])
PROG 2.0
nrgs： 参数的数量

值可以为整数N(N个)，*(任意多个)，+(一个或更多)

>>> parser = argparse.ArgumentParser()
>>> parser.add_argument('--foo', nargs='*')
>>> parser.add_argument('--bar', nargs='*')
>>> parser.add_argument('baz', nargs='*')
>>> parser.parse_args('a b --foo x y --bar 1 2'.split())
Namespace(bar=['1', '2'], baz=['a', 'b'], foo=['x', 'y'])
值为？时，首先从命令行获得参数，若没有则从const获得，然后从default获得：

>>> parser = argparse.ArgumentParser()
>>> parser.add_argument('--foo', nargs='?', const='c', default='d')
>>> parser.add_argument('bar', nargs='?', default='d')
>>> parser.parse_args('XX --foo YY'.split())
Namespace(bar='XX', foo='YY')
>>> parser.parse_args('XX --foo'.split())
Namespace(bar='XX', foo='c')
>>> parser.parse_args(''.split())
Namespace(bar='d', foo='d')
更常用的情况是允许参数为文件

>>> parser = argparse.ArgumentParser()
>>> parser.add_argument('infile', nargs='?', type=argparse.FileType('r'),
...                     default=sys.stdin)
>>> parser.add_argument('outfile', nargs='?', type=argparse.FileType('w'),
...                     default=sys.stdout)
>>> parser.parse_args(['input.txt', 'output.txt'])
Namespace(infile=<open file 'input.txt', mode 'r' at 0x...>,
          outfile=<open file 'output.txt', mode 'w' at 0x...>)
>>> parser.parse_args([])
Namespace(infile=<open file '<stdin>', mode 'r' at 0x...>,
          outfile=<open file '<stdout>', mode 'w' at 0x...>)
const ：保存一个常量

default ：默认值

type ：参数类型

choices ：可供选择的值

>>> parser = argparse.ArgumentParser(prog='doors.py')
>>> parser.add_argument('door', type=int, choices=range(1, 4))
>>> print(parser.parse_args(['3']))
Namespace(door=3)
>>> parser.parse_args(['4'])
usage: doors.py [-h] {1,2,3}
doors.py: error: argument door: invalid choice: 4 (choose from 1, 2, 3)
required ：是否必选

desk ：可作为参数名

>>> parser = argparse.ArgumentParser()
>>> parser.add_argument('--foo', dest='bar')
>>> parser.parse_args('--foo XXX'.split())
Namespace(bar='XXX')
4.解析参数

参数有几种写法：

最常见的空格分开：

>>> parser = argparse.ArgumentParser(prog='PROG')
>>> parser.add_argument('-x')
>>> parser.add_argument('--foo')
>>> parser.parse_args('-x X'.split())
Namespace(foo=None, x='X')
>>> parser.parse_args('--foo FOO'.split())
Namespace(foo='FOO', x=None)
长选项用=分开

>>> parser.parse_args('--foo=FOO'.split())
Namespace(foo='FOO', x=None)
短选项可以写在一起：

>>> parser.parse_args('-xX'.split())
Namespace(foo=None, x='X')
parse_args()方法的返回值为namespace，可以用vars()内建函数化为字典：

>>> parser = argparse.ArgumentParser()
>>> parser.add_argument('--foo')
>>> args = parser.parse_args(['--foo', 'BAR'])
>>> vars(args)
{'foo': 'BAR'}