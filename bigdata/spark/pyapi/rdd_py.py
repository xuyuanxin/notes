

def aggregate(self, zeroValue, seqOp, combOp):
  ''' pyspark.RDD.aggregate (Python method, in pyspark package)
  http://atlantageek.com/2015/05/30/python-aggregate-rdd/index.html

  Aggregate lets you take an RDD and generate a single value that is of a different -
  type than what was stored in the original RDD. It does this with three  parameters. 
  A @zeroValue (or initial value) in the format of the result. A @seqOp function tha-
  t given the resulting type and an individual element in the RDD will merge the  RDD 
  element into the resulting object. The @combOb merges two resulting objects togeth-
  er.

  Consider an example. We want to take a list of records about people and then we wa-
  nt to sum up their ages and count them. So for this example the type in the RDD wi-
  ll be a Dictionary in the format of {name: NAME, age:AGE, gender:GENDER}. The resu-
  lt type will be a tuple that looks like so (Sum of Ages, Count)
  Lets first generate a peopleRDD with 5 people

  people = []
  people.append({'name':'Bob', 'age':45,'gender':'M'})
  people.append({'name':'Gloria', 'age':43,'gender':'F'})
  people.append({'name':'Albert', 'age':28,'gender':'M'})
  people.append({'name':'Laura', 'age':33,'gender':'F'})
  people.append({'name':'Simone', 'age':18,'gender':'T'})
  peopleRdd=sc.parallelize(people)
  len(peopleRdd.collect())
  
  Now we need to create the seqOp. This takes an object of the rdd type and merge  it 
  into a record of the result type. Or another way to say this is add the age to  the 
  first element of the resulting tuple and add 1 for the second element of the tuple

  seqOp = (lambda x,y: (x[0] + y['age'],x[1] + 1))
  
  Now we write an operation to merge two resulting tuple.

  combOp = (lambda x,y: (x[0] + y[0], x[1] + y[1]))
  
  Run the function

  peopleRdd.aggregate((0,0), seqOp, combOp)
  (167, 5)
  
  And here is the result. So why is this convoluted? The combOp seems unecessary  but 
  in the map reduce world of spark you need that seperate operation. Realize that th-
  ese functions are going to be parallelized. peopleRDD is partitioned up. And depen-
  dending on its source and method of converting the data to an RDD each row could be 
  on its own partition.

  So lets backup and define a few things

  partition - A partition is how the RDD is split up. If our RDD was 100,000  records 
  we could have as many as 100,000 partitions or only 1 partition depending on how we 
  created the RDD.

  task - A small job that operates on a single partition. A single task can run on o-
  nly one machine at a time and can operate on only one partiton at a time.

  For the aggregate function the seqOp will run once for every record in a partition. 
  This will result in a resulting object for each partition. The combOp will be  used 
  to merge all the resulting objects together.
  '''
  
  
  