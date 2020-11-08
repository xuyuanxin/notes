# http://my.oschina.net/guol/blog/95699
'''                                                                                  |
CSV全称为"Comma Separated Values", 是一种格式化的文件, 由行和列组成, 分隔符可以根据需|
要来变化. 如下面为一csv文件:                                                         |
Title,Release Date,Director
And Now For Something Completely Different,1971,Ian MacNaughton
Monty Python And The Holy Grail,1975,Terry Gilliam and Terry Jones
Monty Python's Life Of Brian,1979,Terry Jones
Monty Python Live At The Hollywood Bowl,1982,Terry Hughes
Monty Python's The Meaning Of Life,1983,Terry Jones
-------------------------------------------------------------------------------------|


'''

def reader(csvfile, dialect='excel', **fmtparams) # csv.reader
  '''
  >>> import csv
  >>> with open('eggs.csv', 'rb') as csvfile:
  ...     spamreader = csv.reader(csvfile, delimiter=' ', quotechar='|')
  ...     for row in spamreader:
  ...         print ', '.join(row)
  Spam, Spam, Spam, Spam, Spam, Baked Beans
  Spam, Lovely Spam, Wonderful Spam
  '''
  pass