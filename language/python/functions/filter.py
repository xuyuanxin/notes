
def filter(function, iterable):
  '''
  Construct a list from those elements of @iterable for which @function returns true. 
  @iterable may be either a sequence, a container which supports iteration, or an it-
  erator. If @iterable is a string or a tuple, the result also has that type; otherw-
  ise it is always a list. If @function is None, the identity function is assumed, t-
  hat is, all elements of @iterable that are false are removed.
  
  >>> str = ['a', 'b','c', 'd']
  >>> def fun1(s): return s if s != 'a' else None
  >>> ret = filter(fun1, str)
  >>> print ret  ## ['b', 'c', 'd']
  '''
  pass