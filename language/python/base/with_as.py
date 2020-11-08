http://zhoutall.com/archives/325


���Python�е�with��as���﷨
Posted in python - 22 ����, 2013 - 2 Comments
ʹ�����Եĺ����ԣ���������Щ�������ԡ���������֪��˭˵��

�þò�ѧϰpython���﷨�ˣ��ϴ�ȥ���ԣ������Թ��ĵ���python�е�with-as statement��Ҳ��context manager����ͦ����Ȥ�ģ�������ѧϰ��һ�����ջ��ķ��ڴ˷���

��˵��һ���������⣬�ļ��򿪣�

1
2
3
4
5
6
7
try:
    f = open('xxx')
    do something
except:
    do something
finally:
    f.close()
��ʵ�Ҹ��˲�ֹһ�������Ͽ�������ôд���ˣ�����Ǵ�ġ�
������ȷ�����£�

1
2
3
4
5
6
7
8
9
10
11
try:
    f = open('xxx')
except:
    print 'fail to open'
    exit(-1)
try:
    do something
except:
    do something
finally:
    f.close()
���鷳����ô������ȷ�ķ���������ôд��
����ΪʲôҪдfinally������Ϊ��ֹ�����׳��쳣����ܹر��ļ���������Ҫ�ر��ļ���һ��ǰ������ļ��Ѿ����ˡ�
�ڵ�һ�δ�������У�����쳣������f=open(��xxx��)��ʱ�򣬱����ļ������ڣ�����Ϳ���֪��ִ��f.close()��û������ġ�������Ľ���������ǵڶ��δ��롣

�����Թ���ת����ʼ����with�﷨��

�������Ǵ������������̸��try-finally���﷨�ṹ��

1
2
3
4
5
set things up
try:
    do something
finally:
    tear things down
�ⶫ���Ǹ������ṹ�������ļ��򿪣�set things up�ͱ�ʾf=open('xxx')��tear things down�ͱ�ʾf.close()���ڱ�������߳�������Դ�������ն���һ���ͷŵ�����Try��finally�ṹ��֤��tear things down��һ����Զ����ִ�У���ʹ����do something�ù���û����ȫִ�С�

������������ֽṹ���������ȿ��Բ�ȡһ����Ϊ���ŵİ취����װ��

1
2
3
4
5
6
7
8
9
10
11
def controlled_execution(callback):
    set things up
    try:
        callback(thing)
    finally:
        tear things down
 
def my_function(thing):
    do something
 
controlled_execution(my_function)
��װ��һ��֧�ִ������õĺð취����������취��dirty���ر��ǵ�do something�����޸�һЩlocal variables��ʱ�򣨱�ɺ������ã��ٲ��˴��������������ϵ��鷳����

��һ���취��ʹ��������������ֻ��Ҫ����һ�����ݣ�������for-in�ṹȥ��������

1
2
3
4
5
6
7
8
9
def controlled_execution():
    set things up
    try:
        yield thing
    finally:
        tear things down
         
for thing in controlled_execution():
    do something with thing
��Ϊthingֻ��һ��������yield���ֻ��Ҫִ��һ�Ρ���Ȼ���Ӵ���ɶ���Ҳ�������ŵĽǶ���˵���ֱ�����͸�ˡ�������ȷ��forѭ��ִֻ��һ�ε��������Ȼʹ����forѭ������������֪�����˿�һ��������������ѭ����ʲô������

���յ�python-dev�ŶӵĽ����������python 2.5�Ժ�������with���ʽ���﷨��

1
2
3
4
5
6
7
8
9
class controlled_execution:
    def __enter__(self):
        set things up
        return thing
    def __exit__(self, type, value, traceback):
        tear things down
         
with controlled_execution() as thing:
        do something
�����pythonʹ����with-as���﷨����pythonִ����һ��ʱ�������__enter__������Ȼ��Ѹú���return��ֵ����as��ָ���ı�����֮��python��ִ������do something�����顣������ڸ����������ʲô�쳣���������뿪ʱִ��__exit__��
���⣬__exit__��������tear things down�������Խ����쳣�ļ�غʹ���ע��󼸸�������Ҫ����һ���쳣��ֻ��Ҫ���ظú���True���ɡ�����������������������е�TypeError�����������쳣�����׳���

1
2
def __exit__(self, type, value, traceback):
    return isinstance(value, TypeError)
��python2.5���Ժ�file�����Ѿ�д����__enter__��__exit__���������ǿ����������ԣ�

1
2
3
4
5
6
7
8
9
10
11
12
>>> f = open("x.txt")
>>> f
<open file 'x.txt', mode 'r' at 0x00AE82F0>
>>> f.__enter__()
<open file 'x.txt', mode 'r' at 0x00AE82F0>
>>> f.read(1)
'X'
>>> f.__exit__(None, None, None)
>>> f.read(1)
Traceback (most recent call last):
    File "<stdin>", line 1, in <module>
ValueError: I/O operation on closed file
֮���������Ҫ���ļ�����֤���ر�����ֻ��Ҫ��ô����

1
2
3
with open("x.txt") as f:
    data = f.read()
    do something with data
����ж������ǿ�����ôд��

1
2
with open("x.txt") as f1, open('xxx.txt') as f2:
    do something with f1,f2
����˵��__exit__�������Խ��в����쳣�Ĵ���������ǲ�����������д����쳣�����������׳�����ʱ�����ǿ�������д��python 2.7�����ϰ汾��֮ǰ�İ汾�ο�ʹ��contextlib.nested����⺯������

1
2
3
4
5
try:
    with open( "a.txt" ) as f :
        do something
except xxxError:
    do something about exception
��֮��with-as���ʽ����ļ���ÿ��дfinally�Ĺ�������Ա��ִ�������������м�������ġ�

��л���²ο����ϣ�
stackoverflow: Catching an exception while using a Python ��with�� statement
Understanding Python��s ��with�� statement
python docs:
http://docs.python.org/2/reference/compound_stmts.html#with
http://docs.python.org/2/reference/datamodel.html#context-managers
http://docs.python.org/2/library/contextlib.html#contextlib.nested