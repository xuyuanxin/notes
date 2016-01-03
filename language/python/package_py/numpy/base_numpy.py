
http://wiki.scipy.org/Tentative_NumPy_Tutorial            Tentative NumPy Tutorial
https://docs.scipy.org/doc/numpy-dev/user/quickstart.html Quickstart tutorial
http://www.tuicool.com/articles/r2yyei                    Quickstart tutorial  chinese edition

--> The Basics
 NumPy's main object is the homogeneous multidimensional array. It is a table of ele-
 ments (usually numbers), all of the same type, indexed by a tuple of positive integ-
 ers. In Numpy dimensions are called axes. The number of axes is rank. For example, -
 the coordinates of a point in 3D space [1, 2, 1] is an array of rank 1, because it -
 has one axis. That axis has a length of 3. In example pictured below, the array  has 
 rank 2 (it is 2-dimensional). The first dimension (axis) has a length of 2, the sec-
 ond dimension has a length of 3.
 [[ 1., 0., 0.],
  [ 0., 1., 2.]]

 Numpy's array class is called @ndarray. It is also known by the alias @array. Note -
 that numpy.array is not the same as the Standard Python Library class array.array, -
 which only handles one-dimensional arrays and offers less functionality. The more i-
 mportant attributes of an ndarray object are:
 ndarray.ndim
    the number of axes (dimensions) of the array. In the Python world, the number  of 
	dimensions is referred to as rank.
 ndarray.shape
    the dimensions of the array. This is a tuple of integers indicating the size of -
	the array in each dimension. For a matrix with n rows and m columns, shape will -
	be (n,m). The length of the shape tuple is therefore the rank, or number of dime-
	nsions, ndim.
 ndarray.size
    the total number of elements of the array. This is equal to the product of the e-
	lements of shape.
 ndarray.dtype
    an object describing the type of the elements in the array. One can create or sp-
	ecify dtype's using standard Python types. Additionally NumPy provides types of -
	its own. numpy.int32, numpy.int16, and numpy.float64 are some examples.
 ndarray.itemsize
    the size in bytes of each element of the array. For example, an array of elements 
	of type float64 has itemsize 8 (=64/8), while one of type complex32 has  itemsize 
	4 (=32/8). It is equivalent to ndarray.dtype.itemsize.
 ndarray.data
    the buffer containing the actual elements of the array. Normally, we won't need -
	to use this attribute because we will access the elements in an array using inde-
	xing facilities.
 ---------------------------------
 >>> from numpy  import *
 >>> a = arange(15).reshape(3, 5)
 >>> a
 array([[ 0,  1,  2,  3,  4],
        [ 5,  6,  7,  8,  9],
        [10, 11, 12, 13, 14]])
 >>> a.shape
 (3, 5)
 >>> a.ndim  # 3行5列是二维的？
 2
 >>> a.dtype.name
 'int32'
 >>> a.itemsize
 4
 >>> a.size
 15
 >>> type(a)
 numpy.ndarray
 >>> b = array([6, 7, 8])
 >>> b
 array([6, 7, 8])
 >>> b.ndim
 1
 >>> type(b)
 numpy.ndarray
 ---------------------------------

--> Array Creation
 you can create an array from a regular Python list or tuple using the array function
 . The type of the resulting array is deduced from the type of the elements in the s-
 equences.
 >>> from numpy import *
 >>> a = array( [2,3,4] )
 >>> a
 array([2, 3, 4])
 >>> b = array( [ (1.5,2,3), (4,5,6) ] )
 >>> b
 array([[ 1.5,  2. ,  3. ],
        [ 4. ,  5. ,  6. ]])
 >>> c = array( [ [1,2], [3,4] ], dtype=complex )
 >>> c
 array([[ 1.+0.j,  2.+0.j],
        [ 3.+0.j,  4.+0.j]])
 The function @zeros creates an array full of zeros, the function @ones creates an a-
 rray full of ones, and the function @empty creates an array whose initial content i-
 s random and depends on the state of the memory. By default, the dtype of the creat-
 ed array is float64.
 >>> zeros( (3,4) )
 array([[0.,  0.,  0.,  0.],
       [0.,  0.,  0.,  0.],
       [0.,  0.,  0.,  0.]])
 >>> ones( (2,3,4), dtype=int16 )                # dtype can also be specified
 array([[[ 1, 1, 1, 1],
         [ 1, 1, 1, 1],
         [ 1, 1, 1, 1]],
        [[ 1, 1, 1, 1],
         [ 1, 1, 1, 1],
         [ 1, 1, 1, 1]]], dtype=int16)
 >>> empty( (2,3) )
 array([[  3.73603959e-262,   6.02658058e-154,   6.55490914e-260],
       [  5.30498948e-313,   3.14673309e-307,   1.00000000e+000]])
 To create sequences of numbers, NumPy provides a function analogous to range that r-
 eturns arrays instead of lists
 >>> arange( 10, 30, 5 )
 array([10, 15, 20, 25])
 >>> arange( 0, 2, 0.3 )            # it accepts float arguments
 array([ 0. ,  0.3,  0.6,  0.9,  1.2,  1.5,  1.8])
 >>> linspace( 0, 2, 9 )                 # 9 numbers from 0 to 2
 array([ 0.  ,  0.25,  0.5 ,  0.75,  1.  ,  1.25,  1.5 ,  1.75,  2.  ])
 >>> x = linspace( 0, 2*pi, 100 )   # useful to evaluate function at lots of points
 >>> f = sin(x) 

 -->--> Printing Arrays
  One-dimensional arrays are then printed as rows, bidimensionals as matrices and tr-
  idimensionals as lists of matrices.
  >>> a = arange(6)                         # 1d array
  >>> print a
  [0 1 2 3 4 5]
  >>>
  >>> b = arange(12).reshape(4,3)           # 2d array
  >>> print b
  [[ 0  1  2]
   [ 3  4  5]
   [ 6  7  8]
   [ 9 10 11]]
  >>>
  >>> c = arange(24).reshape(2,3,4)         # 3d array
  >>> print c
  [[[ 0  1  2  3]
    [ 4  5  6  7]
    [ 8  9 10 11]]

   [[12 13 14 15]
    [16 17 18 19]
    [20 21 22 23]]]

--> Indexing
 -->--> Single element indexing
  Single element indexing for a 1-D array is what one expects. It work exactly like -
  that for other standard Python sequences. It is 0-based, and accepts negative indi-
  ces for indexing from the end of the array.
  >>> x = np.arange(10)
  >>> x
  array([0, 1, 2, 3, 4, 5, 6, 7, 8, 9])
  >>> x[2]
  2
  >>> x[-2]
  8
  
  Unlike lists and tuples, numpy arrays support multidimensional indexing for multid-
  imensional arrays. That means that it is not necessary to separate each dimension’s 
  index into its own set of square brackets.
  >>> x.shape = (2,5)   # now x is 2-dimensional
  >>> x
  array([[0, 1, 2, 3, 4],
         [5, 6, 7, 8, 9]])
  >>> x[1,3]
  8
  >>> x[1,-1]
  9

  Note that if one indexes a multidimensional array with fewer indices than dimensio-
  ns, one gets a subdimensional array. For example:
  >>>
  >>> x[0]
  array([0, 1, 2, 3, 4])







