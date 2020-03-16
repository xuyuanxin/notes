# Classes and OOP  

## OOP: The Big Picture   /todo

## Class Coding Basics  

### Classes Generate Multiple Instance Objects

there are two kinds of objects in Python’s OOP model: class objects and instance objects. Class objects provide default behavior and serve as factories for instance objects. Instance objects are the real objects your programs process--each is a namespace in its own right, but inherits (i.e., has automatic access to) names in the class from which it was created. Class objects come from statements, and instances come from calls; each time you call a class, you get a new instance of that class.

Class Objects Provide Default Behavior. When we run a @class statement, we get a class object. Here’s a rundown of the  main properties of Python classes:

- The @class statement creates a class object and assigns it a name. 

  the Python @class statement is an executable statement. When reached and run, it generates a new class object and assigns it to the name in the class header.

- Assignments inside @class statements make class attributes

  Just like in module files, top-level assignments within a @class statement (not nested in a def) generate attributes in a class object. Technically, the @class statement defines a local scope that morphs into the attribute namespace of the class object, just like a module’s global scope. After running a @class statement, class attributes are accessed by name qualification: object.name.

- Class attributes provide object state and behavior.

  Attributes of a class object record state information and behavior to be shared by all instances created  from the class; function @def statements nested inside a @class generate methods, which process instances.

Instance Objects Are Concrete Items. When we call a class object, we get an instance object. Here’s an overview of the key points behind class instances:

- Calling a class object like a function makes a new instance object. Each time a class is called, it creates and returns a new instance object. Instances represent concrete items in your program’s domain.
- Each instance object inherits class attributes and gets its own namespace. Instance objects created from classes are new namespaces; they start out empty but inherit attributes that live in the class objects from which they were generated.
- Assignments to attributes of @self in methods make per-instance attributes. Inside a class’s method functions, the first argument (called @self by convention) references the instance object being processed; assignments to attributes of @self create or change data in the instance, not the class.

The end result is that classes define common, shared data and behavior, and generate instances. Instances reflect concrete application entities, and record  per-instance data that may vary per object.

#### A First Example

To begin, let’s define a class named FirstClass by running a Python class statement interactively:  

```python
>>> class FirstClass: # Define a class object
        def setdata(self, value): # Define class's methods
            self.data = value # self is the instance
        def display(self):
            print(self.data) # self.data: per instance
```

the class starts with a header line that lists the class name, followed by a body of one or more nested and (usually) indented statements. Functions inside a class are usually called methods. They’re coded with normal defs. But in a method function, the first argument automatically receives an implied instance object when called--the subject of the call. We need to create a couple of instances to see how this works:  

```python
>>> x = FirstClass() # Make two instances
>>> y = FirstClass() # Each is a new namespace
```

By calling the class this way (notice the parentheses), we generate instance objects, which are just namespaces that have access to their classes’ attributes. at this point, we have three objects: two instances and a class.

```python
   +-------+
   |   X   |         is-a               +------------+
   | -data |--------------------------->| FirstClass |
   +-------+                            |            |
                                        | -setdata   |
   +-------+                            | -display   |
   |   X   |         is-a               |            |
   | -data |--------------------------->|            |
   +-------+                            +------------+ 
```

Figure 27-1. Classes and instances are linked namespace objects in a class tree that is searched by inheritance. Here, the "data" attribute is found in instances, but "setdata" and "display" are in the class above them.

The two instances start out empty but have links back to the class from which they were generated. If we qualify an instance with the name of an attribute that lives in the class object, Python fetches the name from the class by inheritance search  

```python
>>> x.setdata("King Arthur") # Call methods: self is x
>>> y.setdata(3.14159) # Runs: FirstClass.setdata(y, 3.14159)

>>> x.display() # self.data differs in each instance
King Arthur
>>> y.display() # Runs: FirstClass.display(y)
3.14159
```

Neither x nor y has a @setdata attribute of its own, so to find it, Python  follows the link from instance to class. And that’s about all there is to inheritance in Python: it happens at attribute qualification time, and it just involves looking up names in linked objects—here, by following the is-a links in Figure 27-1.

