Introduction
A Foolish Consistency is the Hobgoblin of Little Minds
Code lay-out
 Indentation
 Tabs or Spaces?
 Maximum Line Length
 Blank Lines
 Source File Encoding
 Imports
String Quotes
Whitespace in Expressions and Statements
 Pet Peeves
 Other Recommendations
Comments
 Block Comments
 Inline Comments
 Documentation Strings
Version Bookkeeping

--> Naming Conventions
 -->--> Overriding Principle
 -->--> Descriptive: Naming Styles
 -->--> Prescriptive: Naming Conventions
  -->-->-->Names to Avoid
  -->-->-->Package and Module Names
  -->-->--> Class Names
   Class names should normally use the CapWords convention.
  -->-->-->Exception Names
  -->-->-->Global Variable Names
  -->--> Function Names
   Function names should be lowercase, with words separated by underscores as necess-
   ary to improve readability. mixedCase is allowed only in contexts where that's al-
   ready the prevailing style (e.g. threading.py), to retain backwards compatibility.
  -->-->-->Function and method arguments
  -->-->-->Method Names and Instance Variables
  -->-->-->Constants
  -->-->-->Designing for inheritance
 -->--> Public and internal interfaces

Programming Recommendations
References
Copyright





http://blog.sae.sina.com.cn/archives/4781
PEP8 Python ����淶����
07/17. 2014
������ʼPython֮·�ˣ�����ҵ��ʱ�䣬��ȡ������ѧϰPython��������Բ������������ǹ�������˵�ǹ��ߣ�������������ѭһ�ױ���淶��ʮ�ֱ�Ҫ�ġ����Խ��������Ҹ���PEP 8������һ�ݣ��Ժ��մ˱����ˣ�����������¡�

PEP8 Python ����淶

һ �������
1 ������4���ո���������༭����������ɴ˹��ܣ�����ʹ��Tap�������ܻ��ʹ��Tap�Ϳո�
2 ÿ����󳤶�79�����п���ʹ�÷�б�ܣ����ʹ��Բ���š����е�Ҫ�ڲ������ĺ���ûس���
3 ���top-level��������֮������У����еķ�������֮���һ�У��������߼��޹ض���֮���һ�У������ط�������Ҫ�ٿ��С�

�� �ĵ�����
1 ģ�����ݵ�˳��ģ��˵����docstring��import��globals&constants���������塣����import���֣��ְ���׼���������Լ���д˳�������ŷţ�֮���һ�С�
2 ��Ҫ��һ��import�ж���⣬����import os, sys���Ƽ���
3 �������from XX import XX���ÿ⣬����ʡ�ԡ�module.�������ǿ��ܳ���������ͻ����ʱ��Ҫ����import XX��

�� �ո��ʹ��
����ԭ�򣬱��ⲻ��Ҫ�Ŀո�
1 ����������ǰ��Ҫ�ӿո�
2 ���š�ð�š��ֺ�ǰ��Ҫ�ӿո�
3 ������������ǰ��Ҫ�ӿո���Func(1)��
4 ���е�������ǰ��Ҫ�ӿո���list[2]��
5 ���������Ҹ���һ���ո񣬲�ҪΪ�˶������ӿո�
6 ����Ĭ�ϲ���ʹ�õĸ�ֵ������ʡ�Կո�
7 ��Ҫ��������д��ͬһ�У�����ʹ�á�����������
8 if/for/while����У���ʹִ�����ֻ��һ�䣬Ҳ��������һ�С�

�� ע��
����ԭ�򣬴����ע�Ͳ���û��ע�͡����Ե�һ�δ��뷢���仯ʱ����һ���¾���Ҫ�޸�ע�ͣ�
ע�ͱ���ʹ��Ӣ�ģ�����������ľ��ӣ�����ĸ��д�����Ҫ�н���������������������ո񣬿�ʼ��һ�䡣����Ƕ������ʡ�Խ�������
1 ��ע�ͣ���һ�δ���ǰ���ӵ�ע�͡��ڡ�#�����һ�ո񡣶���֮����ֻ�С�#�����м�������磺

