https://docs.python.org/2/howto/argparse.html#id1  Argparse Tutorial
https://docs.python.org/2/library/argparse.html#module-argparse   API

http://www.tuicool.com/articles/ZF3y6b  Python�����н�����argparse

					
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

  
  
  
  
  
  
  
Python�����н�����argparse - �ټ�������
ʱ�� 2014-08-13 05:48:00  Python_����԰
ԭ��  http://www.cnblogs.com/linxiyue/p/3908623.html
���� Python
2.7֮��python���ٶ�optparseģ�������չ��python��׼���Ƽ�ʹ��argparseģ��������н��н�����

1.example

��һ�������⣺��дһ���ű�main.py��ʹ�÷�ʽ���£�

main.py -u http://www.sohu.com  -d 'a=1,b=2,c=3' -o /tmp/index.html

����Ҫ�󣺴�-uָ����ҳ�棬��ҳ�������е����Ӻ������Ӳ���a=1&b=2&c=3(��Ҫ�����������Ѿ�����ָ���Ĳ���������), Ȼ�󱣴浽-oָ�����ļ��С�

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
2.����������

import argparse
parser = argparse.ArgumentParser()
class ArgumentParser (prog=None, usage=None, description=None, epilog=None, parents=[], formatter_class=argparse.HelpFormatter, prefix_chars='-', fromfile_prefix_chars=None, argument_default=None, conflict_handler='error', add_help=True)

����һ��ArgumentParserʵ������ArgumentParser����Ĳ�����Ϊ�ؼ��ֲ�����

prog ����������֣�Ĭ��Ϊsys.argv[0]��������help��Ϣ��������������ơ�

>>> parser = argparse.ArgumentParser(prog='myprogram')
>>> parser.print_help()
usage: myprogram [-h]

optional arguments:
 -h, --help  show this help message and exit
usage ������������;���ַ���

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
description ��help��Ϣǰ�����֡�

epilog ��help��Ϣ֮�����Ϣ

>>> parser = argparse.ArgumentParser(
...     description='A foo that bars',
...     epilog="And that's how you'd foo a bar")
>>> parser.print_help()
usage: argparse.py [-h]

A foo that bars

optional arguments:
 -h, --help  show this help message and exit

And that's how you'd foo a bar
parents ����ArgumentParser������ɵ��б����ǵ�argumentsѡ��ᱻ��������ArgumentParser�����С�

>>> parent_parser = argparse.ArgumentParser(add_help=False)
>>> parent_parser.add_argument('--parent', type=int)

>>> foo_parser = argparse.ArgumentParser(parents=[parent_parser])
>>> foo_parser.add_argument('foo')
>>> foo_parser.parse_args(['--parent', '2', 'XXX'])
Namespace(foo='XXX', parent=2)
formatter_class ��help��Ϣ����ĸ�ʽ,

prefix_chars ������ǰ׺��Ĭ��Ϊ'-'

>>> parser = argparse.ArgumentParser(prog='PROG', prefix_chars='-+')
>>> parser.add_argument('+f')
>>> parser.add_argument('++bar')
>>> parser.parse_args('+f X ++bar Y'.split())
Namespace(bar='Y', f='X')
fromfile_prefix_chars ��ǰ׺�ַ��������ļ���֮ǰ

>>> with open('args.txt', 'w') as fp:
...    fp.write('-f\nbar')
>>> parser = argparse.ArgumentParser(fromfile_prefix_chars='@')
>>> parser.add_argument('-f')
>>> parser.parse_args(['-f', 'foo', '@args.txt'])
Namespace(f='bar')
����������ʱ�����Խ������ŵ��ļ��ж�ȡ��������parser.parse_args(['-f', 'foo', '@args.txt'])����ʱ����ļ�args.txt��ȡ���൱�� ['-f',  'foo',  '-f',  'bar']��

argument_default ��������ȫ��Ĭ��ֵ�����磬Ҫ��ֹparse_argsʱ�Ĳ���Ĭ����ӣ����ǿ��ԣ�

>>> parser = argparse.ArgumentParser(argument_default=argparse.SUPPRESS)
>>> parser.add_argument('--foo')
>>> parser.add_argument('bar', nargs='?')
>>> parser.parse_args(['--foo', '1', 'BAR'])
Namespace(bar='BAR', foo='1')
>>> parser.parse_args()
Namespace()
��parser.parse_args()ʱ�����Զ�����foo��bar�ˡ�

conflict_handler �������ͻ�Ĳ��ԣ�Ĭ������³�ͻ�ᷢ������

>>> parser = argparse.ArgumentParser(prog='PROG')
>>> parser.add_argument('-f', '--foo', help='old foo help')
>>> parser.add_argument('--foo', help='new foo help')
Traceback (most recent call last):
 ..
ArgumentError: argument --foo: conflicting option string(s): --foo
���ǿ����趨��ͻ������ԣ�

>>> parser = argparse.ArgumentParser(prog='PROG', conflict_handler='resolve')
>>> parser.add_argument('-f', '--foo', help='old foo help')
>>> parser.add_argument('--foo', help='new foo help')
>>> parser.print_help()
usage: PROG [-h] [-f FOO] [--foo FOO]

optional arguments:
 -h, --help  show this help message and exit
 -f FOO      old foo help
 --foo FOO   new foo help
�� add_help ����ΪFalseʱ��help��Ϣ���治����ʾ-h --help��Ϣ��

