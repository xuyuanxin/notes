http://spark.apache.org/docs/latest/running-on-yarn.html

HADOOP_CONF_DIR
YARN_CONF_DIR


--> Running Spark on YARN
  Support for running on YARN (Hadoop NextGen) was added to Spark in version 0.6.0, -
  and improved in subsequent releases.

--> Launching Spark on YARN
  Ensure that HADOOP_CONF_DIR or YARN_CONF_DIR points to the directory which contains 
  the (client side) configuration files for the Hadoop cluster. These configs are us-
  ed to write to HDFS and connect to the YARN ResourceManager. The configuration con-
  tained in this directory will be distributed to the YARN cluster so that all conta-
  iners used by the application use the same configuration. If the configuration ref-
  erences Java system properties or environment variables not managed by YARN, they -
  should also be set in the Spark application¡¯s configuration (driver, executors, and 
  the AM when running in client mode).  
  
  There are two deploy modes that can be used to launch Spark applications on YARN. -
  In "yarn-cluster" mode, the Spark driver runs inside an application master  process 
  which is managed by YARN on the cluster, and the client can go away after initiati-
  ng the application. In "yarn-client" mode, the driver runs in the client process, -
  and the application master is only used for requesting resources from YARN.

  Unlike in Spark standalone and Mesos mode, in which the master¡¯s address is specif-
  ied in the --master parameter, in YARN mode the ResourceManager¡¯s address is picked 
  up from the Hadoop configuration. Thus, the --master parameter is yarn-client or  -
  yarn-cluster. To launch a Spark application in yarn-cluster mode:
  
  $ ./bin/spark-submit --class path.to.your.Class --master yarn-cluster [options] <app jar> [app options]
  
  For example:

  $ ./bin/spark-submit --class org.apache.spark.examples.SparkPi \
    --master yarn-cluster \
    --num-executors 3 \
    --driver-memory 4g \
    --executor-memory 2g \
    --executor-cores 1 \
    --queue thequeue \
    lib/spark-examples*.jar \
    10

  The above starts a YARN client program which starts the default Application Master. 
  Then SparkPi will be run as a child thread of Application Master. The client will -
  periodically poll the Application Master for status updates and display them in the 
  console. The client will exit once your application has finished running. 

  To launch a Spark application in yarn-client mode, do the same, but replace       -
  yarn-cluster with yarn-client. To run spark-shell:

  $ ./bin/spark-shell --master yarn-client

--> Adding Other JARs
  In yarn-cluster mode, the driver runs on a different machine than the client, so  -
  SparkContext.addJar won¡¯t work out of the box with files that are local to the cli-
  ent. To make files on the client available to SparkContext.addJar, include them wi-
  th the --jars option in the launch command.

  $ ./bin/spark-submit --class my.main.Class \
    --master yarn-cluster \
    --jars my-other-jar.jar,my-other-other-jar.jar
    my-main-jar.jar
    app_arg1 app_arg2
  
--> Preparations
  Running Spark-on-YARN requires a binary distribution of Spark which is built with -
  YARN support. Binary distributions can be downloaded from the Spark project websit-
  e. To build Spark yourself, refer to "Building Spark".
  
--> Configuration
  Most of the configs are the same for Spark on YARN as for other deployment modes. -
  See the "configuration page" for more information on those. These are configs  that 
  are specific to Spark on YARN. 
  
  spark-env.sh
  export HADOOP_CONF_DIR=/hadoop2/hadoop-2.3.0/etc/hadoop
  
  
--> Important notes
  Whether core requests are honored in scheduling decisions depends on which schedul-
  er is in use and how it is configured.
  
  In yarn-cluster mode, the local directories used by the Spark executors and the Sp-
  ark driver will be the local directories configured for YARN (Hadoop YARN config  -
  yarn.nodemanager.local-dirs). If the user specifies spark.local.dir, it will be ig-
  nored. In yarn-client mode, the Spark executors will use the local directories con-
  figured for YARN while the Spark driver will use those defined in  spark.local.dir. 
  This is because the Spark driver does not run on the YARN cluster in yarn-client m-
  ode, only the Spark executors do.
  
  The --files and --archives options support specifying file names with the ( similar 
  to Hadoop. For example you can specify: --files localtest.txt) appSees.txt and this 
  will upload the file you have locally named localtest.txt into HDFS but this will -
  be linked to by the name appSees.txt, and your application should use the name as -
  appSees.txt to reference it when running on YARN.
  
  The --jars option allows the SparkContext.addJar function to work if you are  using 
  it with local files and running in yarn-cluster mode. It does not need to be used -
  if you are using it with HDFS, HTTP, HTTPS, or FTP files. 


