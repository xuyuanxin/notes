
--> Python Objects
 Python uses the object model abstraction for data storage. Any construct that conta-
 ins any type of value is an object. All Python objects have the following three cha-
 racteristics: an identity, a type, and a value.
 
 IDENTITY 
 Unique identifier that differentiates an object from all others. Any object¡¯s ident-
 ifier can be obtained using the id() builtin function (BIF). This value is as  close 
 as you will get to a "memory address" in Python.
 
 TYPE 
 An object¡¯s type indicates what kind of values an object can hold, what operations -
 can be applied to such objects, and what behavioral rules these objects are  subject 
 to. You can use the type() BIF to reveal the type of a Python object. Since types a-
 re also objects in Python, type() actually returns an object to you rather than a s-
 imple literal.
 
 VALUE 
 Data item that is represented by an object.
 
 All three are assigned on object creation and are read-only with one exception,  the 
 value. (For new-style types and classes, it may possible to change the type of an o-
 bject, but this is not recommended for the beginner.) If an object supports updates, 
 its value can be changed; otherwise, it is also read-only. 
 
 >>> a=1
 >>> id(a)
 37839336L
 >>> type(a)
 <type 'int'>
 
 Object Attributes
 Certain Python objects have attributes, data values or executable code such as meth-
 ods, associated with them. The most familiar attributes are functions and methods, -
 but some Python types have data attributes associated with them. Objects with data -
 attributes include (but are not limited to): classes, class instances, modules, com-
 plex numbers, and files.
 
--> Standard Types
 Numbers (separate subtypes; three are integer types)
   Integer
     Boolean
     Long integer
   Floating point real number
   Complex number
 String
 List
 Tuple
 Dictionary
 
--> Other Built-in Types
 Type
 Null object (None)
 File
 Set/Frozenset
 Function/Method
 Module
 Class 
 
--> type object
 you can find out the type of an object by calling type() with that object:
 >>> type(42)
 <type 'int'> 
 What you see as <type 'int'> is actually a type object. 
 
 Now you may ask yourself, so then what is the type of any type object? Well, let  us 
 find out:
 >>> type(type(42))
 <type 'type'>
 Yes, the type of all type objects is type. The type "type object" is also the mother 
 of all types and is the default metaclass for all standard Python classes. With  the 
 unification of types and classes in Python 2.2, type objects are playing a more sig-
 nificant role in both object-oriented programming as well as day-to-day object usag-
 e. Classes are now types, and instances are now objects of their respective types.
 
--> None, Python¡¯s Null Object
 Python has a special type known as the Null object or NoneType. It has only one val-
 ue, None. The type of None is NoneType. It does not have any operators or BIFs. If -
 you are familiar with C, the closest analogy to the None type is void, while the   -
 None value is similar to the C value of NULL. None has no (useful) attributes and a-
 lways evaluates to having a Boolean False value.
 
--> Boolean values
 All standard type objects can be tested for truth value and compared to objects of -
 the same type. Objects have inherent True or False values. Objects take a False val-
 ue when they are empty, any numeric representation of zero, or the Null object None.
 The following are defined as having false values in Python:
 * None
 * False (Boolean)
 * Any numeric zero:
   * 0 (integer)
   * 0.0 (float)
   * 0L (long integer)
   * 0.0+0.0j (complex)
 * "" (empty string)
 * [] (empty list)
 * () (empty tuple)
 * {} (empty dictionary)
 Any value for an object other than those above is considered to have a true value, -
 i.e., non-empty, non-zero, etc. User-created class instances have a false value when 
 their nonzero (__nonzero__()) or length (__len__()) special methods, if defined, re-
 turn a zero value.
 
--> Standard Type Operators
 -->--> Object Value Comparison
  Comparison operators are used to determine equality of two data values between mem-
  bers of the same type. These comparison operators are supported for all built-in t-
  ypes. Comparisons yield Boolean True or False values, based on the validity of  the 
  comparison expression.
  
  Standard Type Value Comparison Operators
  Operator        Function
  expr1 < expr2   expr1 is less than expr2
  expr1 > expr2   expr1 is greater than expr2
  expr1 <= expr2  expr1 is less than or equal to expr2
  expr1 >= expr2  expr1 is greater than or equal to expr2
  expr1 == expr2  expr1 is equal to expr2
  expr1 != expr2  expr1 is not equal to expr2 (C-style)
  
  >>> [3, 'abc'] == ['abc', 3]
  False
  >>> [3, 'abc'] == [3, 'abc']
  True
  >>> 3 < 4 < 7 # same as ( 3 < 4 ) and ( 4 < 7 )
  True
  >>> 4 > 3 == 3 # same as ( 4 > 3 ) and ( 3 == 3 )
  True
 -->--> Object Identity Comparison
  In addition to value comparisons, Python also supports the notion of directly comp-
  aring objects themselves.

  Standard Type Object Identity Comparison Operators
  Operator       Function
  obj1 is obj2   obj1 is the same object as obj2
  obj1 is not    obj2 obj1 is not the same object as obj2  
  
  Python provides the "is" and "is not" operators to test if a pair of variables do -
  indeed refer to the same object. Performing a check such as
  >>> a is b
  is an equivalent expression to
  >>> id(a) == id(b)
  >>> a = [ 5, 'hat', -9.3]
  >>> b = a
  >>> a is b
  True
  >>> a is not b
  False
  >>>
  >>> b = 2.5e-5
  >>> b
  2.5e-005
  >>> a
  [5, 'hat', -9.3]
  >>> a is b
  False
  >>> a is not b
  True
  
  Python caches or interns only simple integers that it believes will be used freque-
  ntly in any Python application. At the time of this writing, Python interns intege-
  rs in the range(-5, 257) but this is subject to change, so do not code your applic-
  ation to expect this.
  >>> a = 1
  >>> id(a)
  8402824
  >>> b = 1
  >>> id(b)
  8402824
  >>>
  >>> c = 1.0
  >>> id(c)
  8651220
  >>> d = 1.0
  >>> id(d)
  8651204
  
 -->--> Boolean
  Standard Type Boolean Operators
  Operator          Function
  not expr          Logical NOT of expr (negation)
  expr1 and expr2   Logical AND of expr1 and expr2 (conjunction)
  expr1 or expr2    Logical OR of expr1 and expr2 (disjunction)
  
  >>> x, y = 3.1415926536, -1024
  >>> x < 5.0
  True
  >>> not (x < 5.0)
  False
  >>> (x < 5.0) or (y > 2.718281828)
  True
  >>> (x < 5.0) and (y > 2.718281828)
  False
  >>> not (x is y)
  True
  
 
