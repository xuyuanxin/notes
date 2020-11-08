
 Forward References
  Like some other high-level languages, Python does not permit you to reference or c-
  all a function before it has been declared. 
  
  def foo():
      print 'in foo()'
  bar()
      def bar():
      print 'in bar()'
  >>> foo()
  in foo()
  in bar()
  
  This piece of code is fine because even though a call to bar() (from foo()) appears 
  before bar()’s definition, foo() itself is not called before bar() is declared.  In 
  other words, we declared foo(), then bar(), and then called foo(),but by that time, 
  bar() existed already, so the call succeeds.
  
 Inner or Nested Functions
  It is perfectly legitimate to create function (object)s inside other functions. Th-
  at is the definition of an inner or nested function.	

  The (obvious) way to create an inner function is to define a function from within -
  an outer function’s definition (using the def keyword), as in:  
  -------------------inner.py
  def foo():
      def bar():
          print 'bar() called'
      print 'foo() called'
      bar()
  foo()
  bar()
  ------------------
  > python inner.py
  > foo() called
  > bar() called
  > Traceback (most recent call last):
  >   File "inner.py", line 11, in ?
  >     bar()
  > NameError: name 'bar' is not defined  
  One interesting aspect of inner functions is that they are wholly contained  inside 
  the outer function’s scope If there are no outside references to bar(), it cannot -
  be called from anywhere else except inside the outer function, hence the reason for 
  the exception you see at the end of execution in the above code snippet.
  
  Inner functions turn into something special called closures if the definition of an 
  inner function contains a reference to an object defined in an outer function. 
	  
 Function (and Method) Decorators	  
  Decorators are just “overlays” on top of function calls. These overlays are just a-
  dditional calls that are applied when a function or method is declared. The  syntax 
  for decorators uses a leading “at-sign” ( @ ) followed by the decorator function n-
  ame and optional arguments. It looks something like this:

  @decorator(dec_opt_args)
  def func2Bdecorated(func_opt_args):
       : 	   
  
  class MyClass(object):
      def staticFoo():
          :
      staticFoo = staticmethod(staticFoo)
          :
		  
  With decorators, you can now replace that piece of code with the following:

  class MyClass(object):
      @staticmethod
      def staticFoo():
          :
  Furthermore, decorators can be “stacked” like function calls, so here is a more ge-
  neral example with multiple decorators:

  @deco2
  @deco1
  def func(arg1, arg2, ...): pass

  This is equivalent to creating a composite function:
  def func(arg1, arg2, ...): pass
  func = deco2(deco1(func))
  
  Decorators With and Without Arguments
  
  @decomaker(deco_args)
  def foo(): pass

--> Passing Functions
 Python Functions can be referenced (accessed or aliased to other variables),  passed 
 as arguments to functions, be elements of container objects such as lists and dicti-
 onaries, etc. The one unique characteristic of functions which may set them apart f-
 rom other objects is that they are callable, i.e., they can be invoked via the func-
 tion operator.	  
 
 functions can be aliases to other variables. Because all objects are passed by refe-
 rence, functions are no different. When assigning to another variable, you are assi-
 gning the reference to the same object; and if that object is a function, then all -
 aliases to that same object are callable:
 
 >>> def foo():
 ...     print 'in foo()'
 ...
 >>> bar = foo
 >>> bar()
 in foo()
 
 we can even pass functions in as arguments to other functions for invocation:
 >>> def bar(argfunc):
 ...     argfunc()
 ...
 >>> bar(foo)
 in foo()

--> Argument
 -->--> Positional Arguments, Default arguments
  Positional arguments must be passed in the exact order in which they are defined f-
  or the functions that are called. The syntax for declaring variables with default -
  values in Python is such that all positional arguments must come before any default 
  arguments:
  
  def func(posargs, defarg1=dval1, defarg2=dval2,...):
      "function_documentation_string"
      function_body_suite

  Each default argument is followed by an assignment statement of its default  value. 
  If no value is given during a function call, then this assignment is realized.
  
 -->--> Collecting Parameters

  def print_params(*params):
     print params
	 
  The star in front of the parameter puts all the values into the same tuple. It gat-
  hers them up, so to speak.
  
  >>> print_params(1, 2, 3)
  (1, 2, 3)

  def print_params_3(**params):
     print params
 
  >>> print_params_3(x=1, y=2, z=3)
  {'z': 3, 'x': 1, 'y': 2}
  
  Yep, we get a dictionary rather than a tuple. 

  -->--> Reversing the Process
   Now you’ve learned about gathering up parameters in tuples and dictionaries, but it 
   is in fact possible to do the "opposite" as well, with the same two operators, *and 
   **. This is simply done by using the * or ** operator at the "other end" — that is,
   when calling the function rather than when defining it. 
  
   def add(x, y): return x + y
   params = (1, 2) 
   >>> add(*params)
   3
  
   You can use the same technique with dictionaries, using the ** operator.
  
   def print_params_3(**params): print params
   >>> params = {'name': 'Sir Robin', 'greeting': 'Well met'}
   >>> hello_3(**params)
   Well met, Sir Robin!	  

