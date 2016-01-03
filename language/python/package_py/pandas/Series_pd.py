

class Series(data=None, index=None, dtype=None, name=None, copy=False, fastpath=False): # pandas.Series
  '''
  http://pandas.pydata.org/pandas-docs/stable/generated/pandas.Series.html
  
  
  '''

  def get(key, default=None): # Series.get
    '''
	@key : object
    @Returns: value : type of items contained in object

    Get item from object for given key (DataFrame column, Panel slice, etc.). Return-
	s default value if not found
    '''
	pass

  
  def median(axis=None, skipna=None, level=None, numeric_only=None, **kwargs): # Series.median
    '''
    @axis : {index (0)}
    @skipna : boolean, default True
     Exclude NA/null values. If an entire row/column is NA, the result will be NA
    @level : int or level name, default None
     If the axis is a MultiIndex (hierarchical), count along a particular level, col-
	 lapsing into a scalar
    @numeric_only : boolean, default None
     Include only float, int, boolean data. If None, will attempt to use  everything, 
	 then use only numeric data
    @Returns: median : scalar or Series (if level specified) 

    Return the median of the values for the requested axis
    '''	
    pass
  
  
  

--> Series
 http://pandas.pydata.org/pandas-docs/stable/dsintro.html#series
 
 Series is a one-dimensional labeled array capable of holding any data type (integers
 , strings, floating point numbers, Python objects, etc.). The axis labels are colle-
 ctively referred to as the index. The basic method to create a Series is to call:
 >>> s = pd.Series(data, index=index)
 
 -->--> From ndarray
  If data is an ndarray, index must be the same length as data. If no index is passe-
  d, one will be created having values [0, ..., len(data) - 1].
  In [3]: s = pd.Series(np.random.randn(5), index=['a', 'b', 'c', 'd', 'e'])
  In [4]: s
  Out[4]: 
  a   -2.7828
  b    0.4264
  c   -0.6505
  d    1.1465
  e   -0.6631
  dtype: float64

  In [5]: s.index
  Out[5]: Index([u'a', u'b', u'c', u'd', u'e'], dtype='object')
  
 -->--> From dict
  If data is a dict, if index is passed the values in data corresponding to the labe-
  ls in the index will be pulled out. Otherwise, an index will be constructed from t-
  he sorted keys of the dict, if possible.
  In [7]: d = {'a' : 0., 'b' : 1., 'c' : 2.}

  In [8]: pd.Series(d)
  Out[8]: 
  a    0
  b    1
  c    2
  dtype: float64

  In [9]: pd.Series(d, index=['b', 'c', 'd', 'a'])
  Out[9]: 
  b     1
  c     2
  d   NaN
  a     0
  dtype: float64
  
  Note NaN (not a number) is the standard missing data marker used in pandas

 -->--> From scalar value 
   If data is a scalar value, an index must be provided. The value will be repeated -
   to match the length of index

  In [10]: pd.Series(5., index=['a', 'b', 'c', 'd', 'e'])
  Out[10]: 
  a    5
  b    5
  c    5
  d    5
  e    5
  dtype: float64  

--> Series is ndarray-like
 Series acts very similarly to a ndarray, and is a valid argument to most NumPy func-
 tions. However, things like slicing also slice the index.
 In [11]: s[0]
 Out[11]: -2.7827595933769937

 In [12]: s[:3]
 Out[12]: 
 a   -2.7828
 b    0.4264
 c   -0.6505
 dtype: float64

 In [13]: s[s > s.median()]
 Out[13]: 
 b    0.4264
 d    1.1465
 dtype: float64

 In [14]: s[[4, 3, 1]]
 Out[14]: 
 e   -0.6631
 d    1.1465
 b    0.4264
 dtype: float64

 In [15]: np.exp(s)
 Out[15]: 
 a    0.0619
 b    1.5318
 c    0.5218
 d    3.1472
 e    0.5153
 dtype: float64

--> Series is dict-like
 A Series is like a fixed-size dict in that you can get and set values by index label:

 In [16]: s['a']
 Out[16]: -2.7827595933769937

 In [17]: s['e'] = 12.

 In [18]: s
 Out[18]: 
 a    -2.7828
 b     0.4264
 c    -0.6505
 d     1.1465
 e    12.0000
 dtype: float64

 In [19]: 'e' in s
 Out[19]: True

 In [20]: 'f' in s
 Out[20]: False
 If a label is not contained, an exception is raised:

 >>> s['f']
 KeyError: 'f'
 Using the get method, a missing label will return None or specified default:

 In [21]: s.get('f')

 In [22]: s.get('f', np.nan)
 Out[22]: nan 
 
 
 
 
 
 
 
   
  
