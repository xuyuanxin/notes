

class SparkContext: # pyspark.SparkContext
  '''
  Main entry point for Spark functionality. A SparkContext represents the  connection 
  to a Spark cluster, and can be used to create RDD and broadcast variables on that -
  cluster.
  '''

  def parallelize(c, numSlices=None):
    '''
    Distribute a local Python collection to form an RDD. Using xrange is  recommended 
	if the input represents a range for performance.

    >>> sc.parallelize([0, 2, 3, 4, 6], 5).glom().collect()
    [[0], [2], [3], [4], [6]]
    >>> sc.parallelize(xrange(0, 6, 2), 5).glom().collect()
    [[], [0], [], [2], [4]]
    '''
    pass

  def union(rdds): # pyspark.SparkContext.union (Python method, in pyspark package)
    '''
    Build the union of a list of RDDs. This supports unions() of RDDs with  different 
    serialized formats, although this forces them to be reserialized using the defau-
	lt serializer:
  
    >>> path = os.path.join(tempdir, "union-text.txt")
    >>> with open(path, "w") as testFile:
    ...    _ = testFile.write("Hello")
    >>> textFile = sc.textFile(path)
    >>> textFile.collect()
    [u'Hello']
    >>> parallelized = sc.parallelize(["World!"])
    >>> sorted(sc.union([textFile, parallelized]).collect())
    [u'Hello', 'World!']
    '''
    pass
	
	
  
