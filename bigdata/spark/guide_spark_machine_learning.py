Machine Learning Library (MLlib) Guide

http://spark.apache.org/docs/latest/mllib-guide.html




spark.mllib: data types, algorithms, and utilities


--> MLlib - Data Types
 MLlib supports local vectors and matrices stored on a single machine, as well as di-
 stributed matrices backed by one or more RDDs. Local vectors and local matrices  are 
 simple data models that serve as public interfaces. The underlying linear algebra o-
 perations are provided by Breeze and jblas. A training example used in supervised l-
 earning is called a ¡°labeled point¡± in MLlib.