pyspark.sql module
  Module Context
    DataFrameReader
	
	
class pyspark.sql.DataFrameReader(sqlContext):
  '''
  Interface used to load a DataFrame from external storage systems(e.g. file systems, 
  key-value stores, etc). Use SQLContext.read() to access this.
  '''
  
  def json(path, schema=None):
    '''
	@path ¨C string, path to the JSON dataset.
    @schema ¨C an optional StructType for the input schema.

	Loads a JSON file (one object per line) and returns the result as a             -
	:class`DataFrame`. If the @schema parameter is not specified, this function  goes 
	through the input once to determine the input schema.
	
	>>> df = sqlContext.read.json('python/test_support/sql/people.json')
    >>> df.dtypes
    [('age', 'bigint'), ('name', 'string')]
	'''