
# class frozenset([iterable])
class set([iterable]):
  '''
  Return a new set or frozenset object whose elements are taken from iterable. The e-
  lements of a set must be hashable. To represent sets of sets, the inner sets must -
  be frozenset objects. If iterable is not specified, a new empty set is returned.
  
  Instances of set and frozenset provide the following operations:

  len(s)
    Return the cardinality of set s.

  x in s
    Test x for membership in s.

  x not in s
    Test x for non-membership in s.  
  '''

  def add(elem):
    # Add element elem to the set.
    pass

  def difference(other, ...):
    '''
    set - other - ...
    Return a new set with elements in the set that are not in the others. 
    '''
    pass

  def intersection(other, ...):
    '''
	set & other & ...
    Return a new set with elements common to the set and all others.
	
    >>> a
    set([1, 2])
    >>> b
    set([1, 3])
    >>> c=a.intersection(b)
    >>> c
    set([1])	
    '''
    pass
	
  def update(other, ...):
    '''
	set |= other | ...
    Update the set, adding elements from all others.
	>>> a
    set([1, 2])
    >>> b
    set([1, 3])
    >>> a.update(b)
    >>> a
    set([1, 2, 3])
    >>>
    '''
    pass
	
  def union():
    '''
    set | other | ...
    Return a new set with elements from the set and all others.

    Changed in version 2.6: Accepts multiple input iterables.
	
    >>> a = set([1,2])
    >>> b = set([1,3])
    >>> c = a | b
    >>> d = a.union(b)
    >>> a
    set([1, 2])
    >>> b
    set([1, 3])
    >>> c
    set([1, 2, 3])
    >>> d
    set([1, 2, 3])
    '''
    pass


# http://blog.csdn.net/business122/article/details/7541486