### Classes Are Customized by Inheritance  

In Python, instances inherit from classes, and classes inherit from superclasses. Here are the key ideas behind the machinery of attribute inheritance:  

## Class Coding Details  

### The class Statement  

Like a def, a class statement is an object builder, and an implicit assignment--when run, it generates a class object
and stores a reference to it in the name used in the header. Also like a def, a class statement is true executable code--your class doesn’t exist until Python reaches and runs the class statement that defines it. This typically occurs while importing the module it is coded in, but not before.  

@class is a compound statement, with a body of statements typically indented appearing under the header. In the header, superclasses are listed in parentheses after the class name, separated by commas. Listing more than one superclass leads to multiple inheritance. Here is the statement’s general form:

```python
class name(superclass,...): # Assign to name
    attr = value # Shared class data
    def method(self,...): # Methods
        self.attr = value # Per-instance data  
```

Within the @class statement, any assignments generate class attributes, and specially named methods overload operators; for instance, a function called `__init__` is called at instance object construction time, if defined.

As we’ve seen, classes are mostly just namespaces--that is, tools for defining names(i.e., attributes) that export data and logic to clients.  Just as in a module file, the statements nested in a class statement body create its attributes. When Python executes a class statement (not a call to a class), it runs all the statements in its body, from top to bottom. Assignments that happen during this process create names in the class’s local scope, which become attributes in the associated class object.  

For example, assignments of simple nonfunction objects to class attributes produce data attributes, shared by all instances:  

```python
>>> class SharedData:
        spam = 42 # Generates a class data attribute
>>> x = SharedData() # Make two instances
>>> y = SharedData()
>>> x.spam, y.spam # They inherit and share 'spam' (a.k.a. SharedData.spam)
(42, 42)

>>> SharedData.spam = 99
>>> x.spam, y.spam, SharedData.spam
(99, 99, 99)
```

Here, because the name spam is assigned at the top level of a class statement, it is attached to the class and so will be shared by all instances.  Now, watch what happens if we assign the name spam through an instance instead of the class:  

```python
>>> x.spam = 88
>>> x.spam, y.spam, SharedData.spam
(88, 99, 99)
```

Here’s a more comprehensive example of this behavior that stores the same name in two places. Suppose we run the following class:

```python
class MixedNames: # Define class
   data = 'spam' # Assign class attr
   def __init__(self, value): # Assign method name
       self.data = value # Assign instance attr
   def display(self):
       print(self.data, MixedNames.data) # Instance attr, class attr
```

When we make instances of this class, the name data is attached to those instances by the assignment to self.data in the constructor method:  

```python
>>> x = MixedNames(1) # Make two instance objects
>>> y = MixedNames(2) # Each has its own data
>>> x.display(); y.display() # self.data differs, MixedNames.data is the same
1 spam
2 spam
```

The net result is that data lives in two places: in the instance objects (created by the self.data assignment in __init__), and in the class from which they inherit names(created by the data assignment in the class). The class’s display method prints both versions, by first qualifying the self instance, and then the class.  

### Method

Methods are just function objects created by def statements nested in a class statement’s body. From an abstract perspective, methods provide behavior for instance objects to inherit. From a programming perspective, methods work in exactly the same way as simple functions, with one crucial exception: a method’s first argument always receives the instance object that is the implied subject of the method call.  

Method calls made through an instance, like this:

```python
instance.method(args...)
```

are automatically translated to class method function calls of this form:

```python
class.method(instance, args...)  
```

In a class’s method, the first argument is usually called self by convention (technically, only its position is significant, not its name). This argument provides methods with a hook back to the instance that is the subject of the call--because classes generate many instance objects, they need to use this argument to manage data that varies per instance.  

To clarify these concepts, let’s turn to an example. Suppose we define the following class:

```python
class NextClass: # Define class
    def printer(self, text): # Define method
        self.message = text # Change instance
        print(self.message) # Access instance  
```

The name printer references a function object; because it’s assigned in the class statement’s scope, it becomes a class object attribute and is inherited by every instance made from the class. Normally, because methods like printer are designed to process instances, we call them through instances:  

