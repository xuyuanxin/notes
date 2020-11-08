
def randint(low, high=None, size=None): # numpy.random.randint(low, high=None, size=None)
  '''
  @size: int or tuple of ints, optional
   Output shape. If the given shape is, e.g., (m, n, k), then m * n * k samples are -
   drawn. Default is None, in which case a single value is returned.
  @return: int or ndarray of ints
   size-shaped array of random integers from the appropriate distribution, or a sing-
   le such random int if size not provided.
  Return random integers from @low (inclusive) to @high (exclusive). Return random i-
  ntegers from the “discrete uniform” distribution in the “half-open” interval      -
  [low, high). If @high is None (the default), then results are from [0, @low).
  
  >>> np.random.randint(2, size=10)
  array([1, 0, 0, 0, 1, 1, 0, 0, 1, 0])
  >>> np.random.randint(1, size=10)
  array([0, 0, 0, 0, 0, 0, 0, 0, 0, 0])
  Generate a 2 x 4 array of ints between 0 and 4, inclusive:
  >>>
  >>> np.random.randint(5, size=(2, 4))
  array([[4, 0, 2, 1],
         [3, 2, 2, 0]])
  '''
  pass

def randn(): # numpy.random.randn(d0, d1, ..., dn)
  '''
  Return a sample (or samples) from the “standard normal” distribution. If  positive, 
  int_like or int-convertible arguments are provided, @randn generates an array of  -
  shape (d0, d1, ..., dn), filled with random floats sampled from a univariate “norm-
  al” (Gaussian) distribution of mean 0 and variance 1 (if any of the di are  floats, 
  they are first converted to integers by truncation). A single float randomly sampl-
  ed from the distribution is returned if no argument is provided.
  
  >>> np.random.randn()
  2.1923875335537315 #random
  Two-by-four array of samples from N(3, 6.25):

  >>> 2.5 * np.random.randn(2, 4) + 3
  array([[-4.49401501,  4.00950034, -1.81814867,  7.29718677],  #random
         [ 0.39924804,  4.68456316,  4.99394529,  4.84057254]]) #random
  '''
  pass
  
def permutation(x): # numpy.random.permutation
  '''
  @x : int or array_like
   If x is an integer, randomly permute np.arange(x). If x is an array, make a copy -
   and shuffle the elements randomly.
  @Returns:	out : ndarray
   Permuted sequence or array range.
  Randomly permute a sequence, or return a permuted range.If x is a multi-dimensional 
  array, it is only shuffled along its first index.
  
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