'''                                                                                  |
python��set��������������, ��һ�������ظ�Ԫ�ؼ�, �������ܰ�����ϵ���Ժ������ظ�Ԫ��|
. ���϶���֧��union(����), intersection(��), difference(��)��sysmmetric difference(|
�ԳƲ)����ѧ����. sets ֧�� x in set, len(set),�� for x in set����Ϊһ������ļ���|
��sets����¼Ԫ��λ�û��߲���㡣��ˣ�sets��֧�� indexing, slicing, �����������У�   |
sequence-like���Ĳ�����                                                              |

set ������һ���������ͣ�������{}�����壬����pyton -v �汾 >2.7

set�����ݸ�ʽ��
s1={"abc","def"}      #{} �Լ�����  
>>> print s1  
set(['abc', 'def'])    
>>> s2=set("abcdef")  #set ������string���г�ʼ��  
>>> print s2  
set(['a', 'c', 'b', 'e', 'd', 'f'])  
>>> s3=set(["abc",123,"def"])  #set ������list���г�ʼ��  
>>> print s3  
set([123, 'abc', 'def'])   

>>> x = set('spam')
>>> y = set(['h','a','m'])
>>> x, y
(set(['a', 'p', 's', 'm']), set(['a', 'h', 'm']))

����ЩСӦ�á�

>>> x & y # ����
set(['a', 'm'])

>>> x | y # ����
set(['a', 'p', 's', 'h', 'm'])

>>> x - y # �
set(['p', 's'])

�ǵ���ǰ������������ôȥ�������б����ظ�Ԫ�أ���hash�����Ҳ�У�ֻ�����о��������ϲ��Ǻܸߣ���set������Ǻܲ���ģ�ʾ�����£�

>>> a = [11,22,33,44,11,22]
>>> b = set(a)
>>> b
set([33, 11, 44, 22])
>>> c = [i for i in b]
>>> c
[33, 11, 44, 22]

�ܿ�ѣ����оͿ��Ը㶨��

1.8������ 
 
�������ڰ���һ������Ķ���Ҫ�������ϣ���ʹ��set()�����������������ṩһϵ�е��

 

s = set([3,5,9,10])      #����һ����ֵ����

t = set("Hello")         #����һ��Ψһ�ַ��ļ���

 

���б��Ԫ�鲻ͬ������������ģ�Ҳ�޷�ͨ�����ֽ������������⣬�����е�Ԫ�ز����ظ������磬������ǰ�������t���ϵ�ֵ��������ǣ�

 

>>> t

set(['H', 'e', 'l', 'o'])

 

ע��ֻ������һ��'l'��

����֧��һϵ�б�׼������������������������ͶԳƲ�����磺

 

a = t | s          # t �� s�Ĳ���

b = t & s          # t �� s�Ľ���

c = t �C s          # ��������t�У�������s�У�

d = t ^ s          # �ԳƲ������t��s�У�������ͬʱ�����ڶ����У�

 

����������

t.add('x')            # ���һ��

s.update([10,37,42])  # ��s����Ӷ���

 

ʹ��remove()����ɾ��һ�

t.remove('H')

 

len(s)
set �ĳ���

x in s
���� x �Ƿ��� s �ĳ�Ա

x not in s
���� x �Ƿ��� s �ĳ�Ա

s.issubset(t)
s <= t
�����Ƿ� s �е�ÿһ��Ԫ�ض��� t ��

s.issuperset(t)
s >= t
�����Ƿ� t �е�ÿһ��Ԫ�ض��� s ��

s.union(t)
s | t
����һ���µ� set ���� s �� t �е�ÿһ��Ԫ��

s.intersection(t)
s & t
����һ���µ� set ���� s �� t �еĹ���Ԫ��

s.difference(t)
s - t
����һ���µ� set ���� s ���е��� t ��û�е�Ԫ��

s.symmetric_difference(t)
s ^ t
����һ���µ� set ���� s �� t �в��ظ���Ԫ��

s.copy()
���� set ��s����һ��ǳ����


��ע�⣺union(), intersection(), difference() �� symmetric_difference() �ķ��������non-operator���������� s.union()�����ģ��汾��������κ� iterable ��Ϊ�������෴�����ǵ�������汾��operator based counterparts��Ҫ����������� sets���������Ա���Ǳ�ڵĴ����磺Ϊ�˸��ɶ���ʹ�� set('abc') & 'cbs' ����� set('abc').intersection('cbs')���� 2.3.1 �汾�����ĸ��ģ���ǰ���в����������� sets��

���⣬Set �� ImmutableSet ���߶�֧�� set �� set ֮��ıȽϡ����� sets ��Ҳֻ�����������������ȵģ�ÿһ�� set �е�Ԫ�ض�����һ���е�Ԫ�أ����߻�Ϊsubset����һ�� set ����һ�� set С��ֻ���ڵ�һ�� set �ǵڶ��� set �� subset ʱ����һ�� subset�����ǲ�����ȣ���һ�� set ����һ�� set ��ֻ���ڵ�һ�� set �ǵڶ��� set �� superset ʱ����һ�� superset�����ǲ�����ȣ���

�� set ����ȱȽϲ������������������ܡ����磺�������� sets �������Ҳ����Ϊ�� set��������µ����㶼�᷵�� False��a<b, a==b, ����a>b����ˣ�sets ���ṩ __cmp__ ������

��Ϊ sets ֻ�����˲��������ܣ�subset ��ϵ����list.sort() ������������� sets ���б�û�ж��塣


�����
   ������

hash(s)
   ���� s �� hash ֵ


����������г��˶��� Set ���ö����� ImmutableSet �����õ����㣺

�������voperator��
�ȼ���
������

s.update(t)
s |= t
���������� set ��t����Ԫ�غ�� set ��s��

s.intersection_update(t)
s &= t
����ֻ�������� set ��t����Ԫ�ص� set ��s��

s.difference_update(t)
s -= t
����ɾ���� set ��t���к��е�Ԫ�غ�� set ��s��

s.symmetric_difference_update(t)
s ^= t
���غ��� set ��t������ set ��s�����ж��������߶��е�Ԫ�ص� set ��s��

s.add(x)

�� set ��s��������Ԫ�� x

s.remove(x)

�� set ��s����ɾ��Ԫ�� x, ��������������� KeyError

s.discard(x)

����� set ��s���д���Ԫ�� x, ��ɾ��

s.pop()

ɾ�����ҷ��� set ��s���е�һ����ȷ����Ԫ��, ���Ϊ�������� KeyError

s.clear()

ɾ�� set ��s���е�����Ԫ��


��ע�⣺��������汾�� update(), intersection_update(), difference_update()��symmetric_difference_update()����������� iterable ��Ϊ�������� 2.3.1 �汾���ĸ��ģ���ǰ���в����������� sets��

����ע�⣺���ģ�黹����һ�� union_update() ���������� update() ������һ���������������������Ϊ�������ݡ�����Ա��Ӧ�ö�ʹ�� update() ��������Ϊ�������Ҳ�����õ� set() �� frozenset() ����֧�֡�
 
''' 

