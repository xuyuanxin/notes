http://docs.scipy.org/doc/scipy/reference/generated/scipy.sparse.csr_matrix.html#scipy.sparse.csr_matrix




class csr_matrix(arg1, shape=None, dtype=None, copy=False): # scipy.sparse.csr_matrix
  '''
  Compressed Sparse Row matrix
  
  This can be instantiated in several ways:
  csr_matrix(D)
  with a dense matrix or rank-2 ndarray D
  csr_matrix(S)
  with another sparse matrix S (equivalent to S.tocsr())
  csr_matrix((M, N), [dtype])
  to construct an empty matrix with shape (M, N) dtype is optional, defaulting to dtype=’d’.
  csr_matrix((data, (row_ind, col_ind)), [shape=(M, N)])
  where data, row_ind and col_ind satisfy the relationship a[row_ind[k], col_ind[k]] = data[k].
  csr_matrix((data, indices, indptr), [shape=(M, N)])
  is the standard CSR representation where the column indices for row i are stored in indices[indptr[i]:indptr[i+1]] and their corresponding values are stored in data[indptr[i]:indptr[i+1]]. If the shape parameter is not supplied, the matrix dimensions are inferred from the index arrays.
  
  '''
  
  def sum(axis=None):
    '''
	Sum the matrix over the given axis. If the axis is None, sum over both rows and -
	columns, returning a scalar.
	
    >>> X.toarray()
    array([[0, 1, 1, 1, 0, 0, 1, 0, 1],
           [0, 1, 0, 1, 0, 2, 1, 0, 1],
           [1, 0, 0, 0, 1, 0, 1, 1, 0],
           [0, 1, 1, 1, 0, 0, 1, 0, 1]], dtype=int64)
    >>> type(X)
    <class 'scipy.sparse.csr.csr_matrix'>
    >>> aa = X.sum(axis=0)
    >>> aa
    matrix([[1, 3, 2, 3, 1, 2, 4, 1, 3]], dtype=int64)
    >>> type(aa)
    <class 'numpy.matrixlib.defmatrix.matrix'>
    >>> print(aa)
    [[1 3 2 3 1 2 4 1 3]]
	'''
