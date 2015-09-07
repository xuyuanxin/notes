# http://my.oschina.net/cuffica/blog/33494

#                      os.path

''' os.path.basename(path)
Return the base name of pathname @path. This is the second element of the pair retur-
ned by passing path to the function split().
os.path.basename('/Volumes/1.mp4')   # ('1.mp4')
'''
def basename(path):
    pass

''' os.path.dirname(path)
Return the directory name of pathname @path. This is the first element of the pair r-
eturned by passing path to the function split().
os.path.dirname('/Volumes/1.mp4')   # ('/Volumes')
'''
def dirname(path):
    pass

'''
def join(path, *paths):
    pass
	
''' os.path.split(path)
Split the pathname @path into a pair, (head, tail) where tail is the last pathname c-
omponent and head is everything leading up to that. The tail part will never  contain 
a slash; if path ends in a slash, tail will be empty. If there is no slash in path, -
head will be empty. If path is empty, both head and tail are empty. Trailing  slashes 
are stripped from head unless it is the root (one or more slashes only). In all cases
, join(head, tail) returns a path to the same location as path (but the strings may -
differ). Also see the functions dirname() and basename().

d:\\python\\python.exe -->  ['d:\\python', 'python.exe']
'''
def split(path):
    pass