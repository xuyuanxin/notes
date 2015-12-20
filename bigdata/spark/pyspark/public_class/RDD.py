
class RDD: # class pyspark.RDD(jrdd, ctx, jrdd_deserializer=AutoBatchedSerializer(PickleSerializer()))
  '''
  A Resilient Distributed Dataset (RDD), the basic abstraction in Spark. Represents -
  an immutable, partitioned collection of elements that can be operated on in parall-
  el.
  '''

  def aggregate(self, zeroValue, seqOp, combOp):
    ''' pyspark.RDD.aggregate (Python method, in pyspark package)
    http://atlantageek.com/2015/05/30/python-aggregate-rdd/index.html

    Aggregate lets you take an RDD and generate a single value that is of a differen-
    t type than what was stored in the original RDD. It does this with three paramet-
    ers. A @zeroValue (or initial value) in the format of the result. A @seqOp funct-
    ion that given the resulting type and an individual element in the RDD will merg-
    e the RDD element into the resulting object. The @combOb merges two resulting ob-
    jects together.

    Consider an example. We want to take a list of records about people and then we -
    want to sum up their ages and count them. So for this example the type in the RDD 
    will be a Dictionary in the format of {name: NAME, age:AGE, gender:GENDER}. The -
    result type will be a tuple that looks like so (Sum of Ages, Count). Lets first -
    generate a peopleRDD with 5 people
    > people = []
    > people.append({'name':'Bob', 'age':45,'gender':'M'})
    > people.append({'name':'Gloria', 'age':43,'gender':'F'})
    > people.append({'name':'Albert', 'age':28,'gender':'M'})
    > people.append({'name':'Laura', 'age':33,'gender':'F'})
    > people.append({'name':'Simone', 'age':18,'gender':'T'})
    > peopleRdd=sc.parallelize(people)
    > len(peopleRdd.collect())
    Now we need to create the seqOp. This takes an object of the rdd type and merge -
    it into a record of the result type. Or another way to say this is add the age to  
    the first element of the resulting tuple and add 1 for the second element of  the 
    tuple
    > seqOp = (lambda x,y: (x[0] + y['age'],x[1] + 1))
    Now we write an operation to merge two resulting tuple.
    > combOp = (lambda x,y: (x[0] + y[0], x[1] + y[1]))
    Run the function
    > peopleRdd.aggregate((0,0), seqOp, combOp)
    (167, 5)
    And here is the result. So why is this convoluted? The combOp seems unecessary b-
    ut in the map reduce world of spark you need that seperate operation. Realize th-
    at these functions are going to be parallelized. peopleRDD is partitioned up. And 
    dependending on its source and method of converting the data to an RDD each row -
    could be on its own partition.

    So lets backup and define a few things

    partition - A partition is how the RDD is split up. If our RDD was 100,000 recor-
    ds we could have as many as 100,000 partitions or only 1 partition depending on -
    how we created the RDD.

    task - A small job that operates on a single partition. A single task can run  on 
    only one machine at a time and can operate on only one partiton at a time.

    For the aggregate function the seqOp will run once for every record in a partiti-
    on. This will result in a resulting object for each partition. The combOp will be 
    used to merge all the resulting objects together.
    '''

  def cache():
    #Persist this RDD with the default storage level (MEMORY_ONLY_SER).	
    pass

  def distinct(numPartitions=None):
    '''
    Return a new RDD containing the distinct elements in this RDD.
    >>> sorted(sc.parallelize([1, 1, 2, 3]).distinct().collect())
    [1, 2, 3]
  
    1 也支持key-value的形式，但value是list类型时可能有问题  
    '''
    pass

  def foreach(f):
    '''
    Applies a function to all elements of this RDD.
    >>> def f(x): print(x)
    >>> sc.parallelize([1, 2, 3, 4, 5]).foreach(f)  
    '''
    pass  
 
  def filter(f):
    '''
    Return a new RDD containing only the elements that satisfy a predicate.
    >>> rdd = sc.parallelize([1, 2, 3, 4, 5])
    >>> rdd.filter(lambda x: x % 2 == 0).collect()
    [2, 4]
    '''
    pass
  
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
    pass

  def randomSplit(weights, seed=None): 
    '''
    @weights: weights for splits, will be normalized if they don’t sum to 1
    @seed: random seed
    @Returns: split RDDs in a list
	
    Randomly splits this RDD with the provided weights.

    >>> rdd = sc.parallelize(range(500), 1)
    >>> rdd1, rdd2 = rdd.randomSplit([2, 3], 17)
    >>> len(rdd1.collect() + rdd2.collect())
    500
    >>> 150 < rdd1.count() < 250
    True
    >>> 250 < rdd2.count() < 350
    True
    '''
	pass

  def reduceByKey(func, numPartitions=None):
    '''
    Merge the values for each key using an associative reduce function. This will al-
    so perform the merging locally on each mapper before sending results to a reduce-
    r, similarly to a “combiner” in MapReduce. Output will be hash-partitioned with -
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
	
	如果key只有一个，这个key不会触发回调函数
    注意会有归并后的两个值，再次归并。
    ---------------------------------------------------------------------------------
    '''
    pass

  def union(other): # pyspark.RDD.union (Python method, in pyspark package)
    '''
    Return the union of this RDD and another one.
  
    >>> rdd = sc.parallelize([1, 1, 2, 3])
    >>> rdd.union(rdd).collect()
    [1, 1, 2, 3, 1, 1, 2, 3]
    '''
    pass

  def unpersist():
    #Mark the RDD as non-persistent, and remove all blocks for it from memory and disk.
    pass
	
  def zip(other)
    '''
    Zips this RDD with another one, returning key-value pairs with the first  element 
	in each RDD second element in each RDD, etc. Assumes that the two RDDs have the -
	same number of partitions and the same number of elements in each partition (e.g. 
	one was made through a map on the other).

    >>> x = sc.parallelize(range(0,5))
    >>> y = sc.parallelize(range(1000, 1005))
    >>> x.zip(y).collect()
    [(0, 1000), (1, 1001), (2, 1002), (3, 1003), (4, 1004)]
    '''
    pass
	
	
	

