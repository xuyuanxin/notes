
def permutation(x): # numpy.random.permutation
  '''
  Randomly permute a sequence, or return a permuted range.If x is a multi-dimensional 
  array, it is only shuffled along its first index.
  x : int or array_like
  If x is an integer, randomly permute np.arange(x). If x is an array, make a copy and shuffle the elements randomly.
  Returns:	
  out : ndarray
  Permuted sequence or array range.
  Examples

  >>>
  >>> np.random.permutation(10)
  array([1, 7, 4, 3, 0, 9, 2, 5, 8, 6])
  >>>
  >>> np.random.permutation([1, 4, 9, 12, 15])
  array([15,  1,  9,  4, 12])
  >>>
  >>> arr = np.arange(9).reshape((3, 3))
  >>> np.random.permutation(arr)
  array([[6, 7, 8],
         [0, 1, 2],
         [3, 4, 5]])  
  '''
  pass