# Description : Module config.
# 
# Input : None
#
# Output : None
2 ��ע�ͣ���һ�������ע�͡����磺x = x + 1 # Increment x
�������ַ�ʽ������ʹ�á�
3 ������ν��ע�͡�

�� �ĵ�����
1 Ϊ���еĹ���ģ�顢�������ࡢ����дdocstrings���ǹ��е�û�б�Ҫ�����ǿ���дע�ͣ���def����һ�У���
2 ���docstringҪ���У��ο���������,���PEP 257

"""Return a foobang

Optional plotz says to frobnicate the bizbaz first.

"""
�� �����淶
����ԭ���±������밴�������������У����п�ı��뾡�����ַ��
1 ��������ʹ��Сд��ĸ��l������д��ĸ��O�������׻�������ĸ��
2 ģ������������С��ʹ��ȫ��Сд�ķ�ʽ������ʹ���»��ߡ�
3 ������������С��ʹ��ȫ��Сд�ķ�ʽ��������ʹ���»��ߡ�
4 �������ʹ��CapWords�ķ�ʽ��ģ���ڲ�ʹ�õ������_CapWords�ķ�ʽ��
5 �쳣����ʹ��CapWords+Error��׺�ķ�ʽ��
6 ȫ�ֱ�������ֻ��ģ������Ч������C�����е�static��ʵ�ַ��������֣�һ��__all__����;����ǰ׺һ���»��ߡ�
7 ��������ʹ��ȫ��Сд�ķ�ʽ������ʹ���»��ߡ�
8 ��������ʹ��ȫ����д�ķ�ʽ������ʹ���»��ߡ�
9 ������ԣ������ͱ���������ʹ��ȫ��Сд�ķ�ʽ������ʹ���»��ߡ�
9 ���������3��������public��non-public��subclass API�����������C++�е�public��private��protected��non-public����ǰ��ǰ׺һ���»��ߡ�
11 �����������ؼ������ֳ�ͻ����׺һ�»��ߣ�������Ҫʹ�����Ե�������ʽ��
12 Ϊ��������������������ͻ�������һЩ����ǰ��ǰ׺�����»��ߡ����磺��Foo������__a,����ʱ��ֻ��ͨ��Foo._Foo__a���������塣�������Ҳ��Foo���Ǿ�����Ϊ���ˡ�
13 ��ķ�����һ������������self������̬������һ������������cls��

�� ���뽨��
1 �����п��ǵ�����pythonʵ�ֵ�Ч�ʵ����⣬�����������+����CPython��Python����Ч�ʺܸߣ�����Jython��ȴ�ǳ��ͣ�����Ӧ�ò���.join()�ķ�ʽ��
2 ������ʹ�á�is����is not��ȡ����==��������if x is not None Ҫ����if x��
3 ʹ�û�������쳣��ÿ��ģ���������Լ����쳣�࣬���쳣��̳���Exception��
4 �쳣�в�Ҫʹ����¶��except��except��������exceptions��
5 �쳣��try�Ĵ��뾡�����١����磺

try:
value = collection[key]
except KeyError:
return key_not_found(key)
else:
return handle_value(value)
Ҫ����

try:
# Too broad!
return handle_value(collection[key])
except KeyError:
# Will also catch KeyError raised by handle_value()
return key_not_found(key)
6 ʹ��startswith() and endswith()������Ƭ��������ǰ׺���׺�ļ�顣����

Yes: if foo.startswith(��bar��):����
No: if foo[:3] == ��bar��:
7 ʹ��isinstance()�Ƚ϶�������͡�����
Yes: if isinstance(obj, int): ����
No: if type(obj) is type(1):
8 �ж����пջ򲻿գ������¹���
Yes: if not seq:
if seq:
����
No: if len(seq)
if not len(seq)
9 �ַ�����Ҫ�Կո���β��
10 �����������ж�ʹ�� if boolvalue�ķ�ʽ��