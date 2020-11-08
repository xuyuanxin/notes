'''
http://www.pythoner.com/205.html
'''
 
class Counter([iterable-or-mapping]): # class collections.Counter([iterable-or-mapping])
  '''
  A @Counter is a @dict subclass for counting hashable objects. It is an unordered c-
  ollection where elements are stored as dictionary keys and their counts are  stored 
  as dictionary values. Counts are allowed to be any integer value including zero  or 
  negative counts. The @Counter class is similar to bags or multisets in other langu-
  ages. Elements are counted from an iterable or initialized from another mapping (or 
  counter):
  >>> c = Counter()                           # a new, empty counter
  >>> c = Counter('gallahad')                 # a new counter from an iterable
  >>> c
  Counter({'a': 3, 'l': 2, 'h': 1, 'g': 1, 'd': 1})
  >>> type(c)
  <class 'collections.Counter'>  
  >>> c = Counter({'red': 4, 'blue': 2})      # a new counter from a mapping
  >>> c = Counter(cats=4, dogs=8)             # a new counter from keyword args
  '''
  
  def elements():
    '''
	Return an iterator over elements repeating each as many times as its count. Elem-
	ents are returned in arbitrary order. If an element’s count is less than one,   -
	elements() will ignore it.
    >>> c = Counter(a=4, b=2, c=0, d=-2)
    >>> list(c.elements())
    ['a', 'a', 'a', 'a', 'b', 'b']
	'''
    pass
	
	
	
	
