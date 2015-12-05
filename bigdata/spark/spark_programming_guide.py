

Initializing Spark
 The first thing a Spark program must do is to create a SparkContext object, which t-
 ells Spark how to access a cluster. To create a SparkContext you first need to build 
 a SparkConf object that contains information about your application.
 > conf = SparkConf().setAppName(appName).setMaster(master)
 > sc = SparkContext(conf=conf)
 The @appName parameter is a name for your application to show on the cluster UI.   -
 @master is a Spark, Mesos or YARN cluster URL, or a special ¡°local¡± string to run in 
 local mode. In practice, when running on a cluster, you will not want to hardcode m-
 aster in the program, but rather launch the application with spark-submit and recei-
 ve it there. However, for local testing and unit tests, you can pass ¡°local¡± to  run 
 Spark in-process.