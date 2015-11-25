
def join():
    '''
    Return an RDD containing all pairs of elements with matching keys in @self and  -
	@other. Each pair of elements will be returned as a (k, (v1, v2)) tuple, where  -
	(k, v1) is in @self and (k, v2) is in @other. Performs a hash join across the cl-
	uster.

    >>> x = sc.parallelize([("a", 1), ("b", 4)])
    >>> y = sc.parallelize([("a", 2), ("a", 3)])
    >>> sorted(x.join(y).collect())
    [('a', (1, 2)), ('a', (1, 3))]
    '''

def reduceByKey(func, numPartitions=None):
    '''
	Merge the values for each key using an associative reduce function. This will al-
	so perform the merging locally on each mapper before sending results to a reduce-
	r, similarly to a ¡°combiner¡± in MapReduce. Output will be hash-partitioned with -
	numPartitions partitions, or the default parallelism level if numPartitions is n-
	ot specified.

    >>> from operator import add
    >>> rdd = sc.parallelize([("a", 1), ("b", 1), ("a", 1)])
    >>> sorted(rdd.reduceByKey(add).collect())
    [('a', 2), ('b', 1)]
	
    ---------------------------------------------------------------------------------
	def reduceByKey_api(val1,val2):
        print("val1:%s"%val1)
        print("val2:%s"%val2)
	    return [val1,val2]
	data = [(1,'a1'),(1,'a2'),(1,'a3'),(1,'a4')]
	rdd = sc.parallelize(data)
	result = rdd.reduceByKey(reduceByKey_api)
	
	val1:a1
	val2:a2
	
	val1:['a1','a2']
	val2:a3
	
	val1:[['a1','a2'],a3] 
	val2:a4
	
	result:
	[[['a1','a2'],'a3'],'a4']
    ---------------------------------------------------------------------------------
	'''

def union(other): # pyspark.RDD.union (Python method, in pyspark package)
  '''
  Return the union of this RDD and another one.
  
  >>> rdd = sc.parallelize([1, 1, 2, 3])
  >>> rdd.union(rdd).collect()
  [1, 1, 2, 3, 1, 1, 2, 3]
  '''
  
