'''
http://pandas.pydata.org/pandas-docs/stable/generated/pandas.DataFrame.html?highlight=dataframe   dataframe api
http://pandas.pydata.org/pandas-docs/stable/dsintro.html#dataframe   dataframe tutorial
'''

'''



'''

class DataFrame(data=None, index=None, columns=None, dtype=None, copy=False): # pandas.DataFrame
  '''
  http://pandas.pydata.org/pandas-docs/stable/generated/pandas.DataFrame.html#pandas.DataFrame
    In [37]: d = {'one' : [1., 2., 3., 4.],
    ....:      'two' : [4., 3., 2., 1.]}
    ....: 

    In [38]: pd.DataFrame(d)
    Out[38]: 
       one  two
    0    1    4
    1    2    3
    2    3    2
    3    4    1

    In [39]: pd.DataFrame(d, index=['a', 'b', 'c', 'd'])
    Out[39]: 
       one  two
    a    1    4
    b    2    3
    c    3    2
    d    4    1 
  '''

  shape #DataFrame.shape
    #Return a tuple representing the dimensionality of the DataFrame.

  index
    # 返回索引

  def applymap(func) # pandas.DataFrame.applymap
    '''
	Apply a function to a DataFrame that is intended to operate elementwise, i.e. li-
	ke doing map(func, series) for each series in the DataFrame
	
    @func : function
      Python function, returns a single value from a single value
    @Returns: applied : DataFrame
	'''
    pass

  def as_matrix(columns=None): # DataFrame.as_matrix(columns=None)
    '''
    @columns: list, optional, default:None
	 If None, return all columns, otherwise, returns specified columns.
	@Returns: values : ndarray
     If the caller is heterogeneous and contains booleans or objects, the result wil-
	 l be of dtype=object.
	 
    >>> df = pandas.DataFrame(data)
    >>> df
       pop   state  year
    0  1.5   Ohino  2000
    1  1.7   Ohino  2001
    2  3.6   Ohino  2002
    3  2.4  Nevada  2001
    4  2.9  Nevada  2002
    >>> a=df.as_matrix(['pop','state','year'])
    >>> a
    array([[1.5, 'Ohino', 2000L],
           [1.7, 'Ohino', 2001L],
           [3.6, 'Ohino', 2002L],
           [2.4, 'Nevada', 2001L],
           [2.9, 'Nevada', 2002L]], dtype=object)
    >>> b=df.as_matrix(['pop','state'])
    >>> b
    array([[1.5, 'Ohino'],
           [1.7, 'Ohino'],
           [3.6, 'Ohino'],
           [2.4, 'Nevada'],
           [2.9, 'Nevada']], dtype=object)
	'''
	pass

  def dropna(axis=0, how='any', thresh=None, subset=None, inplace=False):
    '''
    Return object with labels on given axis omitted where alternately any or all of t-
	he data are missing
	
    @axis : {0 or ‘index’, 1 or ‘columns’}, or tuple/list thereof
      Pass tuple or list to drop on multiple axes
    @how : {‘any’, ‘all’}
    @any : if any NA values are present, drop that label
    @all : if all values are NA, drop that label
    @thresh : int, default None
      int value : require that many non-NA values
    @subset : array-like
      Labels along other axis to consider, e.g. if you are dropping rows these  would 
	  be a list of columns to include
    @inplace : boolean, default False
      If True, do operation inplace and return None.
    @Returns:	
      dropped : DataFrame	
	'''
    pass

  def drop_duplicates(*args, **kwargs):
    '''Return DataFrame with duplicate rows removed, optionally only considering certain columns

    Parameters:	
    subset : column label or sequence of labels, optional
    Only consider certain columns for identifying duplicates, by default use all of the columns
    keep : {‘first’, ‘last’, False}, default ‘first’
    first : Drop duplicates except for the first occurrence.
    last : Drop duplicates except for the last occurrence.
    False : Drop all duplicates.
    take_last : deprecated
    inplace : boolean, default False
    Whether to drop duplicates in place or to return a copy
    cols : kwargs only argument of subset [deprecated]
    Returns:	
    deduplicated : DataFrame
    '''
	pass

  def head(n=5):
    #Returns first n rows
    pass

  def info(verbose=None, buf=None, max_cols=None, memory_usage=None, null_counts=None):
    #Concise summary of a DataFrame.
    pass

  def insert(loc, column, value, allow_duplicates=False): # DataFrame.insert
    '''
    @loc : int
     Must have 0 <= loc <= len(columns)
    @column : object
    @value : int, Series, or array-like		
	
    Insert column into DataFrame at specified location.

    If allow_duplicates is False, raises Exception if column is already contained  in 
	the DataFrame.
   '''
   pass
	


