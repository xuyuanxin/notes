'''
operator
 The @operator module exports a set of efficient functions corresponding to the intr-
 insic operators of Python. For example, operator.add(x, y) is equivalent to the exp-
 ression x+y.
'''

def __getitem__(a, b):
  # Return the value of a at index b.
  pass


def itemgetter(item)
def itemgetter(*items): # operator.itemgetter
  '''
  Return a callable object that fetches @item from its operand using the operand¡¯s  -
  __getitem__() method. If multiple @items are specified, returns a tuple of lookup -
  values. For example:
  After f = itemgetter(2), the call f(r) returns r[2].
  After g = itemgetter(2, 5, 3), the call g(r) returns (r[2], r[5], r[3]).
  
  Equivalent to:

  def itemgetter(*items):
      if len(items) == 1:
          item = items[0]
          def g(obj):
              return obj[item]
      else:
          def g(obj):
              return tuple(obj[item] for item in items)
      return g
 
  The @items can be any type accepted by the operand¡¯s __getitem__() method. Diction-
  aries accept any hashable value. Lists, tuples, and strings accept an index or a s-
  lice:

  >>>
  >>> itemgetter(1)('ABCDEFG')
  'B'
  >>> itemgetter(1,3,5)('ABCDEFG')
  ('B', 'D', 'F')
  >>> itemgetter(slice(2,None))('ABCDEFG')
  'CDEFG'
  
  New in version 2.4.
  Changed in version 2.5: Added support for multiple item extraction.

  Example of using itemgetter() to retrieve specific fields from a tuple record:

  >>>
  >>> inventory = [('apple', 3), ('banana', 2), ('pear', 5), ('orange', 1)]
  >>> getcount = itemgetter(1)
  >>> map(getcount, inventory)
  [3, 2, 5, 1]
  >>> sorted(inventory, key=getcount)
  [('orange', 1), ('banana', 2), ('apple', 3), ('pear', 5)]
  '''
  pass
  
  
  
  
  
