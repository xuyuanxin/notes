
http://docs.scipy.org/doc/numpy/reference/arrays.ndarray.html    The N-dimensional array (ndarray)
http://docs.scipy.org/doc/numpy/reference/generated/numpy.ndarray.html#numpy.ndarray   numpy.ndarray


class ndarray: # class numpy.ndarray
  '''
  An array object represents a multidimensional, homogeneous array of fixed-size ite-
  ms. An associated data-type object describes the format of each element in the arr-
  ay (its byte-order, how many bytes it occupies in memory, whether it is an integer, 
  a floating point number, or something else, etc.)

  Arrays should be constructed using @array, @zeros or @empty. The parameters given -
  here refer to a low-level method (ndarray(...)) for instantiating an array.
  
  @shape : tuple of ints
    Shape of created array.
  @dtype : data-type, optional
    Any object that can be interpreted as a numpy data type.
  @buffer : object exposing buffer interface, optional
    Used to fill the array with data.
  @offset : int, optional
    Offset of array data in buffer.
  @strides : tuple of ints, optional
    Strides of data in memory.
  @order : {‘C’, ‘F’}, optional
    Row-major (C-style) or column-major (Fortran-style) order.
  '''

  ndim
    Number of array dimensions.
	
	>>> x = np.array([1, 2, 3])
	>>> x.ndim
	1
	>>> y = np.zeros((2, 3, 4))
	>>> y.ndim
	3
	
  def sum(axis=None, dtype=None, out=None, keepdims=False):
    '''
	Return the sum of the array elements over the given axis.
    Refer to numpy.sum for full documentation.
	
    >>> x=np.ones((2,3,4))
    >>> x
    array([[[ 1.,  1.,  1.,  1.],
            [ 1.,  1.,  1.,  1.],
            [ 1.,  1.,  1.,  1.]],

           [[ 1.,  1.,  1.,  1.],
            [ 1.,  1.,  1.,  1.],
            [ 1.,  1.,  1.,  1.]]])
    >>> y=x.sum(axis=1)
    >>> y
    array([[ 3.,  3.,  3.,  3.],
           [ 3.,  3.,  3.,  3.]])
    >>> y=x.sum(axis=2)
    >>> y
    array([[ 4.,  4.,  4.],
           [ 4.,  4.,  4.]])
    >>> y=x.sum(axis=0)
    >>> y
    array([[ 2.,  2.,  2.,  2.],
           [ 2.,  2.,  2.,  2.],
           [ 2.,  2.,  2.,  2.]])
	'''
	pass
	

--> The N-dimensional array (ndarray)

 -->--> Array creation
  http://docs.scipy.org/doc/numpy/user/basics.creation.html#arrays-creation
  http://docs.scipy.org/doc/numpy/reference/routines.array-creation.html#routines-array-creation
  
  There are 5 general mechanisms for creating arrays:
  1 Conversion from other Python structures (e.g., lists, tuples)
  2 Intrinsic numpy array array creation objects (e.g., arange, ones, zeros, etc.)
  3 Reading arrays from disk, either from standard or custom formats
  4 Creating arrays from raw bytes through the use of strings or buffers
  5 Use of special library functions (e.g., random)
  
  
  
  
  
  
  
  
  
