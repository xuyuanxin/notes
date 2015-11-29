'''
http://pandas.pydata.org/pandas-docs/stable/generated/pandas.DataFrame.html?highlight=dataframe
http://pandas.pydata.org/pandas-docs/stable/dsintro.html#dataframe 
'''

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

class pandas.DataFrame(data=None, index=None, columns=None, dtype=None, copy=False)