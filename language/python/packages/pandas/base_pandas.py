# http://my.oschina.net/lionets/blog/277847
import pandas as pd
import numpy as np

'''
pandas�ǻ���Numpy�����ĺ��и��߼����ݽṹ�͹��ߵ����ݷ�����

Ŀ¼[-]
  Series
  DataFrame
  ��������
    �������� 
    �޸�����
    ��������
    ɾ��ָ�����ϵ���
    ��������Ƭ
    ������������ݶ���
    ����Ӧ�ú�ӳ��
    ���������
    ͳ�Ʒ���
    Э���������ϵ��
    ���� Index ���ת��
  ����ȱʧ����
    is(not)null
    dropna
    fillna
  inplace ����
  ��λ�����

pandas�ǻ���Numpy�����ĺ��и��߼����ݽṹ�͹��ߵ����ݷ�����. ������Numpy�ĺ�����     |
ndarray, pandasҲ��Χ����Series��DataFrame�����������ݽṹչ����. Series��DataFrame��|
���Ӧ��һά�����кͶ�ά�ı�ṹ. pandas Լ���׳ɵĵ��뷽������:                     |
>>> from pandas import Series,DataFrame
>>> import pandas as pd

----> Series
  Series���Կ���һ�������������ֵ�. ���������һά���ݶ�������������Series����:
  >>> s = Series([1,2,3.0,'abc'])
  >>> s
  0      1
  1      2
  2      3
  3    abc
  dtype: object                                                                      |

  ��Ȼdtype:object���԰������ֻ�����������, ���ܸо���Ӱ�����ܵ�����, ��û��Ǳ��ֵ� |
  ����dtype. Series�������������Ҫ������:index��values, �ֱ�Ϊ�������������С���Ϊ��|
  ������������һ���б����� index ��ֵ�Ǵ� 0 �����������������������һ�����ֵ�� |
  ��ֵ�Խṹ���ͻ����� index-value ��Ӧ�� Series�������ڳ�ʼ����ʱ���Թؼ��ֲ�����ʽ |
  ָ��һ�� index ����                                                              |
  >>> s = Series(data=[1,3,5,7],index = ['a','b','x','y'])
  >>> s
  a    1
  b    3
  x    5
  y    7
  dtype: int64
  >>> s.index
  Index(['a', 'b', 'x', 'y'], dtype='object')
  >>> s.values
  array([1, 3, 5, 7], dtype=int64)
                                                                                     |
  Series �����Ԫ�ػ��ϸ����ո����� index ����������ζ�ţ���� data �������м�ֵ�Ե� |
  ����ôֻ�� index �к��еļ��ᱻʹ�ã��Լ���� data ��ȱ����Ӧ�ļ�����ʹ���� NaN ֵ |
  �������Ҳ�ᱻ��ӡ�ע�� Series �� index �� values ��Ԫ��֮����Ȼ���ڶ�Ӧ��ϵ������|
  ���ֵ��ӳ�䲻ͬ��index �� values ʵ����Ϊ��������� ndarray ���飬��� Series ����|
  ��������ȫok��Series ����ʹ�ü�ֵ�Ե����ݽṹ���ĺô����ڣ�Series ������������� |
  ʱ��index ���Զ����롣���⣬Series ��������� index ������һ�� name ���ԣ�         |
  >>> s.name = 'a_series'
  >>> s.index.name = 'the_index'
  >>> s
  the_index
  a            1
  b            3
  x            5
  y            7
  Name: a_series, dtype: int64

----> DataFrame                                                                      |
  DataFrame ��һ������͵����ݽṹ��������һ��������У������� index����ÿ�п����ǲ� |
  ͬ��ֵ���ͣ����� ndarray ֻ����һ�� dtype���������Ͽ��԰� DataFrame �����ǹ���ͬһ |
  �� index �� Series �ļ��ϡ�DataFrame �Ĺ��췽���� Series ���ƣ�ֻ��������ͬʱ���ܶ�|
  ��һά����Դ��ÿһ�������Ϊ������һ�У�                                           |
  >>> data = {'state':['Ohino','Ohino','Ohino','Nevada','Nevada'],
        'year':[2000,2001,2002,2001,2002],
        'pop':[1.5,1.7,3.6,2.4,2.9]}
  >>> df = DataFrame(data)
  >>> df
     pop   state  year
  0  1.5   Ohino  2000
  1  1.7   Ohino  2001
  2  3.6   Ohino  2002
  3  2.4  Nevada  2001
  4  2.9  Nevada  2002

  [5 rows x 3 columns]                                                               |
  ��Ȼ���� data �������Ǹ��ֵ䣬���ֵ�ļ����ǳ䵱 DataFrame �� index �Ľ�ɫ������   |
  Series �� ��name�� ���ԡ��������ɵ� index ���� ��01234������������ DataFrame ����������|
  Ϊ��
  DataFrame(data=None,index=None,coloumns=None) # columns �� ��name����
  
  >>> df = DataFrame(data,index=['one','two','three','four','five'],
               columns=['year','state','pop','debt'])
  >>> df
         year   state  pop  debt
  one    2000   Ohino  1.5  NaN
  two    2001   Ohino  1.7  NaN
  three  2002   Ohino  3.6  NaN
  four   2001  Nevada  2.4  NaN
  five   2002  Nevada  2.9  NaN

  [5 rows x 4 columns]
  ͬ��ȱʧֵ�� NaN ���ϡ���һ�� index��columns �� ���������ͣ�
  >>> df.index
  Index(['one', 'two', 'three', 'four', 'five'], dtype='object')
  >>> df.columns
  Index(['year', 'state', 'pop', 'debt'], dtype='object')
  >>> type(df['debt'])
  <class 'pandas.core.series.Series'>
  DataFrame �����к������еĲ���������ƽ��ģ�������һ�ж��� Series�� 

---->��������                                                                        |
  ��������                                                                           |
   ����ĳ��ֵ�������е������������� Python �ڽ��� list.index(value) ����������ͨ���� |
   ��������ʵ�֡�������������һ�� Series ��Ѱ�ҵ� ��c����
   >>> ser = Series(list('abcdefg'))
   >>> ser[ser='c']
   2   c
   dtype: object
   Series �л���һ�� ser.idxmax() �� ser.idxmin() ���������Է������������С��ֵ�� |
   ����ֵ������ .argmin() �� .argmax() ��������λ�á���Ȼ�����෽��Ҳ�ǿ���ͨ��������|
   �� ser[ser=ser.max()] �����ʵ�ֵġ� 
  �޸�����
   ����� index ����ʱ���ɱ�ģ������ν�޸���������ʵ��������һ��ʹ���������������� |
   �飬���̳о����ݡ�
   obj.set_index(keys, drop=True, append=False, inplace=False, verify_integrity=False) 
   ��������һ����������key��������һ�������顣��� key ��ֵ�������������ͣ�Ҳ�����ǵ�|
   ���ߵ�һ������������ĳһ����Ϊ�������������                                      |
   >>> indexed_df = df.set_index(['A', 'B'])
   >>> indexed_df2 = df.set_index(['A', [0, 1, 2, 0, 1, 2]])
   >>> indexed_df3 = df.set_index('column1')

  ��������
   Series �������������ͨ���� .reindex(index=None,**kwargs) ����ʵ�֡�**kwargs �г� |
   �õĲ���������method=None,fill_value=np.NaN��
   ser = Series([4.5,7.2,-5.3,3.6],index=['d','b','a','c'])
   >>> a = ['a','b','c','d','e']
   >>> ser.reindex(a)
   a   -5.3
   b    7.2
   c    3.6
   d    4.5
   e    NaN
   dtype: float64
   >>> ser.reindex(a,fill_value=0)
   a   -5.3
   b    7.2
   c    3.6
   d    4.5
   e    0.0
   dtype: float64
   >>> ser.reindex(a,method='ffill')
   a   -5.3
   b    7.2
   c    3.6
   d    4.5
   e    4.5
   dtype: float64
   >>> ser.reindex(a,fill_value=0,method='ffill')
   a   -5.3
   b    7.2
   c    3.6
   d    4.5
   e    4.5
   dtype: float64                                                                    |
   .reindex() �����᷵��һ���¶����� index �ϸ���ѭ�����Ĳ�����
   method:{'backfill', 'bfill', 'pad', 'ffill', None} 
   ��������ָ����ֵ����䣩��ʽ����û�и���ʱ���Զ��� fill_value ��䣬Ĭ��Ϊ NaN    |
   ��ffill = pad��bfill = back fill���ֱ�ָ��ֵʱ��ǰ�������ȡֵ��

   DataFrame �����������������Ϊ��
   .reindex(index=None,columns=None,**kwargs)��
   ���� Series ����һ����ѡ�� columns ���������ڸ����������÷����������ƣ�ֻ������ֵ |
   ���� method ����ֻ��Ӧ�����У����� 0��

   >>> state = ['Texas','Utha','California']
   >>> df.reindex(columns=state,method='ffill')
       Texas  Utha  California
   a      1   NaN           2
   c      4   NaN           5  
   d      7   NaN           8

   [3 rows x 3 columns]
   >>> df.reindex(index=['a','b','c','d'],columns=state,method='ffill')
      Texas  Utha  California
   a      1   NaN           2
   b      1   NaN           2
   c      4   NaN           5
   d      7   NaN           8

   [4 rows x 3 columns]
   ���� fill_value ��Ȼ����Ч��������С�������Ѿ��뵽�ˣ��ɲ�����ͨ�� df.T.reindex(index,method='**').T �����ķ�ʽ��ʵ�������ϵĲ�ֵ�أ����ǿ��еġ�����Ҫע�⣬ʹ�� reindex(index,method='**') ��ʱ��index �����ǵ����ģ�����ͻ�����һ�� ValueError: Must be monotonic for forward fill�����������е����һ�ε��ã����ʹ�� index=['a','b','d','c'] �Ļ��Ͳ��С� 


ɾ��ָ�����ϵ���

��ɾ�� Series ��Ԫ�ػ� DataFrame ��ĳһ�У��У�����˼��ͨ������� .drop(labels, axis=0) ������


>>> ser
d    4.5
b    7.2
a   -5.3
c    3.6
dtype: float64
>>> df
   Ohio  Texas  California
a     0      1           2
c     3      4           5
d     6      7           8

[3 rows x 3 columns]
>>> ser.drop('c')
d    4.5
b    7.2
a   -5.3
dtype: float64
>>> df.drop('a')
   Ohio  Texas  California
c     3      4           5
d     6      7           8

[2 rows x 3 columns]
>>> df.drop(['Ohio','Texas'],axis=1)
   California
a           2
c           5
d           8

[3 rows x 1 columns]
.drop() ���ص���һ���¶���Ԫ���󲻻ᱻ�ı䡣 


��������Ƭ

���� Numpy��pandas Ҳ֧��ͨ�� obj[::] �ķ�ʽ������������Ƭ���Լ�ͨ��������������й��ˡ�

������Ҫע�⣬��Ϊ pandas ����� index ���������������Ե�ʹ�÷�������Ϊ��Ƭ����ʱ������ĩ�˰����ġ�


>>> foo
a    4.5
b    7.2
c   -5.3
d    3.6
dtype: float64
>>> bar
0    4.5
1    7.2
2   -5.3
3    3.6
dtype: float64
>>> foo[:2]
a    4.5
b    7.2
dtype: float64
>>> bar[:2]
0    4.5
1    7.2
dtype: float64
>>> foo[:'c']
a    4.5
b    7.2
c   -5.3
dtype: float64
���� foo �� bar ֻ�� index ��ͬ����bar �� index ���������С��ɼ���ʹ������������Ƭʱ������� Python �б�� Numpy ��Ĭ��״����ͬ������ 'c' �������ַ�������ʱ������Ͱ���������߽�Ԫ�ء�

����һ���ر�֮������ DataFrame �����������ʽ����Ϊ������������˫����������

������ô��⣺DataFrame ����ı�׼��Ƭ�﷨Ϊ��.ix[::,::]��ix ������Խ���������Ƭ���ֱ�Ϊ�У�axis=0�����У�axis=1���ķ���


>>> df
   Ohio  Texas  California
a     0      1           2
c     3      4           5
d     6      7           8

[3 rows x 3 columns]
>>> df.ix[:2,:2]
   Ohio  Texas
a     0      1
c     3      4

[2 rows x 2 columns]
>>> df.ix['a','Ohio']
0
����ʹ�� ix ��ֱ���е�����������ˣ�

����ʱ��ѡȡ������
��Ƭʱ��ѡȡ������
�⿴�����е㲻���߼��������߽���˵ �������﷨�趨��Դ��ʵ����������������


>>> df['Ohio']
a    0
c    3
d    6
Name: Ohio, dtype: int32
>>> df[:'c']
   Ohio  Texas  California
a     0      1           2
c     3      4           5

[2 rows x 3 columns]
>>> df[:2]
   Ohio  Texas  California
a     0      1           2
c     3      4           5

[2 rows x 3 columns]
����һ����������ǣ�����������һ������ index([2,4,5]) ��������ʹ�� ser[2] ������ʱ�򣬵��׻ᱻ����Ϊ��һ���������ǵ����������أ�

���ǵ�һ������������������� index ���������͵�ʱ����ʹ���������������ᱻ�Զ�����Ϊ���ڱ�ǩ�������������ǻ���λ�õ�������Ҫ�������������壬����ʹ��

.loc[label] �����ϸ���ڱ�ǩ������
.iloc[inte] �����ϸ��������λ�õ�����
.ix[] �������������ϸ�ʽ���������ϰ档

ʹ�ò���������������ע�������еĲ�ͬ�з������з��� : ����ʡ����


>>> df['Texas']>=4
a    False
c     True
d     True
Name: Texas, dtype: bool
>>> df[df['Texas']>=4]
   Ohio  Texas  California
c     3      4           5
d     6      7           8

[2 rows x 3 columns]
>>> df.ix[:,df.ix['c']>=4]
   Texas  California
a      1           2
c      4           5
d      7           8

[3 rows x 2 columns]


������������ݶ���

pandas ����Ҫ��һ�������ǣ������ԶԲ�ͬ�����Ķ�������������㡣�ڽ��������ʱ�����������ȡ�����ԵĲ������Զ������ݶ����ڲ��ص��������������ֵ��Ĭ��Ϊ NaN��


>>> foo = Series({'a':1,'b':2})
>>> foo
a    1
b    2
dtype: int64
>>> bar = Series({'b':3,'d':4})
>>> bar
b    3
d    4
dtype: int64
>>> foo + bar
a   NaN
b     5
d   NaN
dtype: float64
DataFrame �Ķ��������ͬʱ�������к����ϡ�

����ϣ�����������г��� NA ֵʱ������ʹ��ǰ�� reindex ���ᵽ�� fill_value ����������Ϊ�˴����������������Ҫʹ�ö���ķ����������ǲ�������df1.add(df2,fill_value=0)�����������������У�sub(), div(), mul()��

Series �� DataFrame ֮������������漰�㲥����ʱ�Ȳ����� 


����Ӧ�ú�ӳ��

Numpy �� ufuncs��Ԫ�ؼ����鷽����Ҳ�����ڲ��� pandas ����

��ϣ��������Ӧ�õ� DataFrame �����ĳһ�л���ʱ������ʹ�� .apply(func, axis=0, args=(), **kwds) ������


f = lambda x:x.max()-x.min()
>>> df
   Ohio  Texas  California
a     0      1           2
c     3      4           5
d     6      7           8

[3 rows x 3 columns]
>>> df.apply(f)
Ohio          6
Texas         6
California    6
dtype: int64
>>> df.apply(f,axis=1)
a    2
c    2
d    2
dtype: int64


���������

Series �� sort_index(ascending=True) �������Զ� index �������������ascending �������ڿ����������Ĭ��Ϊ����

��Ҫ��ֵ�� Series �������򣬵�ʹ�� .order(na_last=True, ascending=True, kind='mergesort') �������κ�ȱʧֵĬ�϶��ᱻ�ŵ� Series ��ĩβ��

�� DataFrame �ϣ�.sort_index(axis=0, by=None, ascending=True) ��������һ�������ѡ�������һ�� by ������by ���������������ĳһ��Щ���н������򣨲��ܶ���ʹ�� by ��������


>>> df.sort_index(by='Ohio')
   Ohio  Texas  California
a     0      1           2
c     3      4           5
d     6      7           8

[3 rows x 3 columns]
>>> df.sort_index(by=['California','Texas'])
   Ohio  Texas  California
a     0      1           2
c     3      4           5
d     6      7           8

[3 rows x 3 columns]
>>> df.sort_index(axis=1)
   California  Ohio  Texas
a           2     0      1
c           5     3      4
d           8     6      7

[3 rows x 3 columns]
������Series.rank(method='average', ascending=True)��������������Ĳ�֮ͬ�����ڣ�����Ѷ���� values �滻�����Σ��� 1 �� n������ʱΨһ������������δ���ƽ���������� method ����������������õģ������ĸ�ֵ��ѡ��average, min, max, first��


>>> ser=Series([3,2,0,3],index=list('abcd'))
>>> ser
a    3
b    2
c    0
d    3
dtype: int64
>>> ser.rank()
a    3.5
b    2.0
c    1.0
d    3.5
dtype: float64
>>> ser.rank(method='min')
a    3
b    2
c    1
d    3
dtype: float64
>>> ser.rank(method='max')
a    4
b    2
c    1
d    4
dtype: float64
>>> ser.rank(method='first')
a    3
b    2
c    1
d    4
dtype: float64
ע���� ser[0]=ser[3] ���ƽ�����ϣ���ͬ method �������ֳ��Ĳ�ͬ���Ρ�

DataFrame �� .rank(axis=0, method='average', ascending=True) �������˸� axis ��������ѡ���л��зֱ������������ʱ����û�����ȫ��Ԫ�ص����������� 


ͳ�Ʒ���

pandas ������һЩͳ�Ʒ��������Ǵ󲿷ֶ�����Լ��ͻ���ͳ�ƣ����ڴ� Series ����ȡ����ֵ����� DataFrame ���л�������ȡһ�� Series��

���� DataFrame.mean(axis=0,skipna=True) �����������ݼ��д��� NA ֵʱ����Щֵ�ᱻ������������������Ƭ���л��У�ȫ�� NA��������������������ͨ�� skipna=False �����ô˹��ܣ�


>>> df
    one  two
a  1.40  NaN
b  7.10 -4.5
c   NaN  NaN
d  0.75 -1.3

[4 rows x 2 columns]
>>> df.mean()
one    3.083333
two   -2.900000
dtype: float64
>>> df.mean(axis=1)
a    1.400
b    1.300
c      NaN
d   -0.275
dtype: float64
>>> df.mean(axis=1,skipna=False)
a      NaN
b    1.300
c      NaN
d   -0.275
dtype: float64
�������õ�ͳ�Ʒ����У� 


########################	*******************************************
count	�� NA ֵ������
describe	��� Series �� DF ���м������ͳ��
min , max	��Сֵ�����ֵ
argmin , argmax	��Сֵ�����ֵ������λ�ã�������
idxmin , idxmax	��Сֵ�����ֵ������ֵ
quantile	������λ����0 �� 1��
sum	���
mean	��ֵ
median	��λ��
mad	���ݾ�ֵ����ƽ���������
var	����
std	��׼��
skew	����ֵ��ƫ�ȣ����׾أ�
kurt	����ֵ�ķ�ȣ��Ľ׾أ�
cumsum	����ֵ���ۼƺ�
cummin , cummax	����ֵ���ۼ����ֵ���ۼ���Сֵ
cumprod	����ֵ���ۼƻ�
diff	����һ�ײ�֣���ʱ�����к����ã�
pct_change	����ٷ����仯


Э���������ϵ��

Series �������������Լ���Э���������ϵ������������Ҫ����������һ�� Series��DataFrame ����������������н����������㣬������һ�� len(columns) ��С�ķ���

.corr(other, method='pearson', min_periods=1) ���ϵ����Ĭ��Ƥ��ɭ
.cov(other, min_periods=None) Э����
min_periods ����Ϊ�����������ޣ����ڴ�ֵ�Ĳ��������㡣 


���� Index ���ת��

DataFrame �� .set_index(keys, drop=True, append=False, verify_integrity=False) �����Ὣ��һ��������ת��Ϊ��������������һ���¶���Ĭ�� drop=True ��ʾת�����ɾ����Щ�Ѿ�������������С���һ�� .reset_index() �������������෴������Ѿ���λ�������ת���������档


>>> df = DataFrame(np.arange(8).reshape(4,2),columns=['a','b'])
>>> df
   a  b
0  0  1
1  2  3
2  4  5
3  6  7

[4 rows x 2 columns]
>>> df2 = df.set_index('a')
>>> df2
   b
a   
0  1
2  3
4  5
6  7

[4 rows x 1 columns]
>>> df2.reset_index()
   a  b
0  0  1
1  2  3
2  4  5
3  6  7

[4 rows x 2 columns]


����ȱʧ����
pandas �� NA ����Ҫ����Ϊ np.nan������ Python �ڽ��� None Ҳ�ᱻ���� NA ����

���� NA �ķ��������֣�dropna , fillna , isnull , notnull �� 


is(not)null

��һ�Է����Զ�����Ԫ�ؼ�Ӧ�ã�Ȼ�󷵻�һ�����������飬һ������ڲ����������� 


dropna

����һ�� Series��dropna ����һ�������ǿ����ݺ�����ֵ�� Series��

�������ڶ� DataFrame �Ĵ���ʽ����Ϊһ�� drop �Ļ�������Ҫ����һ�У��У�������Ľ����ʽ��ǰ�����ƣ�����ͨ��һ������Ĳ�����dropna(axis=0, how='any', thresh=None) ��how ������ѡ��ֵΪ any ���� all��all ������ƬԪ��ȫΪ NA ʱ����������(��)������һ����Ȥ�Ĳ����� thresh���ò���������Ϊ���������������ǣ����� thresh=3������һ���������� 3 ���� NA ֵʱ���䱣����

fillna

fillna(value=None, method=None, axis=0) �е� value �������˻��������⣬������ʹ���ֵ䣬��������ʵ�ֶԲ�ͬ������䲻ͬ��ֵ��method ���÷���ǰ�� .reindex() ������ͬ�����ﲻ��׸���� 


inplace ����
ǰ���и���һֱû���������ƪʾ��д�������ֻ�ͦ��Ҫ�ġ����� Series �� DataFrame ����ķ����У����ǻ�����������޸Ĳ�����һ��������ģ���������һ�� replace=False �Ŀ�ѡ����������ֶ��趨Ϊ True����ôԭ����Ϳ��Ա��滻�� 


��λ�����
��λ�������hierarchical indexing���� pandas ��һ����Ҫ���ܣ�����������һ������ӵ�ж���������𡣻��仰˵��һ��ʹ���˲�λ��������Ķ�ά���飬���Դ洢�ʹ�����ά���ϵ����ݡ�


>>> hdf = DataFrame(np.arange(8).reshape(4,2),index=[['sh','sh','sz','sz'],['600000','600001','000001','000002']],columns=['open','close'])
>>> hdf
           open  close
sh 600000     0      1
   600001     2      3
sz 000001     4      5
   000002     6      7

[4 rows x 2 columns]
>>> hdf.index
MultiIndex(levels=[['sh', 'sz'], ['000001', '000002', '600000', '600001']],
           labels=[[0, 0, 1, 1], [2, 3, 0, 1]])
������ԭ�� sh �� sz �Ѿ��ǵ���ά�������ˣ���ʹ�ò�λ������󣬿��Խ��������ݼ������ڶ�ά��ṹ�С�������������ܺͻ��ڷ���Ĳ�����������͸�ӱ��Ƚ���Ҫ��

�������λ���������Index �� MultiIndex������һ�� names ���ԣ�������������������������Ա�����������ֱ���ԡ��� names ���ԵĲ�������ֱ��ͨ�� obj.index.names=[] ����ʽ��ʵ�֡�


