pyspark.sql module
  Module Context
    DataFrame
	
	
class pyspark.sql.DataFrame(jdf, sql_ctx):
  '''
  A distributed collection of data grouped into named columns.
  '''
  
  
  dtypes
    '''
    Returns all column names and their data types as a list.

    >>> df.dtypes
    [('age', 'int'), ('name', 'string')]
	'''