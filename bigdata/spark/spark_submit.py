
./bin/spark-submit \
  --class <main-class>
  --master <master-url> \
  --deploy-mode <deploy-mode> \
  --conf <key>=<value> \
  ... # other options
  <application-jar> [application-arguments]


----> spark-submit 参数

 --master MASTER_URL
  可以是spark://host:port, mesos://host:port, yarn,  yarn-cluster,yarn-client, local
  
 --deploy-mode DEPLOY_MODE
   driver运行之处，client运行在本机，cluster运行在集群
  
 --class CLASS_NAME
  主类名称，含包名

 --name NAME
  Application名称
  
 --jars JARS
  Driver依赖的第三方jar包

 --py-files PY_FILES
  用逗号隔开的放置在Python应用程序PYTHONPATH上的.zip, .egg, .py文件列表

 --files FILES
  用逗号隔开的要放置在每个executor工作目录的文件列表

 --properties-file FILE
  设置应用程序属性的文件路径，默认是conf/spark-defaults.conf

 --driver-memory MEM
  Driver程序使用内存大小

 --driver-java-options
 
 --driver-library-path
  Driver程序的库路径

 --driver-class-path
  Driver程序的类路径

 --executor-memory MEM
  executor内存大小，默认1G

 --driver-cores NUM
  Driver程序的使用CPU个数，仅限于Spark Alone模式

 --supervise
  失败后是否重启Driver，仅限于Spark  Alone模式

 --total-executor-cores NUM
  executor使用的总核数，仅限于Spark Alone、Spark on Mesos模式

 --executor-cores NUM
  每个executor使用的内核数，默认为1，仅限于Spark on Yarn模式

 --queue QUEUE_NAME
  提交应用程序给哪个YARN的队列，默认是default队列，仅限于Spark on Yarn模式

 --num-executors NUM 
  启动的executor数量，默认是2个，仅限于Spark on Yarn模式

 --archives ARCHIVES
  仅限于Spark on Yarn模式
  