--> DataFrame
 http://pandas.pydata.org/pandas-docs/stable/dsintro.html#dataframe
 
 DataFrame is a 2-dimensional labeled data structure with columns of potentially dif-
 ferent types. You can think of it like a spreadsheet or SQL table, or a dict of    -
 Series objects. It is generally the most commonly used pandas object. Like Series, -
 DataFrame accepts many different kinds of input:
 
 Dict of 1D ndarrays, lists, dicts, or Series
 2-D numpy.ndarray
 Structured or record ndarray
 A Series
 Another DataFrame

 Along with the data, you can optionally pass index (row labels) and columns ( column 
 labels) arguments. If you pass an index and / or columns, you are guaranteeing the -
 index and / or columns of the resulting DataFrame. Thus, a dict of Series plus a sp-
 ecific index will discard all data not matching up to the passed index.

 If axis labels are not passed, they will be constructed from the input data based on 
 common sense rules.
 
 -->--> From dict of Series or dicts
  The result index will be the union of the indexes of the various Series. If there -
  are any nested dicts, these will be first converted to Series. If no columns are p-
  assed, the columns will be the sorted list of dict keys.

  In [30]: d = {'one' : pd.Series([1., 2., 3.], index=['a', 'b', 'c']),
     ....:      'two' : pd.Series([1., 2., 3., 4.], index=['a', 'b', 'c', 'd'])}
     ....: 

  In [31]: df = pd.DataFrame(d)

  In [32]: df
  Out[32]: 
     one  two
  a    1    1
  b    2    2
  c    3    3
  d  NaN    4

  In [33]: pd.DataFrame(d, index=['d', 'b', 'a'])
  Out[33]: 
     one  two
  d  NaN    4
  b    2    2
  a    1    1

  In [34]: pd.DataFrame(d, index=['d', 'b', 'a'], columns=['two', 'three'])
  Out[34]: 
     two three
  d    4   NaN
  b    2   NaN
  a    1   NaN
  The row and column labels can be accessed respectively by accessing the index and -
  columns attributes:

  Note When a particular set of columns is passed along with a dict of data, the pas-
  sed columns override the keys in the dict.
  
  In [35]: df.index
  Out[35]: Index([u'a', u'b', u'c', u'd'], dtype='object')

  In [36]: df.columns
  Out[36]: Index([u'one', u'two'], dtype='object')

 -->--> From dict of ndarrays / lists
  The ndarrays must all be the same length. If an index is passed, it must clearly a-
  lso be the same length as the arrays. If no index is passed, the result will be   -
  range(n), where n is the array length.

  In [37]: d = {'one' : [1., 2., 3., 4.],
     ....:      'two' : [4., 3., 2., 1.]}
     ....: 

  In [38]: pd.DataFrame(d)
  Out[38]: 
     one  two
  0    1    4
  1    2    3
  2    3    2
  3    4    1

  In [39]: pd.DataFrame(d, index=['a', 'b', 'c', 'd'])
  Out[39]: 
     one  two
  a    1    4
  b    2    3
  c    3    2
  
 -->--> From structured or record array
  This case is handled identically to a dict of arrays.
  In [40]: data = np.zeros((2,), dtype=[('A', 'i4'),('B', 'f4'),('C', 'a10')])
  In [41]: data[:] = [(1,2.,'Hello'), (2,3.,"World")]

  In [42]: pd.DataFrame(data)
  Out[42]: 
     A  B      C
  0  1  2  Hello
  1  2  3  World

  In [43]: pd.DataFrame(data, index=['first', 'second'])
  Out[43]: 
          A  B      C
  first   1  2  Hello
  second  2  3  World

  In [44]: pd.DataFrame(data, columns=['C', 'A', 'B'])
  Out[44]: 
         C  A  B
  0  Hello  1  2
  1  World  2  3
  
 -->--> From a list of dicts
  In [45]: data2 = [{'a': 1, 'b': 2}, {'a': 5, 'b': 10, 'c': 20}]

  In [46]: pd.DataFrame(data2)
  Out[46]: 
     a   b   c
  0  1   2 NaN
  1  5  10  20

  In [47]: pd.DataFrame(data2, index=['first', 'second'])
  Out[47]: 
          a   b   c
  first   1   2 NaN
  second  5  10  20

  In [48]: pd.DataFrame(data2, columns=['a', 'b'])
  Out[48]: 
     a   b
  0  1   2
  1  5  10
  
--> Column selection, addition, deletion
 In [32]: df
 Out[32]: 
    one  two
 a    1    1
 b    2    2
 c    3    3
 d  NaN    4  
 
 You can treat a DataFrame semantically like a dict of like-indexed Series objects. -
 Getting, setting, and deleting columns works with the same syntax as the analogous -
 dict operations:
 
 In [54]: df['one']
 Out[54]: 
 a     1
 b     2
 c     3
 d   NaN
 Name: one, dtype: float64

 In [55]: df['three'] = df['one'] * df['two']
 In [56]: df['flag'] = df['one'] > 2

 In [57]: df
 Out[57]: 
    one  two  three   flag
 a    1    1      1  False
 b    2    2      4  False
 c    3    3      9   True
 d  NaN    4    NaN  False

 Columns can be deleted or popped like with a dict:
 In [58]: del df['two']
 In [59]: three = df.pop('three')
 In [60]: df
 Out[60]: 
    one   flag
 a    1  False
 b    2  False
 c    3   True
 d  NaN  False
 
 When inserting a scalar value, it will naturally be propagated to fill the column:
 In [61]: df['foo'] = 'bar'
 In [62]: df
 Out[62]: 
    one   flag  foo
 a    1  False  bar
 b    2  False  bar
 c    3   True  bar
 d  NaN  False  bar
 
 When inserting a Series that does not have the same index as the DataFrame, it  will 
 be conformed to the DataFrame’s index:
 In [63]: df['one_trunc'] = df['one'][:2]
 In [64]: df
 Out[64]: 
    one   flag  foo  one_trunc
 a    1  False  bar          1
 b    2  False  bar          2
 c    3   True  bar        NaN
 d  NaN  False  bar        NaN

 You can insert raw ndarrays but their length must match the length of the          -
 DataFrame’s index. By default, columns get inserted at the end. The insert  function 
 is available to insert at a particular location in the columns:
 In [65]: df.insert(1, 'bar', df['one'])
 In [66]: df
 Out[66]: 
    one  bar   flag  foo  one_trunc
 a    1    1  False  bar          1
 b    2    2  False  bar          2
 c    3    3   True  bar        NaN
 d  NaN  NaN  False  bar        NaN

 
 
 
 
 
 
 
 
