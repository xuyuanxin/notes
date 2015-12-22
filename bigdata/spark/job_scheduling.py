http://spark.apache.org/docs/latest/job-scheduling.html


Overview
Scheduling Across Applications
  Dynamic Resource Allocation
    Configuration and Setup
    Resource Allocation Policy
      Request Policy
      Remove Policy
    Graceful Decommission of Executors
Scheduling Within an Application
  Fair Scheduler Pools
  Default Behavior of Pools
  Configuring Pool Properties

Overview
  Spark has several facilities for scheduling resources between computations.  First, 
  recall that, as described in the "cluster mode overview", each Spark application (-
  instance of SparkContext) runs an independent set of executor processes. The clust-
  er managers that Spark runs on provide facilities for scheduling across applicatio-
  ns. Second, within each Spark application, multiple "jobs" (Spark actions) may be -
  running concurrently if they were submitted by different threads. This is common if 
  your application is serving requests over the network. Spark includes a fair sched-
  uler to schedule resources within each SparkContext.

Scheduling Across Applications
  When running on a cluster, each Spark application gets an independent set of execu-
  tor JVMs that only run tasks and store data for that application. If multiple users 
  need to share your cluster, there are different options to manage allocation, depe-
  nding on the cluster manager.

  The simplest option, available on all cluster managers, is static partitioning of -
  resources. With this approach, each application is given a maximum amount of resou-
  rces it can use, and holds onto them for its whole duration. This is the approach -
  used in Spark’s standalone and YARN modes, as well as the coarse-grained Mesos mod-
  e. Resource allocation can be configured as follows, based on the cluster type:
  
  Standalone mode: By default, applications submitted to the standalone mode  cluster 
  will run in FIFO (first-in-first-out) order, and each application will try to use -
  all available nodes. You can limit the number of nodes an application uses by sett-
  ing the spark.cores.max configuration property in it, or change the default for ap-
  plications that don’t set this setting through spark.deploy.defaultCores.  Finally, 
  in addition to controlling cores, each application’s spark.executor.memory  setting 
  controls its memory use.
  
  Mesos: To use static partitioning on Mesos, set the spark.mesos.coarse configurati-
  on property to true, and optionally set spark.cores.max to limit each application’s 
  resource share as in the standalone mode. You should also set spark.executor.memory 
  to control the executor memory.
  
  YARN: The --num-executors option to the Spark YARN client controls how many execut-
  ors it will allocate on the cluster, while --executor-memory and --executor-cores -
  control the resources per executor.
  
  
  












