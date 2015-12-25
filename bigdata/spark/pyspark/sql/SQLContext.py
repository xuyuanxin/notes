pyspark.sql module
  Module Context
    SQLContext
	
	
	
class pyspark.sql.SQLContext(sparkContext, sqlContext=None):
  '''
  Main entry point for Spark SQL functionality. A SQLContext can be used create     -
  DataFrame, register DataFrame as tables, execute SQL over tables, cache tables, and 
  read parquet files.

  @sparkContext ¨C The SparkContext backing this SQLContext.
  @sqlContext ¨C An optional JVM Scala SQLContext. If set, we do not instantiate a new 
  SQLContext in the JVM, instead we make all calls to this object.
  '''
  

  read
    Returns a DataFrameReader that can be used to read data in as a DataFrame.
    Returns: DataFrameReader
  
  
  
