


class Broadcast(sc=None, value=None, pickle_registry=None, path=None)# pyspark.Broadcast
  '''
  A broadcast variable that gets reused across tasks. A broadcast variable created w-
  ith SparkContext.broadcast(). Access its value through value.
  >>> from pyspark.context import SparkContext
  >>> sc = SparkContext('local', 'test')
  >>> b = sc.broadcast([1, 2, 3, 4, 5])
  >>> b.value
  [1, 2, 3, 4, 5]
  >>> sc.parallelize([0, 0]).flatMap(lambda x: b.value).collect()
  [1, 2, 3, 4, 5, 1, 2, 3, 4, 5]
  >>> b.unpersist()
  >>> large_broadcast = sc.broadcast(range(10000))
  '''

  def dump(value, f):
    pass
	
  def load(path):
    pass
	
  def unpersist(blocking=False):
    #Delete cached copies of this broadcast on the executors.
    pass

  def value:
    #Return the broadcasted value
	pass
	
	
	