--> Closures
 If references are made from inside an inner function to an object defined in any ou-
 ter scope (but not in the global scope), the inner function then is known as a     -
 @closure. The variables defined in the outer function but used or referred to by the 
 inner function are called free variables. A closure combines an inner function’s own 
 code and scope along with the scope of an outer function. closure variables live  in 
 a function’s namespace and scope.
 
 Simple Closure Example
 
 By using the variable @count inside it, we have created a closure because it now ca-
 rries with it the scope of counter().
 
 def counter(start_at=0):
     count = [start_at]
     def incr():
         count[0] += 1
         return count[0]
     return incr
	 
 >>> count = counter(5)
 >>> print count()
 6
 >>> print count()
 7
 >>> count2 = counter(100)
 >>> print count2()
 101
 >>> print count()
 8	 
	 


----> positional parameters, Keyword Parameters
 |def hello_1(greeting, name):
 |  print '%s, %s!' % (greeting, name)

 @greeting @name are called positional parameters because their positions are import-
 ant. 
 
 hello_1('a','b') 
 hello_1('b','a')   # print not same
 
 hello_1(name='world', greeting='Hello')
 hello_1(greeting='Hello', name='world') # print same

 The parameters that are supplied with a name like this are called keyword parameters. 

 |def hello_3(greeting='Hello', name='world'):
 |   print '%s, %s!' % (greeting, name)

 When a parameter has a default value like this, you don’t need to supply it when you 
 call the function! You can supply none, some, or all, as the situation might dictat-
 e:
 >>> hello_3()
 Hello, world!
 >>> hello_3('Greetings')
 Greetings, world!
 >>> hello_3('Greetings', 'universe')
 Greetings, universe!
 >>> hello_3(name='Gumby')
 Hello, Gumby!

 |def hello_4(name, greeting='Hello', punctuation='!'):
 |    print '%s, %s%s' % (greeting, name, punctuation)
 This function can be called in many ways. Here are some of them:
 >>> hello_4('Mars')
 Hello, Mars!
 >>> hello_4('Mars', 'Howdy')
 Howdy, Mars!
 >>> hello_4('Mars', 'Howdy', '...')
 Howdy, Mars...
 >>> hello_4('Mars', punctuation='.')
 Hello, Mars.
 >>> hello_4('Mars', greeting='Top of the morning to ya')
 Top of the morning to ya, Mars!
 >>> hello_4()
 Traceback (most recent call last):
 File "<pyshell#64>", line 1, in ?
 hello_4()
 TypeError: hello_4() takes at least 1 argument (0 given)
 
----> Collecting Parameters
 |def print_params(*params):
 |  print params
 The star in front of the parameter puts all the values into the same tuple. It gath-
 ers them up, so to speak. 
 >>> print_params(1, 2, 3)
 (1, 2, 3)

 |def print_params_3(**params):
 |   print params
 >>> print_params_3(x=1, y=2, z=3)
 {'z': 3, 'x': 1, 'y': 2}
 Yep, we get a dictionary rather than a tuple. 

 Reversing the Process
 Now you’ve learned about gathering up parameters in tuples and dictionaries, but  it 
 is in fact possible to do the "opposite" as well, with the same two operators, * and 
 **. This is simply done by using the * or ** operator at the "other end" — that is ,
 when calling the function rather than when defining it. 
 |def add(x, y): return x + y
 params = (1, 2) 
 >>> add(*params)
 3
 You can use the same technique with dictionaries, using the ** operator.
 def print_params_3(**params): print params
 >>> params = {'name': 'Sir Robin', 'greeting': 'Well met'}
 >>> hello_3(**params)
 Well met, Sir Robin!

