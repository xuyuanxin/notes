

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
	
	
def textFile(name, minPartitions=None, use_unicode=True): #  pyspark.SparkContext
  '''
  Read a text file from HDFS, a local file system (available on all nodes), or any  -
  Hadoop-supported file system URI, and return it as an RDD of Strings.
  If use_unicode is False, the strings will be kept as str (encoding as utf-8), which 
  is faster and smaller than unicode. (Added in Spark 1.2)

  >>> path = os.path.join(tempdir, "sample-text.txt")
  >>> with open(path, "w") as testFile:
  ...    _ = testFile.write("Hello world!")
  >>> textFile = sc.textFile(path)
  >>> textFile.collect()
  [u'Hello world!'] 
  
  textFile的参数是一个path,这个path可以是：
  1. 一个文件路径，这时候只装载指定的文件
  2. 一个目录路径，这时候只装载指定目录下面的所有文件（不包括子目录下面的文件）
  3. 通过通配符的形式加载多个文件或者加载多个目录下面的所有文件
  第三点是一个使用小技巧，现在假设我的数据结构为先按天分区，再按小时分区的，在hdfs上 |
  的目录结构类似于：

  /user/hdfs/input/dt=20130728/hr=00/                                                |
  /user/hdfs/input/dt=20130728/hr=01/
  ...
  /user/hdfs/input/dt=20130728/hr=23/
  具体的数据都在hr等于某个时间的目录下面，现在我们要分析20130728这一天的数据，我们就 |
  必须把这个目录下面的所有hr=*的子目录下面的数据全部装载进RDD，于是我们可以这样写：  |
  sc.textFile("hdfs://n1:8020/user/hdfs/input/dt=20130728/hr=*/")
  注意到hr=*,是一个模糊匹配的方式。
  '''
  pass
	
	
  
