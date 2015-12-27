'''
http://pandas.pydata.org/pandas-docs/stable/generated/pandas.DataFrame.html?highlight=dataframe   dataframe api
http://pandas.pydata.org/pandas-docs/stable/dsintro.html#dataframe   dataframe tutorial
'''

'''



'''

class DataFrame(data=None, index=None, columns=None, dtype=None, copy=False): # pandas.DataFrame
  '''
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