```python
>>> x = NextClass() # Make instance
>>> x.printer('instance call') # Call its method
instance call
>>> x.message # Instance changed
'instance call
```

When we call the method by qualifying an instance like this, printer is first located by inheritance, and then its self argument is automatically assigned the instance object (x); the text argument gets the string passed at the call ('instance call'). Notice that because Python automatically passes the first argument to self for us, we only actually have to pass in one argument. Inside printer, the name self is used to access or set per-instance data because it refers back to the instance currently being processed

As we’ve seen, though, methods may be called in one of two ways--through an instance, or through the class itself. For example, we can also call printer by going through the class name, provided we pass an instance to the self argument explicitly:

```python
>>> NextClass.printer(x, 'class call') # Direct class call
class call
>>> x.message # Instance changed again
'class call'
```

Calls routed through the instance and the class have the exact same effect, as long as we pass the same instance object ourselves in the class form. By default, in fact, you get an error message if you try to call a method without any instance:

```python
>>> NextClass.printer('bad call')
TypeError: unbound method printer() must be called with NextClass instance...
```

### Calling Superclass Constructors  

If subclass constructors need to guarantee that superclass construction-time logic runs, too, they generally must call the superclass’s `__init__` method explicitly through the class:

```python
class Super:
    def __init__(self, x):
        ...default code...

class Sub(Super):
    def __init__(self, x, y):
        Super.__init__(self, x) # Run superclass __init__
        ...custom code... # Do my init actions

I = Sub(1, 2)  
```

### Inheritance  

Of course, the whole point of the namespace created by the class statement is to support name inheritance.  Every time you use an expression of the form object.attr where object is an instance or class object, Python searches the namespace tree from bottom to top, beginning with object, looking for the first attr it can find. This includes references to self attributes in your methods. Because lower definitions in the tree override higher ones, inheritance forms the basis
of specialization.  

# Operator Overloading  

## Call Expressions: `__call__`  

```python
class tracer:
    def __init__(self, func): # Remember original, init counter
        self.calls = 0
        self.func = func
    def __call__(self, *args): # On later calls: add logic, run original
        self.calls += 1
        print('call %s to %s' % (self.calls, self.func.__name__))
        return self.func(*args)

@tracer # Same as spam = tracer(spam)
def spam(a, b, c): # Wrap spam in a decorator object
    return a + b + c

print(spam(1, 2, 3)) # Really calls the tracer wrapper object
    print(spam('a', 'b', 'c')) # Invokes __call__ in class
```

Because the spam function is run through the tracer decorator, when the original spam name is called it actually triggers the `__call__` method in the class. This method counts and logs the call, and then dispatches it to the original wrapped function.  

```python
c:\code> python tracer1.py
call 1 to spam
6
call 2 to spam
abc
```

### A First Look at Class Decorators and Metaclasses  



# Advanced Class Topics

## Static and Class Methods

As of Python 2.2, it is possible to define two kinds of methods within a class that can be called without an instance: static methods work roughly like simple instance-less functions inside a class, and class methods are passed a class instead of an instance.  

### Why the Special Methods?  

Sometimes, programs need to process data associated with classes instead of instances. Consider keeping track of the number of instances created from a class. This type of information and its processing are associated with the class rather than its instances.    

Python supports such goals with the notion of static methods—simple functions with no self argument that are nested in a class and are designed to work on class attributes instead of instance attributes.   

### Static Methods in 2.X and 3.X  

To illustrate, suppose we want to use class attributes to count how many instances are generated from a class. The following file, spam.py, makes a first attempt  

```python
class Spam:
    numInstances = 0
    def __init__(self):
        Spam.numInstances = Spam.numInstances + 1
    def printNumInstances():
        print("Number of instances created: %s" % Spam.numInstances)
```

The printNumInstances method is designed to process class data, not instance data—it’s about all the instances, not any one in particular. Because of that, we want to be able to call it without having to pass an instance.  

In 2.X, calls to a self-less method function through both the class and instances fail (as usual, I’ve omitted some error text here for space):  

