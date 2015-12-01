'''
http://pandas.pydata.org/pandas-docs/stable/generated/pandas.DataFrame.html?highlight=dataframe
http://pandas.pydata.org/pandas-docs/stable/dsintro.html#dataframe 
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
  



