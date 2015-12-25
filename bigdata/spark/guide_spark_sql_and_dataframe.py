http://spark.apache.org/docs/latest/sql-programming-guide.html



examples/src/main/resources/people.json
{"name":"Michael"}
{"name":"Andy", "age":30}
{"name":"Justin", "age":19}


Overview
 Spark SQL is a Spark module for structured data processing. It provides a programmi-
 ng abstraction called DataFrames and can also act as distributed SQL query engine. -
 Spark SQL can also be used to read data from an existing Hive installation.
 
--> DataFrames
 -->--> Starting Point: SQLContext
  
  #python
  >from pyspark.sql import SQLContext
  >sqlContext = SQLContext(sc)
  
 -->--> Creating DataFrames
  #python
  >from pyspark.sql import SQLContext
  >sqlContext = SQLContext(sc)
  >df = sqlContext.read.json("examples/src/main/resources/people.json")
  # Displays the content of the DataFrame to stdout
  >df.show()
  
 -->--> DataFrame Operations
 
  ------- python
  from pyspark.sql import SQLContext
  sqlContext = SQLContext(sc)
  
  # Create the DataFrame
  df = sqlContext.read.json("examples/src/main/resources/people.json")
   
  # Show the content of the DataFrame
  df.show()
  ## age  name
  ## null Michael
  ## 30   Andy
  ## 19   Justin

  # Print the schema in a tree format
  df.printSchema()
  ## root
  ## |-- age: long (nullable = true)
  ## |-- name: string (nullable = true)

  # Select only the "name" column
  df.select("name").show()
  ## name
  ## Michael
  ## Andy
  ## Justin

  # Select everybody, but increment the age by 1
  df.select(df['name'], df['age'] + 1).show()
  ## name    (age + 1)
  ## Michael null
  ## Andy    31
  ## Justin  20

  # Select people older than 21
  df.filter(df['age'] > 21).show()
  ## age name
  ## 30  Andy

  # Count people by age
  df.groupBy("age").count().show()
  ## age  count
  ## null 1
  ## 19   1
  ## 30   1
 
 
 
 
 
 
 
 
 
 
 
 
 
 