```python
C:\code> c:\python27\python
>>> from spam import Spam
>>> a = Spam() # Cannot call unbound class methods in 2.X
>>> b = Spam() # Methods expect a self object by default
>>> c = Spam()
>>> Spam.printNumInstances()
TypeError: unbound method printNumInstances() must be called with Spam instance
as first argument (got nothing instead)
>>> a.printNumInstances()
TypeError: printNumInstances() takes no arguments (1 given)
```

In Python 3.X, calls to self-less methods made through classes work, but calls from instances fail:  

```python
C:\code> c:\python33\python
>>> from spam import Spam
>>> a = Spam() # Can call functions in class in 3.X
>>> b = Spam() # Calls through instances still pass a self
>>> c = Spam()
>>> Spam.printNumInstances() # Differs in 3.X
Number of instances created: 3
>>> a.printNumInstances()
TypeError: printNumInstances() takes 0 positional arguments but 1 was given
```

That is, calls to instance-less methods like printNumInstances made through the class fail in Python 2.X but work in Python 3.X. On the other hand, calls made through an instance fail in both Pythons, because an instance is automatically passed to a method that does not have an argument to receive it:

```python
Spam.printNumInstances() # Fails in 2.X, works in 3.X
instance.printNumInstances() # Fails in both 2.X and 3.X (unless static)
```

If you’re able to use 3.X and stick with calling self-less methods through classes only, you already have a static method feature. However, to allow self-less methods to be called through classes in 2.X and through instances in both 2.X and 3.X, you need to either adopt other designs or be able to somehow mark such methods as special. Let’s look at both options in turn.  

### Static Method Alternatives 

if you just want to call functions that access class members without an instance, perhaps the simplest idea is to use normal functions outside the class, not class methods. This way, an instance isn’t expected in the call. The following mutation of spam.py illustrates, and works the same in Python 3.X and 2.X:  

```python
def printNumInstances():
    print("Number of instances created: %s" % Spam.numInstances)
class Spam:
    numInstances = 0
    def __init__(self):
        Spam.numInstances = Spam.numInstances + 1
C:\code> c:\python33\python
>>> import spam
>>> a = spam.Spam()
>>> b = spam.Spam()
>>> c = spam.Spam()
>>> spam.printNumInstances() # But function may be too far removed
Number of instances created: 3 # And cannot be changed via inheritance
>>> spam.Spam.numInstances
3
```

Because the class name is accessible to the simple function as a global variable, this works fine. 

### Using Static and Class Methods

```python
# File bothmethods.py
class Methods:
    def imeth(self, x): # Normal instance method: passed a self
        print([self, x])
    def smeth(x): # Static: no instance passed
        print([x])
        
    def cmeth(cls, x): # Class: gets class, not instance
        print([cls, x])
        
    smeth = staticmethod(smeth) # Make smeth a static method (or @: ahead)
    cmeth = classmethod(cmeth) # Make cmeth a class method (or @: ahead)
```

Notice how the last two assignments in this code simply reassign (a.k.a. rebind) the method names smeth and cmeth. Attributes are created and changed by any assignment in a class statement, so these final assignments simply overwrite the assignments made earlier by the defs. 

Technically, Python now supports three kinds of class-related methods, with differing argument protocols:

- Instance methods, passed a self instance object (the default)
- Static methods, passed no extra object (via staticmethod)
- Class methods, passed a class object (via classmethod, and inherent in metaclasses)    

Moreover, Python 3.X extends this model by also allowing simple functions in a class to serve the role of static methods without extra protocol, when called through a class object only. 

Instance methods are the normal and default case that we’ve seen in this book. An instance method must always be called with an instance object. When you call it through an instance, Python passes the instance to the first (leftmost) argument automatically; when you call it through a class, you must pass along the instance manually:  

```python
>>> from bothmethods import Methods # Normal instance methods
>>> obj = Methods() # Callable through instance or class
>>> obj.imeth(1)
[<bothmethods.Methods object at 0x0000000002A15710>, 1]
```

Static methods, by contrast, are called without an instance argument. 

```python
>>> Methods.smeth(3) # Static method: call through class
[3] # No instance passed or expected
>>> obj.smeth(4) # Static method: call through instance
[4] # Instance not passed
```

