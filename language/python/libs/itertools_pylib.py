Python���ڽ�ģ��itertools�ṩ�˷ǳ����õ����ڲ�����������ĺ�����

���ȣ����ǿ���itertools�ṩ�ļ��������ޡ���������

>>> import itertools
>>> natuals = itertools.count(1)
>>> for n in natuals:
...     print n
...
1
2
3
...
��Ϊcount()�ᴴ��һ�����޵ĵ���������������������ӡ����Ȼ�����У�����ͣ��������ֻ�ܰ�Ctrl+C�˳���

cycle()��Ѵ����һ�����������ظ���ȥ��

>>> import itertools
>>> cs = itertools.cycle('ABC') # ע���ַ���Ҳ�����е�һ��
>>> for c in cs:
...     print c
...
'A'
'B'
'C'
'A'
'B'
'C'
...
ͬ��ͣ��������

repeat()�����һ��Ԫ�������ظ���ȥ����������ṩ�ڶ��������Ϳ����޶��ظ�������

>>> ns = itertools.repeat('A', 10)
>>> for n in ns:
...     print n
...
��ӡ10��'A'
��������ֻ����for����ʱ�Ż����޵ص�����ȥ�����ֻ�Ǵ�����һ�������������������Ȱ����޸�Ԫ�����ɳ�������ʵ��Ҳ���������ڴ��д������޶��Ԫ�ء�

����������Ȼ�������޵�����ȥ������ͨ�����ǻ�ͨ��takewhile()�Ⱥ������������ж�����ȡ��һ�����޵����У�

>>> natuals = itertools.count(1)
>>> ns = itertools.takewhile(lambda x: x <= 10, natuals)
>>> for n in ns:
...     print n
...
��ӡ��1��10
itertools�ṩ�ļ������������������������ã�

chain()

chain()���԰�һ������������������γ�һ������ĵ�������

for c in chain('ABC', 'XYZ'):
    print c
# ����Ч����'A' 'B' 'C' 'X' 'Y' 'Z'
groupby()

groupby()�ѵ����������ڵ��ظ�Ԫ������������һ��

>>> for key, group in itertools.groupby('AAABBBCCAAA'):
...     print key, list(group) # Ϊʲô����Ҫ��list()�����أ�
...
A ['A', 'A', 'A']
B ['B', 'B', 'B']
C ['C', 'C']
A ['A', 'A', 'A']
ʵ������ѡ������ͨ��������ɵģ�ֻҪ�����ں���������Ԫ�ط��ص�ֵ��ȣ�������Ԫ�ؾͱ���Ϊ����һ��ģ�����������ֵ��Ϊ���key���������Ҫ���Դ�Сд���飬�Ϳ�����Ԫ��'A'��'a'��������ͬ��key��

>>> for key, group in itertools.groupby('AaaBBbcCAAa', lambda c: c.upper()):
...     print key, list(group)
...
A ['A', 'a', 'a']
B ['B', 'B', 'b']
C ['c', 'C']
A ['A', 'A', 'a']
imap()

imap()��map()���������ڣ�imap()�����������������У����ң�����������еĳ��Ȳ�һ�£��Զ̵��Ǹ�Ϊ׼��

>>> for x in itertools.imap(lambda x, y: x * y, [10, 20, 30], itertools.count(1)):
...     print x
...
10
40
90
ע��imap()����һ���������󣬶�map()����list���������map()ʱ���Ѿ�������ϣ�

>>> r = map(lambda x: x*x, [1, 2, 3])
>>> r # r�Ѿ����������
[1, 4, 9]
�������imap()ʱ����û�н����κμ��㣺

>>> r = itertools.imap(lambda x: x*x, [1, 2, 3])
>>> r
<itertools.imap object at 0x103d3ff90>
# rֻ��һ����������
������forѭ����r���е������Ż���ÿ��ѭ�������м������һ��Ԫ�أ�

>>> for x in r:
...     print x
...
1
4
9
��˵��imap()ʵ���ˡ����Լ��㡱��Ҳ��������Ҫ��ý����ʱ��ż��㡣����imap()�����ܹ�ʵ�ֶ��Լ���ĺ����Ϳ��Դ����������У�

>>> r = itertools.imap(lambda x: x*x, itertools.count(1))
>>> for n in itertools.takewhile(lambda x: x<100, r):
...     print n
...
�����ʲô?
�����imap()����map()ȥ�����������л���ʲô�����

>>> r = map(lambda x: x*x, itertools.count(1))
�����ʲô?
ifilter()

���ö�˵�ˣ�ifilter()����filter()�Ķ���ʵ�֡�

С��

itertoolsģ���ṩ��ȫ���Ǵ���������ܵĺ��������ǵķ���ֵ����list�����ǵ�������ֻ����forѭ��������ʱ����������㡣