--> Spark Properties
  Property Name             Default        
  "spark.yarn.am.memory"    512m    
    Amount of memory to use for the YARN Application Master in client mode, in the s-
	ame format as JVM memory strings (e.g. 512m, 2g). In cluster mode, use          -
	spark.driver.memory instead.
  "spark.driver.cores"      1    
    Number of cores used by the driver in YARN cluster mode. Since the driver is  run 
	in the same JVM as the YARN Application Master in cluster mode, this also contro-
	ls the cores used by the YARN AM. In client mode, use spark.yarn.am.cores to con-
	trol the number of cores used by the YARN AM instead.
  "spark.yarn.am.cores"     1    
    Number of cores to use for the YARN Application Master in client mode. In cluste-
	r mode, use spark.driver.cores instead.
  spark.yarn.am.waitTime    100s    In `yarn-cluster` mode, time for the application master to wait for the SparkContext to be initialized. In `yarn-client` mode, time for the application master to wait for the driver to connect to it.
  spark.yarn.submit.file.replication    The default HDFS replication (usually 3)    HDFS replication level for the files uploaded into HDFS for the application. These include things like the Spark jar, the app jar, and any distributed cache files/archives.
  spark.yarn.preserve.staging.files    false    Set to true to preserve the staged files (Spark jar, app jar, distributed cache files) at the end of the job rather than delete them.
  spark.yarn.scheduler.heartbeat.interval-ms    3000    The interval in ms in which the Spark application master heartbeats into the YARN ResourceManager. The value is capped at half the value of YARN's configuration for the expiry interval (yarn.am.liveness-monitor.expiry-interval-ms).
  spark.yarn.scheduler.initial-allocation.interval    200ms    The initial interval in which the Spark application master eagerly heartbeats to the YARN ResourceManager when there are pending container allocation requests. It should be no larger than spark.yarn.scheduler.heartbeat.interval-ms. The allocation interval will doubled on successive eager heartbeats if pending containers still exist, until spark.yarn.scheduler.heartbeat.interval-ms is reached.
  spark.yarn.max.executor.failures    numExecutors * 2, with minimum of 3    The maximum number of executor failures before failing the application.
  spark.yarn.historyServer.address    (none)    The address of the Spark history server (i.e. host.com:18080). The address should not contain a scheme (http://). Defaults to not being set since the history server is an optional service. This address is given to the YARN ResourceManager when the Spark application finishes to link the application from the ResourceManager UI to the Spark history server UI. For this property, YARN properties can be used as variables, and these are substituted by Spark at runtime. For eg, if the Spark history server runs on the same node as the YARN ResourceManager, it can be set to `${hadoopconf-yarn.resourcemanager.hostname}:18080`.
  spark.yarn.dist.archives    (none)    Comma separated list of archives to be extracted into the working directory of each executor.
  spark.yarn.dist.files    (none)    Comma-separated list of files to be placed in the working directory of each executor.
  spark.executor.instances    2    The number of executors. Note that this property is incompatible with spark.dynamicAllocation.enabled. If both spark.dynamicAllocation.enabled and spark.executor.instances are specified, dynamic allocation is turned off and the specified number of spark.executor.instances is used.
  "spark.yarn.executor.memoryOverhead"  executorMemory * 0.10, with minimum of 384    
    The amount of off heap memory (in megabytes) to be allocated per executor. This -
	is memory that accounts for things like VM overheads, interned strings, other na-
	tive overheads, etc. This tends to grow with the executor size (typically 6-10%).
  "spark.yarn.driver.memoryOverhead"    driverMemory * 0.10, with minimum of 384    
    The amount of off heap memory (in megabytes) to be allocated per driver in clust-
	er mode. This is memory that accounts for things like VM overheads, interned str-
	ings, other native overheads, etc. This tends to grow with the container size (t-
	ypically 6-10%).
  spark.yarn.am.memoryOverhead    AM memory * 0.10, with minimum of 384    Same as spark.yarn.driver.memoryOverhead, but for the Application Master in client mode.
  spark.yarn.am.port    (random)    Port for the YARN Application Master to listen on. In YARN client mode, this is used to communicate between the Spark driver running on a gateway and the Application Master running on YARN. In YARN cluster mode, this is used for the dynamic executor feature, where it handles the kill from the scheduler backend.
  spark.yarn.queue    default    The name of the YARN queue to which the application is submitted.
  spark.yarn.jar    (none)    The location of the Spark jar file, in case overriding the default location is desired. By default, Spark on YARN will use a Spark jar installed locally, but the Spark jar can also be in a world-readable location on HDFS. This allows YARN to cache it on nodes so that it doesn't need to be distributed each time an application runs. To point to a jar on HDFS, for example, set this configuration to "hdfs:///some/path".
  spark.yarn.access.namenodes    (none)    A list of secure HDFS namenodes your Spark application is going to access. For example, `spark.yarn.access.namenodes=hdfs://nn1.com:8032,hdfs://nn2.com:8032`. The Spark application must have acess to the namenodes listed and Kerberos must be properly configured to be able to access them (either in the same realm or in a trusted realm). Spark acquires security tokens for each of the namenodes so that the Spark application can access those remote HDFS clusters.
  spark.yarn.appMasterEnv.[EnvironmentVariableName]    (none)    Add the environment variable specified by EnvironmentVariableName to the Application Master process launched on YARN. The user can specify multiple of these and to set multiple environment variables. In `yarn-cluster` mode this controls the environment of the SPARK driver and in `yarn-client` mode it only controls the environment of the executor launcher.
  spark.yarn.containerLauncherMaxThreads    25    The maximum number of threads to use in the application master for launching executor containers.
  spark.yarn.am.extraJavaOptions    (none)    A string of extra JVM options to pass to the YARN Application Master in client mode. In cluster mode, use `spark.driver.extraJavaOptions` instead.
  spark.yarn.am.extraLibraryPath    (none)    Set a special library path to use when launching the application master in client mode.
  spark.yarn.maxAppAttempts    yarn.resourcemanager.am.max-attempts in YARN    The maximum number of attempts that will be made to submit the application. It should be no larger than the global number of max attempts in the YARN configuration.
  spark.yarn.submit.waitAppCompletion    true    In YARN cluster mode, controls whether the client waits to exit until the application completes. If set to true, the client process will stay alive reporting the application's status. Otherwise, the client process will exit after submission.
  spark.yarn.executor.nodeLabelExpression    (none)    A YARN node label expression that restricts the set of nodes executors will be scheduled on. Only versions of YARN greater than or equal to 2.6 support node label expressions, so when running against earlier versions, this property will be ignored.
  spark.yarn.keytab    (none)    The full path to the file that contains the keytab for the principal specified above. This keytab will be copied to the node running the Application Master via the Secure Distributed Cache, for renewing the login tickets and the delegation tokens periodically.
  spark.yarn.principal    (none)    Principal to be used to login to KDC, while running on secure HDFS.
  spark.yarn.config.gatewayPath    (none)    A path that is valid on the gateway host (the host where a Spark application is started) but may differ for paths for the same resource in other nodes in the cluster. Coupled with spark.yarn.config.replacementPath, this is used to support clusters with heterogeneous configurations, so that Spark can correctly launch remote processes.
  The replacement path normally will contain a reference to some environment variable exported by YARN (and, thus, visible to Spark containers).

  For example, if the gateway node has Hadoop libraries installed on /disk1/hadoop, and the location of the Hadoop install is exported by YARN as the HADOOP_HOME environment variable, setting this value to /disk1/hadoop and the replacement path to $HADOOP_HOME will make sure that paths used to launch remote processes properly reference the local YARN configuration.

  spark.yarn.config.replacementPath    (none)    See spark.yarn.config.gatewayPath.
  
  
