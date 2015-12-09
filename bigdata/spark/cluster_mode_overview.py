http://spark.apache.org/docs/latest/cluster-overview.html

----> 
 This document gives a short overview of how Spark runs on clusters, to make it easi-
 er to understand the components involved. Read through the "application submission -
 guide" to learn about launching applications on a cluster.
 
----> Components
 Spark applications run as independent sets of processes on a cluster, coordinated b-
 y the SparkContext object in your main program (called the driver program).

 Specifically, to run on a cluster, the SparkContext can connect to several types  of 
 cluster managers (either Spark¡¯s own standalone cluster manager, Mesos or YARN), wh-
 ich allocate resources across applications. Once connected, Spark acquires executors 
 on nodes in the cluster, which are processes that run computations and store data f-
 or your application. Next, it sends your application code ( defined by JAR or Python 
 files passed to SparkContext) to the executors. Finally, SparkContext sends tasks to 
 the executors to run.
 
 There are several useful things to note about this architecture:
 1 Each application gets its own executor processes, which stay up for the duration -
   of the whole application and run tasks in multiple threads. This has the benefit -
   of isolating applications from each other, on both the scheduling side (each driv-
   er schedules its own tasks) and executor side (tasks from different applications -
   run in different JVMs). However, it also means that data cannot be shared across -
   different Spark applications (instances of SparkContext) without writing it to  an 
   external storage system.
 2 Spark is agnostic to the underlying cluster manager. As long as it can acquire ex-
   ecutor processes, and these communicate with each other, it is relatively easy  to 
   run it even on a cluster manager that also supports other applications (e.g.     -
   Mesos/YARN).
 3 The driver program must listen for and accept incoming connections from its execu-
   tors throughout its lifetime (e.g., see "spark.driver.port and                   -
   spark.fileserver.port" in the network config section). As such, the driver program 
   must be network addressable from the worker nodes.
 4 Because the driver schedules tasks on the cluster, it should be run close to the -
   worker nodes, preferably on the same local area network. If you¡¯d like to send re-
   quests to the cluster remotely, it¡¯s better to open an RPC to the driver and  have 
   it submit operations from nearby than to run a driver far away from the worker no-
   des.
   
----> Cluster Manager Types
 The system currently supports three cluster managers:
 Standalone
  a simple cluster manager included with Spark that makes it easy to set up a cluste-
  r.
 Apache Mesos
  a general cluster manager that can also run Hadoop MapReduce and service applicati-
  ons.
 Hadoop YARN
  the resource manager in Hadoop 2.
 In addition, Spark¡¯s EC2 launch scripts make it easy to launch a standalone  cluster 
 on Amazon EC2.




