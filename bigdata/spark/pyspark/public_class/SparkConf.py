class SparkConf: # class pyspark.SparkConf(loadDefaults=True, _jvm=None, _jconf=None)
  '''
  All setter methods in this class support chaining. For example, you can write 
    conf.setMaster(¡°local¡±).setAppName(¡°My app¡±).
  Note that once a SparkConf object is passed to Spark, it is cloned and can no long-
  er be modified by the user.
  
  conf = SparkConf().setAppName(appName).setMaster(master)
  sc = SparkContext(conf=conf)
  
  scala
  val conf = new SparkConf()
             .setMaster("local[2]")
             .setAppName("CountingSheep")
             .set("spark.executor.memory", "1g")
  val sc = new SparkContext(conf)
  '''
  
  def set(key, value):
    # Set a configuration property.
    pass
  
  def setAppName(value):
    # Set application name.
    pass
	
  def setMaster(value):
    #Set master URL to connect to.
    pass

  
  
  
