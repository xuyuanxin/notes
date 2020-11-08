

def enumerate(sequence, start=0):
  '''
  Return an enumerate object. @sequence must be a sequence, an iterator, or some oth-
  er object which supports iteration. The next() method of the iterator returned by -
  enumerate() returns a tuple containing a count (from @start which defaults to 0) a-
  nd the values obtained from iterating over sequence:
  
  >>> seasons = ['Spring', 'Summer', 'Fall', 'Winter']
  >>> list(enumerate(seasons))
  [(0, 'Spring'), (1, 'Summer'), (2, 'Fall'), (3, 'Winter')]
  >>> list(enumerate(seasons, start=1))
  [(1, 'Spring'), (2, 'Summer'), (3, 'Fall'), (4, 'Winter')]
  
  app_list = [1234, 5677, 8899]
  for index,app_id in enumerate(app_list):
    print index, app_id
 
  output£º 
  0 1234 
  1 5677 
  2 8899
  '''
  pass
  
