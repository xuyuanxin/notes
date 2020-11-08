# http://my.oschina.net/cuffica/blog/33494

#                      os.path


def basename(path): #os.path.basename(path)
  ''' 
  Return the base name of pathname @path. This is the second element of the pair ret-
  urned by passing path to the function split().
  os.path.basename('/Volumes/1.mp4')   # ('1.mp4')
  '''
  pass

def dirname(path):
  ''' os.path.dirname(path)
  Return the directory name of pathname @path. This is the first element of the  pair 
  returned by passing path to the function split().
  os.path.dirname('/Volumes/1.mp4')   # ('/Volumes')
  '''
  pass

def exists(path):
  '''
  Return True if @path refers to an existing path. Returns False for broken  symbolic 
  links. On some platforms, this function may return False if permission is not gran-
  ted to execute os.stat() on the requested file, even if the path physically exists.
  '''
  pass

def isfile(path) # os.path.isfile
  '''
  Return True if path is an existing regular file. This follows symbolic links, so b-
  oth islink() and isfile() can be true for the same path.
  '''
  pass

def join(path, *paths):
  '''
  Join one or more path components intelligently. The return value is the concatenat-
  ion of @path and any members of *@paths with exactly one directory separator      -
  (os.sep) following each non-empty part except the last, meaning that the result wi-
  ll only end in a separator if the last part is empty. If a component is an absolute 
  path, all previous components are thrown away and joining continues from the absol-
  ute path component.

  On Windows, the drive letter is not reset when an absolute path component (e.g.,  -
  r'\foo') is encountered. If a component contains a drive letter, all previous comp-
  onents are thrown away and the drive letter is reset. Note that since there is a c-
  urrent directory for each drive, os.path.join("c:", "foo") represents a path relat-
  ive to the current directory on drive C: (c:foo), not c:\foo.
  
  >>> os.path.join('c:\\', 'csv', 'test.csv') 
  'c:\\csv\\test.csv' 
  >>> os.path.join('windows\temp', 'c:\\', 'csv', 'test.csv') 
  'c:\\csv\\test.csv' 
  >>> os.path.join('/home/aa','/home/aa/bb','/home/aa/bb/c') 
  '/home/aa/bb/c' 
  '''
  pass

def split(path):
  ''' os.path.split(path)
  Split the pathname @path into a pair, (head, tail) where tail is the last  pathname 
  component and head is everything leading up to that. The tail part will never cont-
  ain a slash; if path ends in a slash, tail will be empty. If there is no slash in -
  path, head will be empty. If path is empty, both head and tail are empty.  Trailing 
  slashes are stripped from head unless it is the root (one or more slashes only). In 
  all cases, join(head, tail) returns a path to the same location as path (but the s-
  trings may differ). Also see the functions dirname() and basename().

  d:\\python\\python.exe -->  ['d:\\python', 'python.exe']
  '''
  pass