----> Can I Change a Parameter
 Parameters are kept in what is called a local scope
 >>> def try_to_change(n):
 n = 'Mr. Gumby'
 >>> name = 'Mrs. Entity'
 >>> try_to_change(name)
 >>> name
 'Mrs. Entity'
 It’s just as if you did something like this:
 >>> name = 'Mrs. Entity'
 >>> n = name # This is almost what happens when passing a parameter
 >>> n = 'Mr. Gumby' # This is done inside the function
 >>> name
 'Mrs. Entity'
 But consider what happens if you use a mutable data structure such as a list:
 >>> def change(n):
 n[0] = 'Mr. Gumby'
 >>> names = ['Mrs. Entity', 'Mrs. Thing']
 >>> change(names)
 >>> names
 ['Mr. Gumby', 'Mrs. Thing']
 Let’s do it again without the function call:
 >>> names = ['Mrs. Entity', 'Mrs. Thing']
 >>> n = names # Again pretending to pass names as a parameter
 >>> n[0] = 'Mr. Gumby' # Change the list
 >>> names
 ['Mr. Gumby', 'Mrs. Thing']
 You’ve seen this sort of thing before. When two variables refer to the same list,  -
 they . . . refer to the same list. It’s really as simple as that. If you want to av-
 oid this, you must make a copy of the list. When you do slicing on a sequence, the -
 returned slice is always a copy. Thus, if you make a slice of the entire list, you -
 get a copy:
 >>> names = ['Mrs. Entity', 'Mrs. Thing']
 >>> n = names[:]
 Now n and names contain two separate (nonidentical) lists that are equal:
 >>> n is names
 False
 >>> n == names
 True
 If you change n now (as you did inside the function change), it won’t affect names:
 >>> n[0] = 'Mr. Gumby'
 >>> n
 ['Mr. Gumby', 'Mrs. Thing']
 >>> names
 ['Mrs. Entity', 'Mrs. Thing']
 Let’s try this trick with change:
 >>> change(names[:])
 >>> names
 ['Mrs. Entity', 'Mrs. Thing']
 Now the parameter n contains a copy, and your original list is safe.

----> Scoping
 What are variables, really? You can think of them as names referring to values.  So, 
 after the assignment x = 1, the name x refers to the value 1. It’s almost like usin-
 g dictionaries, where keys refer to values, except that you’re using an  "invisible" 
 dictionary. Actually, this isn’t far from the truth. There is a built-in function c-
 alled @vars, which returns this dictionary:
 >>> x = 1
 >>> scope = vars()
 >>> scope['x']
 1
 >>> scope['x'] += 1
 >>> x
 2
 This sort of "invisible dictionary" is called a namespace or scope. So, how many na-
 mespaces are there? In addition to the global scope, each function call creates a n-
 ew one:
 >>> def foo(): x = 42
 ...
 >>> x = 1
 >>> foo()
 >>> x
 1

 The parameters work just like local variables, so there is no problem in having a p-
 arameter with the same name as a global variable:
 >>> def output(x): print x
 ...
 >>> x = 1
 >>> y = 2
 >>> output(y)
 2

 But what if you want to access the global variables inside a function? 
 >>> def combine(parameter): print parameter + external
 ...
 >>> external = 'berry'
 >>> combine('Shrub')
 Shrubberry

 If a local variable or parameter exists with the same name as the global variable y-
 ou want to access, you can’t do it directly. The global variable is shadowed by  the 
 local one. If needed, you can still gain access to the global variable by using  the 
 function @globals.

 >>> def combine(parameter):
 print parameter + globals()['parameter']
 ...
 >>> parameter = 'berry'
 >>> combine('Shrub')
 Shrubberry

 And how do you think you can tell it to make a variable global?
 >>> x = 1
 >>> def change_global():
 global x
 x = x + 1
 >>> change_global()
 >>> x
 2

----> NESTED SCOPES closure
 Python functions may be nested, you can put one inside another. Here is an example:
 |def foo():
 |   def bar():
 |       print "Hello, world!"
 |   bar()
 Nesting is normally not all that useful, but there is one particular application th-
 at stands out: using one function to "create" another. This means that you can (amo-
 ng other things) write functions like the following:
 |def multiplier(factor):
 |  def multiplyByFactor(number):
 |      return number*factor
 |  return multiplyByFactor
 One function is inside another, and the outer function returns the inner one; that -
 is, the function itself is returned, it is not called. What’s important is that  the 
 returned function still has access to the scope where it was defined; in other words
 , it carries its environment (and the associated local variables) with it! Each time 
 the outer function is called, the inner one gets redefined, and each time, the vari-
 able factor may have a new value. Because of Python’s nested scopes, this variable -
 from the outer local scope (of multiplier) is accessible in the inner function later 
 on, as follows:
 >>> double = multiplier(2)
 >>> double(5)
 10
 >>> triple = multiplier(3)
 >>> triple(3)
 9
 >>> multiplier(5)(4)
 20
 A function such as multiplyByFactor that stores its enclosing scopes is called a   -
 @closure.

