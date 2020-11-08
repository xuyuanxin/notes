
def sum(a, axis=None, dtype=None, out=None, keepdims=False): # numpy.sum
  '''
  Sum of array elements over a given axis.
  
  >>> np.sum([0.5, 1.5])
  2.0
  >>> np.sum([0.5, 0.7, 0.2, 1.5], dtype=np.int32)
  1
  >>> np.sum([[0, 1], [0, 5]])
  6
  >>> np.sum([[0, 1], [0, 5]], axis=0)
  array([0, 6])
  >>> np.sum([[0, 1], [0, 5]], axis=1)
  array([1, 5])
  '''
  pass
  
  
