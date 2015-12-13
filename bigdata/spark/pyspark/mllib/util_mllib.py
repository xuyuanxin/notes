






class MLUtils: # pyspark.mllib.util.MLUtils

  '''
  '''
  
  def static loadLibSVMFile(sc, path, numFeatures=-1, minPartitions=None, multiclass=None): 
    '''
    Loads labeled data in the LIBSVM format into an RDD of LabeledPoint. The LIBSVM -
	format is a text-based format used by LIBSVM and LIBLINEAR. Each line  represents 
	a labeled sparse feature vector using the following format:
    label index1:value1 index2:value2 ...
    where the indices are one-based and in ascending order. This method parses each -
	line into a LabeledPoint, where the feature indices are converted to zero-based.

    @sc: Spark context
    @path: file or directory path in any Hadoop-supported file system URI
    @numFeatures: number of features, which will be determined from the input data if 
	  a nonpositive value is given. This is useful when the dataset is already  split 
	  into multiple files and you want to load them separately, because some features 
	  may not present in certain files, which leads to inconsistent feature dimensio-
	  ns.
    @minPartitions ¨C min number of partitions
    @Returns: labeled data stored as an RDD of LabeledPoint
    '''
    pass














