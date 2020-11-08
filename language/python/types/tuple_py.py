'''
Tuples are sequences, just like lists. The only difference is that tuples can’t be c-
hanged. (As you may have noticed, this is also true of strings.) The tuple syntax  is 
simple—if you separate some values with commas, you automatically have a tuple:
'''
>>> 1, 2, 3
(1, 2, 3)

>>> (1, 2, 3) # As you can see, tuples may also be (and often are) enclosed in parentheses:
(1, 2, 3)     # 

>>> ()        # The empty tuple is written as two parentheses containing nothing:
()


>>> 42
42
>>> 42,
(42,)
>>> (42,)
(42,)
>>> 3*(40+2)
126
>>> 3*(40+2,)
(42, 42, 42)

''' The tuple Function
The tuple function works in pretty much the same way as list: it takes one sequence -
argument and converts it to a tuple. If the argument is already a tuple, it is retur-
ned unchanged:
'''
>>> tuple([1, 2, 3])
(1, 2, 3)
>>> tuple('abc')
('a', 'b', 'c')
>>> tuple((1, 2, 3))
(1, 2, 3)

tup=(1, 2, 3, 4, 5)
#元组转为字符串，返回：(1, 2, 3, 4, 5)
print tup.__str__()