Class methods are similar, but Python automatically passes the class (not an instance) in to a class method’s first (leftmost) argument, whether it is called through a class or an instance:  

```python
>>> Methods.cmeth(5) # Class method: call through class
[<class 'bothmethods.Methods'>, 5] # Becomes cmeth(Methods, 5)
>>> obj.cmeth(6) # Class method: call through instance
[<class 'bothmethods.Methods'>, 6] # Becomes cmeth(Methods, 6)
```

### Counting Instances with Static Methods  

```python
class Spam:
    numInstances = 0 # Use static method for class data
    def __init__(self):
        Spam.numInstances += 1
    def printNumInstances():
        print("Number of instances: %s" % Spam.numInstances)
    printNumInstances = staticmethod(printNumInstances)
```

Using the static method built-in, our code now allows the self-less method to be called through the class or any instance of it, in both Python 2.X and 3.X:  

```python
>>> from spam_static import Spam
>>> a = Spam()
>>> b = Spam()
>>> c = Spam()
>>> Spam.printNumInstances() # Call as simple function
Number of instances: 3
>>> a.printNumInstances() # Instance argument not passed
Number of instances: 3
```

```python
class Sub(Spam):
    def printNumInstances(): # Override a static method
        print("Extra stuff...") # But call back to original
        Spam.printNumInstances()
    printNumInstances = staticmethod(printNumInstances)
>>> from spam_static import Spam, Sub
>>> a = Sub()
>>> b = Sub()
>>> a.printNumInstances() # Call from subclass instance
Extra stuff...
Number of instances: 2
>>> Sub.printNumInstances() # Call from subclass itself
Extra stuff...
Number of instances: 2
>>> Spam.printNumInstances() # Call original version
Number of instances: 2
>>> class Other(Spam): pass # Inherit static method verbatim
>>> c = Other()
>>> c.printNumInstances()
Number of instances: 3
```

### Counting Instances with Class Methods  

```python
class Spam:
    numInstances = 0 # Use class method instead of static
    def __init__(self):
        Spam.numInstances += 1
    def printNumInstances(cls):
        print("Number of instances: %s" % cls.numInstances)
    printNumInstances = classmethod(printNumInstances)

>>> from spam_class import Spam
>>> a, b = Spam(), Spam()
>>> a.printNumInstances() # Passes class to first argument
Number of instances: 2
>>> Spam.printNumInstances() # Also passes class to first argument
Number of instances: 2
```

## Decorators and Metaclasses: Part 1

This is called a “decoration,” but in more concrete terms is really just a way to run extra processing steps at function and class definition time with explicit syntax. It comes in two flavors:  Function decorators, Class decorators.

### Function Decorator Basics  

Syntactically, a function decorator is a sort of runtime declaration about the function that follows. A function decorator is coded on a line by itself just before the def statement that defines a function or method. It consists of the @ symbol, followed by what we call a metafunction—a function (or other callable object) that manages another function.   

Static methods since Python 2.4, for example, may be coded with decorator syntax like this:  

```python
class C:
    @staticmethod # Function decoration syntax
    def meth():
        ...
```

Internally, this syntax has the same effect as the following—passing the function through the decorator and assigning the result back to the original name:  

```python
class C:
    def meth():
        ...
    meth = staticmethod(meth) # Name rebinding equivalent
```

### A First Look at User-Defined Function Decorators  

Although Python provides a handful of built-in functions that can be used as decorators, we can also write custom decorators of our own.  As a quick example, though, let’s look at a simple user-defined decorator at work.  

### A First Look at Class Decorators and Metaclasses  

In short, class decorators are similar to function decorators, but they are run at the end of a class statement to rebind a class name to a callable. As such, they can be used to either manage classes just after they are created, or insert a layer of wrapper logic to manage instances when they are later created. Symbolically, the code structure:  

```python
def decorator(aClass): ...

@decorator # Class decoration syntax
class C: ...
```

is mapped to the following equivalent:

```python
def decorator(aClass): ...

class C: ... # Name rebinding equivalent
C = decorator(C)
```



## 参考：

learning python （python学习手册）



