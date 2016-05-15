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

  shape # DataFrame.shape
    # Return a tuple representing the dimensionality of the DataFrame.

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
	
    @axis : {0 or "index", 1 or "columns"}, or tuple/list thereof
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
	                                                                                 |
	对于一个 Series，dropna 返回一个仅含非空数据和索引值的 Series。问题在于对 DataFrame 
	的处理方式，因为一旦 drop 的话，至少要丢掉一行（列）。这里的解决方式与前面类似，还
	是通过一个额外的参数：dropna(axis=0, how='any', thresh=None) ，how 参数可选的值为 
	any 或者 all。all 仅在切片元素全为 NA 时才抛弃该行(列)。另外一个有趣的参数是 thresh，
	该参数的类型为整数，它的作用是，比如 thresh=3，会在一行中至少有 3 个非 NA 值时将其保留。
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
    # Returns first n rows
    pass

  def info(verbose=None, buf=None, max_cols=None, memory_usage=None, null_counts=None):
    '''
	buf : writable buffer, defaults to sys.stdout
    Concise summary of a DataFrame.
    '''
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
	
  def reindex():
    '''
    Create a dataframe with some fictional data.

    >>> index = ['Firefox', 'Chrome', 'Safari', 'IE10', 'Konqueror']
    >>> df = pd.DataFrame({
    ...      'http_status': [200,200,404,404,301],
    ...      'response_time': [0.04, 0.02, 0.07, 0.08, 1.0]},
    ...       index=index)
    >>> df
                http_status  response_time
    Firefox            200           0.04
    Chrome             200           0.02
    Safari             404           0.07
    IE10               404           0.08
    Konqueror          301           1.00
    Create a new index and reindex the dataframe. By default values in the new index that do not have corresponding records in the dataframe are assigned NaN.

    >>> new_index= ['Safari', 'Iceweasel', 'Comodo Dragon', 'IE10',
    ...             'Chrome']
    >>> df.reindex(new_index)
                   http_status  response_time
    Safari                 404           0.07
    Iceweasel              NaN            NaN
    Comodo Dragon          NaN            NaN
    IE10                   404           0.08
    Chrome                 200           0.02
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
 You can treat a DataFrame semantically like a dict of like-indexed Series objects. -
 Getting, setting, and deleting columns works with the same syntax as the analogous -
 dict operations:
 
 In [32]: df
 Out[32]: 
    one  two
 a    1    1
 b    2    2
 c    3    3
 d  NaN    4  
 
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

--> Console display
 http://pandas.pydata.org/pandas-docs/stable/dsintro.html#console-display
 
 Very large DataFrames will be truncated to display them in the console. You can als-
 o get a summary using info(). 
 
 In [101]: baseball = pd.read_csv('data/baseball.csv')

 In [102]: print(baseball)
        id     player  year  stint  ...   hbp   sh   sf  gidp
 0   88641  womacto01  2006      2  ...   0.0  3.0  0.0   0.0
 1   88643  schilcu01  2006      1  ...   0.0  0.0  0.0   0.0
 ..    ...        ...   ...    ...  ...   ...  ...  ...   ...
 98  89533   aloumo01  2007      1  ...   2.0  0.0  3.0  13.0
 99  89534  alomasa02  2007      1  ...   0.0  0.0  0.0   0.0

 [100 rows x 23 columns]
 
 In [103]: baseball.info()
 <class 'pandas.core.frame.DataFrame'>
 RangeIndex: 100 entries, 0 to 99
 Data columns (total 23 columns):
 id        100 non-null int64
 player    100 non-null object
 year      100 non-null int64
 stint     100 non-null int64
 team      100 non-null object
 lg        100 non-null object
 g         100 non-null int64
 ab        100 non-null int64
 r         100 non-null int64
 h         100 non-null int64
 X2b       100 non-null int64
 X3b       100 non-null int64
 hr        100 non-null int64
 rbi       100 non-null float64
 sb        100 non-null float64
 cs        100 non-null float64
 bb        100 non-null int64
 so        100 non-null float64
 ibb       100 non-null float64
 hbp       100 non-null float64
 sh        100 non-null float64
 sf        100 non-null float64
 gidp      100 non-null float64
 dtypes: float64(9), int64(11), object(3)
 memory usage: 18.0+ KB
 
 However, using to_string will return a string representation of the DataFrame in ta-
 bular form, though it won’t always fit the console width:
 In [104]: print(baseball.iloc[-20:, :12].to_string())
        id     player  year  stint team  lg    g   ab   r    h  X2b  X3b
 80  89474  finlest01  2007      1  COL  NL   43   94   9   17    3    0
 81  89480  embreal01  2007      1  OAK  AL    4    0   0    0    0    0
 82  89481  edmonji01  2007      1  SLN  NL  117  365  39   92   15    2
 83  89482  easleda01  2007      1  NYN  NL   76  193  24   54    6    0
 84  89489  delgaca01  2007      1  NYN  NL  139  538  71  139   30    0
 85  89493  cormirh01  2007      1  CIN  NL    6    0   0    0    0    0
 86  89494  coninje01  2007      2  NYN  NL   21   41   2    8    2    0
 87  89495  coninje01  2007      1  CIN  NL   80  215  23   57   11    1
 88  89497  clemero02  2007      1  NYA  AL    2    2   0    1    0    0
 89  89498  claytro01  2007      2  BOS  AL    8    6   1    0    0    0
 90  89499  claytro01  2007      1  TOR  AL   69  189  23   48   14    0
 91  89501  cirilje01  2007      2  ARI  NL   28   40   6    8    4    0
 92  89502  cirilje01  2007      1  MIN  AL   50  153  18   40    9    2
 93  89521  bondsba01  2007      1  SFN  NL  126  340  75   94   14    0
 94  89523  biggicr01  2007      1  HOU  NL  141  517  68  130   31    3
 95  89525  benitar01  2007      2  FLO  NL   34    0   0    0    0    0
 96  89526  benitar01  2007      1  SFN  NL   19    0   0    0    0    0
 97  89530  ausmubr01  2007      1  HOU  NL  117  349  38   82   16    3
 98  89533   aloumo01  2007      1  NYN  NL   87  328  51  112   19    1
 99  89534  alomasa02  2007      1  NYN  NL    8   22   1    3    1    0
 
 New since 0.10.0, wide DataFrames will now be printed across multiple rows by default:

 In [105]: pd.DataFrame(np.random.randn(3, 12))
 Out[105]: 
          0         1         2         3         4         5         6   \
 0  1.225021 -0.528620  0.448676  0.619107 -1.199110 -0.949097  2.169523   
 1 -1.753617  0.992384 -0.505601 -0.599848  0.133585  0.008836 -1.767710   
 2 -0.461585 -1.321106  1.745476  1.445100  0.991037 -0.860733 -0.870661   

          7         8         9         10        11  
 0  0.302230  0.919516  0.657436  0.262574 -0.804798  
 1  0.700112 -0.020773 -0.302481  0.347869  0.179123  
 2 -0.117845 -0.046266  2.095649 -0.524324 -0.610555  
 
 You can change how much to print on a single row by setting the display.width option:

 In [106]: pd.set_option('display.width', 40) # default is 80

 In [107]: pd.DataFrame(np.random.randn(3, 12))
 Out[107]: 
          0         1         2   \
 0 -1.280951  1.472585 -1.001914   
 1  0.130529 -1.603771 -0.128830   
 2 -1.084566 -0.515272  1.367586   
 
          3         4         5   \
 0  1.044770 -0.050668 -0.013289   
 1 -1.869301 -0.232977 -0.139801   
 2  0.963500  0.224105 -0.020051   
 
          6         7         8   \
 0 -0.291893  2.029038 -1.117195   
 1 -1.083341 -0.357234 -0.818199   
 2  0.524663  0.351081 -1.574209   
 
          9         10        11  
 0  1.598577 -0.397325  0.151653  
 1 -0.886885  1.238885 -1.639274  
 2 -0.486856 -0.545888 -0.927076  
 
 You can adjust the max width of the individual columns by setting display.max_colwidth

 In [108]: datafile={'filename': ['filename_01','filename_02'],
    .....:           'path': ["media/user_name/storage/folder_01/filename_01",
    .....:                    "media/user_name/storage/folder_02/filename_02"]}
    .....: 

 In [109]: pd.set_option('display.max_colwidth',30)
 
 In [110]: pd.DataFrame(datafile)
 Out[110]: 
       filename  \
 0  filename_01   
 1  filename_02   

                             path  
 0  media/user_name/storage/fo...  
 1  media/user_name/storage/fo...  

 In [111]: pd.set_option('display.max_colwidth',100)

 In [112]: pd.DataFrame(datafile)
 Out[112]: 
       filename  \
 0  filename_01   
 1  filename_02   

                                             path  
 0  media/user_name/storage/folder_01/filename_01  
 1  media/user_name/storage/folder_02/filename_02  

 You can also disable this feature via the expand_frame_repr option. This will  print 
 the table in one block.
 
 
 
 
 