3.��Ӳ���ѡ��

>>> parser.add_argument('integers', metavar='N', type=int, nargs='+',
...                     help='an integer for the accumulator')
>>> parser.add_argument('--sum', dest='accumulate', action='store_const',
...                     const=sum, default=max,
...                     help='sum the integers (default: find the max)')
add_argument (name or flags...[, action][, nargs][, const][, default][, type][, choices][, required][, help][, metavar][, dest])

name or flags �����������֣���ѡ������λ�ò�����

��ӿ�ѡ������

>>> parser.add_argument('-f', '--foo')
���λ�ò�����

>>> parser.add_argument('bar')
parse_args()����ʱ������'-'����֤��ѡ������ʣ�µļ�Ϊλ�ò�����

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
����ʱû��λ�ò����ͻᱨ���ˡ�

action: Ĭ��Ϊstore

store_const��ֵ�����const�У�

>>> parser = argparse.ArgumentParser()
>>> parser.add_argument('--foo', action='store_const', const=42)
>>> parser.parse_args('--foo'.split())
Namespace(foo=42)
store_true��store_false��ֵ��ΪTrue��False

>>> parser = argparse.ArgumentParser()
>>> parser.add_argument('--foo', action='store_true')
>>> parser.add_argument('--bar', action='store_false')
>>> parser.add_argument('--baz', action='store_false')
>>> parser.parse_args('--foo --bar'.split())
Namespace(bar=False, baz=True, foo=True)
append����Ϊ�б�

>>> parser = argparse.ArgumentParser()
>>> parser.add_argument('--foo', action='append')
>>> parser.parse_args('--foo 1 --foo 2'.split())
Namespace(foo=['1', '2'])
append_const����Ϊ�б������const�ؼ�����������ӣ�

>>> parser = argparse.ArgumentParser()
>>> parser.add_argument('--str', dest='types', action='append_const', const=str)
>>> parser.add_argument('--int', dest='types', action='append_const', const=int)
>>> parser.parse_args('--str --int'.split())
Namespace(types=[<type 'str'>, <type 'int'>])
count��ͳ�Ʋ������ֵĴ���

>>> parser = argparse.ArgumentParser()
>>> parser.add_argument('--verbose', '-v', action='count')
>>> parser.parse_args('-vvv'.split())
Namespace(verbose=3)
help��help��Ϣ

version���汾

>>> import argparse
>>> parser = argparse.ArgumentParser(prog='PROG')
>>> parser.add_argument('--version', action='version', version='%(prog)s 2.0')
>>> parser.parse_args(['--version'])
PROG 2.0
nrgs�� ����������

ֵ����Ϊ����N(N��)��*(������)��+(һ�������)

>>> parser = argparse.ArgumentParser()
>>> parser.add_argument('--foo', nargs='*')
>>> parser.add_argument('--bar', nargs='*')
>>> parser.add_argument('baz', nargs='*')
>>> parser.parse_args('a b --foo x y --bar 1 2'.split())
Namespace(bar=['1', '2'], baz=['a', 'b'], foo=['x', 'y'])
ֵΪ��ʱ�����ȴ������л�ò�������û�����const��ã�Ȼ���default��ã�

>>> parser = argparse.ArgumentParser()
>>> parser.add_argument('--foo', nargs='?', const='c', default='d')
>>> parser.add_argument('bar', nargs='?', default='d')
>>> parser.parse_args('XX --foo YY'.split())
Namespace(bar='XX', foo='YY')
>>> parser.parse_args('XX --foo'.split())
Namespace(bar='XX', foo='c')
>>> parser.parse_args(''.split())
Namespace(bar='d', foo='d')
�����õ�������������Ϊ�ļ�

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
const ������һ������

default ��Ĭ��ֵ

type ����������

choices ���ɹ�ѡ���ֵ

>>> parser = argparse.ArgumentParser(prog='doors.py')
>>> parser.add_argument('door', type=int, choices=range(1, 4))
>>> print(parser.parse_args(['3']))
Namespace(door=3)
>>> parser.parse_args(['4'])
usage: doors.py [-h] {1,2,3}
doors.py: error: argument door: invalid choice: 4 (choose from 1, 2, 3)
required ���Ƿ��ѡ

desk ������Ϊ������

>>> parser = argparse.ArgumentParser()
>>> parser.add_argument('--foo', dest='bar')
>>> parser.parse_args('--foo XXX'.split())
Namespace(bar='XXX')
4.��������

�����м���д����

����Ŀո�ֿ���

>>> parser = argparse.ArgumentParser(prog='PROG')
>>> parser.add_argument('-x')
>>> parser.add_argument('--foo')
>>> parser.parse_args('-x X'.split())
Namespace(foo=None, x='X')
>>> parser.parse_args('--foo FOO'.split())
Namespace(foo='FOO', x=None)
��ѡ����=�ֿ�

>>> parser.parse_args('--foo=FOO'.split())
Namespace(foo='FOO', x=None)
��ѡ�����д��һ��

>>> parser.parse_args('-xX'.split())
Namespace(foo=None, x='X')
parse_args()�����ķ���ֵΪnamespace��������vars()�ڽ�������Ϊ�ֵ䣺

>>> parser = argparse.ArgumentParser()
>>> parser.add_argument('--foo')
>>> args = parser.parse_args(['--foo', 'BAR'])
>>> vars(args)
{'foo': 'BAR'}