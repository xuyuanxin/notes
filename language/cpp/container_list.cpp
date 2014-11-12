/*******************************************************************************
 The container classes of the STL are different kinds of data structures for holding 
 data, such as lists, queues, and stacks. Each is a template class with a parameter 
 for the particular type of data to be stored. So, for example, you can specify a 
 list to be a list of ints, or doubles, or strings, or any class or struct type you 
 wish. Each container template class may have its own specialized accessor and mutator 
 functions for adding data and removing data from the container. Different container 
 classes may have different kinds of iterators. For example, one container class may 
 have bidirectional iterators while another container class may have only forward 
 iterators. However, whenever they are defined the iterator operators and the member 
 functions begin()and end() have the same meaning for all STL container classes.

 There are, however, differences between a vector and a list container. One of the 
 main differences is that a vector container has random access iterators while a 
 list has only bidirectional iterators.



 sequential container : A sequential container arranges its data items into a list 
 so there is a first element, a next element, and so forth up to a last element.

 */
