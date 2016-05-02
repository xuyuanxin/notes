


def itemgetter(item)
def itemgetter(*items): # operator.itemgetter
  '''
  Return a callable object that fetches @item from its operand using the operand¡¯s  -
  __getitem__() method. If multiple @items are specified, returns a tuple of lookup -
  values. For example:
  After f = itemgetter(2), the call f(r) returns r[2].
  After g = itemgetter(2, 5, 3), the call g(r) returns (r[2], r[5], r[3]).
  '''
  pass