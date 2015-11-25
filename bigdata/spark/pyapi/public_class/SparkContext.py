

def union(rdds): # pyspark.SparkContext.union (Python method, in pyspark package)
  '''
  Build the union of a list of RDDs. This supports unions() of RDDs with different s-
  erialized formats, although this forces them to be reserialized using the default -
  serializer:
  
  >>> path = os.path.join(tempdir, "union-text.txt")
  >>> with open(path, "w") as testFile:
  ...    _ = testFile.write("Hello")
  >>> textFile = sc.textFile(path)
  >>> textFile.collect()
  [u'Hello']
  >>> parallelized = sc.parallelize(["World!"])
  >>> sorted(sc.union([textFile, parallelized]).collect())
  [u'Hello', 'World!']
  '''
  
