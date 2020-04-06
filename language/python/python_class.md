Classes and OOP  

# OOP: The Big Picture   /todo

# Class Coding Basics  

## Classes Generate Multiple Instance Objects

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

### A First Example

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

## Classes Are Customized by Inheritance  

In Python, instances inherit from classes, and classes inherit from superclasses. Here are the key ideas behind the machinery of attribute inheritance:  

- Superclasses are listed in parentheses in a class header.  
- Classes inherit attributes from their superclasses. Just as instances inherit the attribute names defined in their classes, classes inherit all of the attribute names defined in their superclasses; Python finds them automatically when they’re accessed, if they don’t exist in the subclasses.   
- Instances inherit attributes from all accessible classes. Each instance gets names from the class it’s generated from, as well as all of that class’s superclasses. When looking for a name, Python checks the instance, then its class, then all superclasses.  
- Each object.attribute reference invokes a new, independent search. Python performs an independent search of the class tree for each attribute fetch expression. This includes references to instances and classes made outside class statements (e.g., X.attr), as well as references to attributes of the self instance argument in a class’s method functions. Each self.attr expression in a method invokes a new
  search for attr in self and above.  
- Logic changes are made by subclassing, not by changing superclasses. By redefining superclass names in subclasses lower in the hierarchy (class tree), subclasses replace and thus customize inherited  behavior.  

### A Second Example

To illustrate the role of inheritance, this next example builds on the previous one. First, we’ll define a new class, SecondClass, that inherits all of FirstClass’s names and provides one of its own:   

```python
>>> class SecondClass(FirstClass): # Inherits setdata
        def display(self): # Changes display
            print('Current value = "%s"' % self.data)
```

SecondClass defines the display method to print with a different format. By defining an attribute with the same name as an attribute in FirstClass, SecondClass effectively replaces the display attribute in its superclass.   

```python
>>> z = SecondClass()
>>> z.setdata(42) # Finds setdata in FirstClass
>>> z.display() # Finds overridden method in SecondClass
Current value = "42"
```

Now, here’s a crucial thing to notice about OOP: the specialization introduced in SecondClass is completely external to FirstClass. That is, it doesn’t affect existing or future FirstClass objects, like the x from the prior example: 

```python
>>> x.display() # x is still a FirstClass instance (old message)
New value
```

### Classes Are Attributes in Modules

Before we move on, remember that there’s nothing magic about a class name. It’s just a variable assigned to an object when the class statement runs, and the object can be referenced with any normal expression. For instance, if our FirstClass were coded in a module file instead of being typed interactively, we could import it and use its name normally in a class header line:

```python
from modulename import FirstClass # Copy name into my scope
class SecondClass(FirstClass): # Use class name directly
    def display(self): ...
        
# Or, equivalently:
import modulename # Access the whole module
class SecondClass(modulename.FirstClass): # Qualify to reference
    def display(self): ...
```

## Classes Can Intercept Python Operators

In simple terms, operator overloading lets objects coded with classes intercept and respond to operations that work on built-in types: addition, slicing, printing, qualification, and so on.   

- Methods named with double underscores (`__X__`) are special hooks.   
- Such methods are called automatically when instances appear in built-in operations. For instance, if an instance object inherits an `__add__` method, that method is called whenever the object appears in a + expression. The method’s return value becomes the result of the corresponding expression.   
- Classes may override most built-in type operations.  
- There are no defaults for operator overloading methods, and none are required. If a class does not define or inherit an operator overloading method, it just means that the corresponding operation is not supported for the class’s instances. If there is no `__add__`, for example, + expressions raise exceptions. 
- New-style classes have some defaults, but not for common operations. In Python 3.X, and so-called “new style” classes in 2.X that we’ll define later, a root class named object does provide defaults for some `__X__` methods, but not for many, and not for most commonly used operations.  
- Operators allow classes to integrate with Python’s object model. By overloading type operations, the user-defined objects we implement with classes can act just like built-ins, and so provide consistency as well as compatibility with expected interfaces.

### A Third Example

```python
>>> class ThirdClass(SecondClass): # Inherit from SecondClass
        def __init__(self, value): # On "ThirdClass(value)"
            self.data = value
        def __add__(self, other): # On "self + other"
            return ThirdClass(self.data + other)
        def __str__(self): # On "print(self)", "str()"
            return '[ThirdClass: %s]' % self.data 
        def mul(self, other): # In-place change: named
            self.data *= other

>>> a = ThirdClass('abc') # __init__ called
>>> a.display() # Inherited method called
Current value = "abc"
>>> print(a) # __str__: returns display string
[ThirdClass: abc]
>>> b = a + 'xyz' # __add__: makes a new instance
>>> b.display() # b has all ThirdClass methods
Current value = "abcxyz"
>>> print(b) # __str__: returns display string
[ThirdClass: abcxyz]
>>> a.mul(3) # mul: changes instance in place
>>> print(a)
[ThirdClass: abcabcabc]
```

### Why Use Operator Overloading?

As mentioned earlier, if you omit an operator overloading method and do not inherit it from a superclass, the corresponding operation will not be supported for your instances; if it’s attempted, an exception will be raised (or, in some cases like printing, a standard default will be used).  

## The World’s Simplest Python Class

```python
>>> class rec: pass # Empty namespace object
```

After we make the class by running this statement interactively, we can start attaching attributes to the class by assigning names to it completely outside of the original class statement:

```python
>>> rec.name = 'Bob' # Just objects with attributes
>>> rec.age = 40

>>> print(rec.name) # Like a C struct or a record
Bob
```

Notice that this works even though there are no instances of the class yet; classes are objects in their own right, even without instances. In fact, they are just self-contained namespaces; as long as we have a reference to a class, we can set or change its attributes anytime we wish. Watch what happens when we do create two instances, though:

```python
>>> x = rec() # Instances inherit class names
>>> y = rec()
>>> x.name, y.name # name is stored on the class only
('Bob', 'Bob')
```

Really, these instances have no attributes of their own; they simply fetch the name attribute from the class object where it is stored. If we do assign an attribute to an instance, though, it creates (or changes) the attribute in that object

```python
>>> x.name = 'Sue' # But assignment changes x only
>>> rec.name, x.name, y.name
('Bob', 'Sue', 'Bob')
```

```python
>>> list(rec.__dict__.keys())
['age', '__module__', '__qualname__', '__weakref__', 'name', '__dict__', '__doc__']
>>> list(name for name in rec.__dict__ if not name.startswith('__'))
['age', 'name']
>>> list(x.__dict__.keys())
['name']
>>> list(y.__dict__.keys()) # list() not required in Python 2.X
[]

>>> x.name, x.__dict__['name'] # Attributes present here are dict keys
('Sue', 'Sue')
>>> x.age # But attribute fetch checks classes too
40
>>> x.__dict__['age'] # Indexing dict does not do inheritance
KeyError: 'age'
```

Here, the class’s namespace dictionary shows the name and age attributes we assigned to it, x has its own name, and y is still empty. Because of this model, an attribute can often be fetched by either dictionary indexing or attribute notation, but only if it’s present on the object in question—attribute notation kicks off inheritance search, but indexing looks in the single object only (as we’ll see later, both have valid roles):

```python
>>> x.__class__ # Instance to class link
<class '__main__.rec'>
>>> rec.__bases__ # Class to superclasses link, () in 2.X
(<class 'object'>,)
```

Even methods, normally created by a def nested in a class, can be created completely independently of any class object. The following, for example, defines a simple function outside of any class that takes one argument:

```python
>>> def uppername(obj):
        return obj.name.upper() # Still needs a self argument (obj)
    
>>> rec.method = uppername # Now it's a class's method!
>>> x.method() # Run method to process x
'SUE'
>>> y.method() # Same, but pass y to self
'BOB'
>>> rec.method(x) # Can call through instance or class
'SUE'
```

# A More Realistic Example

## Step 1: Making Instances

The normal way to give instance attributes their first values is to assign them to self in the `__init__` constructor method, which contains code run automatically by Python each time an instance is created. Let’s add one to our class:  

```python
class Person:
    def __init__(self, name, job=None, pay=0): # Constructor takes three arguments
        self.name = name # Fill out fields when created
        self.job = job # self is the new instance object
        self.pay = pay

if __name__ == '__main__': # When run for testing only
    # self-test code
    bob = Person('Bob Smith')
    sue = Person('Sue Jones', job='dev', pay=100000)
    print(bob.name, bob.pay)
    print(sue.name, sue.pay)
```

In OO terms, self is the newly created instance object, and name, job, and pay become state information—descriptive data saved on an object for later use.  Now, we get exactly the behavior we’re after—running the file as a top-level script tests it because its `__name__` is `__main__`, but importing it as a library of classes later does not:

```python
C:\code> person.py
Bob Smith 0
Sue Jones 100000
C:\code> python
Python 3.3.0 (v3.3.0:bd8afb90ebf2, Sep 29 2012, 10:57:17) ...
>>> import person
>>>
```

## Step 2: Adding Behavior Methods  

```python
# Add methods to encapsulate operations for maintainability
class Person:
    def __init__(self, name, job=None, pay=0):
        self.name = name
        self.job = job
        self.pay = pay
    def lastName(self): # Behavior methods
        return self.name.split()[-1] # self is implied subject
    def giveRaise(self, percent):
        self.pay = int(self.pay * (1 + percent)) # Must change here only

if __name__ == '__main__':
    bob = Person('Bob Smith')
    sue = Person('Sue Jones', job='dev', pay=100000)
    print(bob.name, bob.pay)
    print(sue.name, sue.pay)
    print(bob.lastName(), sue.lastName()) # Use the new methods
    sue.giveRaise(.10) # instead of hardcoding
    print(sue.pay)
```

## Step 3: Operator Overloading  

```python
# Add __repr__ overload method for printing objects
class Person:
    def __init__(self, name, job=None, pay=0):
        self.name = name
        self.job = job
        self.pay = pay
    def lastName(self):
        return self.name.split()[-1]
    def giveRaise(self, percent):
        self.pay = int(self.pay * (1 + percent))
    def __repr__(self): # Added method
        return '[Person: %s, %s]' % (self.name, self.pay) # String to print

if __name__ == '__main__':
    bob = Person('Bob Smith')
    sue = Person('Sue Jones', job='dev', pay=100000)
    print(bob)
    print(sue)
    print(bob.lastName(), sue.lastName())
    sue.giveRaise(.10)
    print(sue)
```

```python
[Person: Bob Smith, 0]
[Person: Sue Jones, 100000]
Smith Jones
[Person: Sue Jones, 110000]
```

## Step 4: Customizing Behavior by Subclassing  



# Class Coding Details  

## The class Statement  

Like a def, a class statement is an object builder, and an implicit assignment--when run, it generates a class object and stores a reference to it in the name used in the header. Also like a def, a class statement is true executable code--your class doesn’t exist until Python reaches and runs the class statement that defines it. This typically occurs while importing the module it is coded in, but not before.  

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

The net result is that data lives in two places: in the instance objects (created by the self.data assignment in `__init__`), and in the class from which they inherit names(created by the data assignment in the class). The class’s display method prints both versions, by first qualifying the self instance, and then the class.  

## Method

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

## Inheritance  

Of course,the whole point of the namespace created by the class statement is to support nameinheritance.  Every time you use an expression of the form object.attr where object is an instance or class object, Python searches the namespace tree from bottom to top, beginning with object, looking for the first attr it can find. This includes references to self attributes in your methods. Because lower definitions in the tree override higher ones, inheritance forms the basis of specialization.  

### Attribute Tree Construction

![python_class_01](F:\mygit\notes\language\python\images\python_class_01.PNG)  

Figure 29-1. Program code creates a tree of objects in memory to be searched by attribute inheritance. Calling a class creates a new instance that remembers its class, running a class statement creates a new class, and superclasses are listed in parentheses in the class statement header. Each attribute reference triggers a new bottom-up tree search—even references to self attributes within a class’s methods.  

The net result is a tree of attribute namespaces that leads from an instance, to the class it was generated from, to all the superclasses listed in the class header. Python searches upward in this tree, from instances to superclasses, each time you use qualification to fetch an attribute name from an instance object.  

### Specializing Inherited Methods  

```python
>>> class Super:
        def method(self):
            print('in Super.method')
>>> class Sub(Super):
        def method(self): # Override method
            print('starting Sub.method') # Add actions here
            Super.method(self) # Run default action
            print('ending Sub.method')
```

Direct superclass method calls are the crux of the matter here. The Sub class replaces Super’s method function with its own specialized version, but within the replacement, Sub calls back to the version exported by Super to carry out the default behavior. In other words, Sub.method just extends Super.method’s behavior, rather than replacing it completely:

```python
>>> x = Super() # Make a Super instance
>>> x.method() # Runs Super.method
in Super.method
>>> x = Sub() # Make a Sub instance
>>> x.method() # Runs Sub.method, calls Super.method
starting Sub.method
in Super.method
ending Sub.method
```

### Class Interface Techniques  

Extension is only one way to interface with a superclass. The file shown in this section, specialize.py, defines multiple classes that illustrate a variety of common techniques: 

- Super: Defines a method function and a delegate that expects an action in a subclass.
- Inheritor:Doesn’t provide any new names, so it gets everything defined in Super.
- Replacer:Overrides Super’s method with a version of its own.   
- Extender: Customizes Super’s method by overriding and calling back to run the default.  
- Provider: Implements the action method expected by Super’s delegate method.  

```python
# specialize.py
class Super:
    def method(self):
        print('in Super.method') # Default behavior
    def delegate(self):
        self.action() # Expected to be defined

class Inheritor(Super): # Inherit method verbatim
    pass

class Replacer(Super): # Replace method completely
    def method(self):    
        print('in Replacer.method')

class Extender(Super): # Extend method behavior
    def method(self):
        print('starting Extender.method')
        Super.method(self)
        print('ending Extender.method')

class Provider(Super): # Fill in a required method
    def action(self):
        print('in Provider.action')

if __name__ == '__main__':
    for klass in (Inheritor, Replacer, Extender):
        print('\n' + klass.__name__ + '...')
        klass().method()
    
    print('\nProvider...')
    x = Provider()
    x.delegate()
```

```python
% python specialize.py
Inheritor...
in Super.method

Replacer...
in Replacer.method

Extender...
starting Extender.method
in Super.method
ending Extender.method

Provider...
in Provider.action
```

### Abstract Superclasses  

Of the prior example’s classes, Provider may be the most crucial to understand. When we call the delegate method through a Provider instance, two independent inheritance searches occur:

1. On the initial x.delegate call, Python finds the delegate method in Super by searching the Provider instance and above. The instance x is passed into the method’s self argument as usual.
2. Inside the Super.delegate method, self.action invokes a new, independent inheritance search of self and above. Because self references a Provider instance, the action method is located in the Provider subclass.

At least in terms of the delegate method, the superclass in this example is what is sometimes called an abstract superclass—a class that expects parts of its behavior to be provided by its subclasses. If an expected method is not defined in a subclass, Python raises an undefined name exception when the inheritance search fails.

```python
class Super:
    def delegate(self):
        self.action()
    def action(self):
        raise NotImplementedError('action must be defined!')

>>> X = Super()
>>> X.delegate()
NotImplementedError: action must be defined!
    
>>> class Sub(Super): pass
>>> X = Sub()
>>> X.delegate()
NotImplementedError: action must be defined!

>>> class Sub(Super):
        def action(self): print('spam')
>>> X = Sub()
>>> X.delegate()
spam
```

As of Python 2.6 and 3.0, the prior section’s abstract superclasses (a.k.a. “abstract base classes”), which require methods to be filled in by subclasses, may also be implemented with special class syntax. In Python 3.X, we use a keyword argument in a class header, along with special @decorator syntax  

```python
from abc import ABCMeta, abstractmethod

class Super(metaclass=ABCMeta):
    @abstractmethod
    def method(self, ...):
        pass
```

But in Python 2.6 and 2.7, we use a class attribute instead:  

```python
class Super:
    __metaclass__ = ABCMeta
    @abstractmethod
    def method(self, ...):
        pass
```

Either way, the effect is the same—we can’t make an instance unless the method is defined lower in the class tree. In 3.X, for example, here is the special syntax equivalent of the prior section’s example:  

```python
>>> from abc import ABCMeta, abstractmethod
>>>
>>> class Super(metaclass=ABCMeta):
        def delegate(self):
            self.action()
        @abstractmethod
        def action(self):
            pass
>>> X = Super()
TypeError: Can't instantiate abstract class Super with abstract methods action

>>> class Sub(Super): pass
>>> X = Sub()
TypeError: Can't instantiate abstract class Sub with abstract methods action

>>> class Sub(Super):
        def action(self): print('spam')
>>> X = Sub()
>>> X.delegate()
spam
```

Coded this way, a class with an abstract method cannot be instantiated (that is, we cannot create an instance by calling it) unless all of its abstract methods have been defined in subclasses.   

# Operator Overloading  

## The Basics  

Really “operator overloading” simply means intercepting built-in operations in a class’s methods—Python automatically invokes your methods when instances of the class appear in built-in operations, and your method’s return value becomes the result of the corresponding operation. Here’s a review of the key ideas behind overloading:  

- Operator overloading lets classes intercept normal Python operations.
- Classes can overload all Python expression operators.
- Classes can also overload built-in operations such as printing, function calls, attribute access, etc.
- Overloading makes class instances act more like built-in types.
- Overloading is implemented by providing specially named methods in a class. 

## Attribute Access: `__getattr__` and `__setattr__`  

In Python, classes can also intercept basic attribute access (a.k.a. qualification) when needed or useful. Specifically, for an object created from a class, the dot operator expression object.attribute can be implemented by your code too, for reference, assignment, and deletion contexts.  

### Attribute Reference 

  

## String Representation: `__repr__` and `__str__`  

As we’ve learned, the default display of instance objects for a class like this is neither generally useful nor aesthetically pretty:  

```python
>>> class adder:
        def __init__(self, value=0):
            self.data = value # Initialize data
        def __add__(self, other):
            self.data += other # Add other in place (bad form?)

>>> x = adder() # Default displays
>>> print(x)
<__main__.adder object at 0x00000000029736D8>
>>> x
<__main__.adder object at 0x00000000029736D8>
```

But coding or inheriting string representation methods allows us to customize the display—as in the following, which defines a `__repr__` method in a subclass that returns a string representation for its instances.  

```python
>>> class addrepr(adder): # Inherit __init__, __add__
        def __repr__(self): # Add string representation
            return 'addrepr(%s)' % self.data # Convert to as-code string

>>> x = addrepr(2) # Runs __init__
>>> x + 1 # Runs __add__ (x.add() better?)
>>> x # Runs __repr__
addrepr(3)
>>> print(x) # Runs __repr__
addrepr(3)
>>> str(x), repr(x) # Runs __repr__ for both
('addrepr(3)', 'addrepr(3)')
```

If defined, `__repr__` (or its close relative, `__str__`) is called automatically when class instances are printed or converted to strings. These methods allow you to define a better display format for your objects than the default instance display.  

In particular, Python provides two display methods to support alternative displays for different audiences:

- `__str__` is tried first for the print operation and the str built-in function (the internal equivalent of which print runs). It generally should return a user-friendly display.
- `__repr__` is used in all other contexts: for interactive echoes, the repr function, and nested appearances, as well as by print and str if no `__str__` is present. 

```python
>>> class addstr(adder):
        def __str__(self): # __str__ but no __repr__
            return '[Value: %s]' % self.data # Convert to nice string
>>> x = addstr(3)
>>> x + 1
>>> x # Default __repr__
<__main__.addstr object at 0x00000000029738D0>
>>> print(x) # Runs __str__
[Value: 4]
>>> str(x), repr(x)
('[Value: 4]', '<__main__.addstr object at 0x00000000029738D0>')

>>> class addboth(adder):
        def __str__(self):
            return '[Value: %s]' % self.data # User-friendly string
        def __repr__(self):
            return 'addboth(%s)' % self.data # As-code string
>>> x = addboth(4)
>>> x + 1
>>> x # Runs __repr__
addboth(5)
>>> print(x) # Runs __str__
[Value: 5]
>>> str(x), repr(x)
('[Value: 5]', 'addboth(5)')
```



## Call Expressions: `__call__`  

On to our next overloading method: the `__call__` method is called when your instance is called. No, this isn’t a circular definition—if defined, Python runs a `__call__` method for function call expressions applied to your instances, passing along whatever positional or keyword arguments were sent. This allows instances to conform to a functionbased API:  

```python
>>> class Callee:
        def __call__(self, *pargs, **kargs): # Intercept instance calls
            print('Called:', pargs, kargs) # Accept arbitrary arguments
>>> C = Callee()
>>> C(1, 2, 3) # C is a callable object
Called: (1, 2, 3) {}
>>> C(1, 2, 3, x=4, y=5)
Called: (1, 2, 3) {'y': 5, 'x': 4}
```

Intercepting call expression like this allows class instances to emulate the look and feel of things like functions, but also retain state information for use during calls.  

```python
>>> class Prod:
def __init__(self, value):
self.value = value
def comp(self, other):
return self.value * other
>>> x = Prod(3)
>>> x.comp(3)
9
>>> x.comp(4)
12
```



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

Rather than hardcoding the class name, the class method uses the automatically passed class object generically:  

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

```python
class Spam:
    numInstances = 0 # Trace class passed in
    def __init__(self):
        Spam.numInstances += 1
    def printNumInstances(cls):
        print("Number of instances: %s %s" % (cls.numInstances, cls))
    printNumInstances = classmethod(printNumInstances)

class Sub(Spam):
    def printNumInstances(cls): # Override a class method
        print("Extra stuff...", cls) # But call back to original
        Spam.printNumInstances()
    printNumInstances = classmethod(printNumInstances)

class Other(Spam): pass # Inherit class method verbatim

>>> from spam_class import Spam, Sub, Other
>>> x = Sub()
>>> y = Spam()
>>> x.printNumInstances() # Call from subclass instance
Extra stuff... <class 'spam_class.Sub'>
Number of instances: 2 <class 'spam_class.Spam'>
>>> Sub.printNumInstances() # Call from subclass itself
Extra stuff... <class 'spam_class.Sub'>
Number of instances: 2 <class 'spam_class.Spam'>
>>> y.printNumInstances() # Call from superclass instance
Number of instances: 2 <class 'spam_class.Spam'>
```

In the first call here, a class method call is made through an instance of the Sub subclass, and Python passes the lowest class, Sub, to the class method. All is well in this case—since Sub’s redefinition of the method calls the Spam superclass’s version explicitly, the superclass method in Spam receives its own class in its first argument. But watch what happens for an object that inherits the class method verbatim: 

```python
>>> z = Other() # Call from lower sub's instance
>>> z.printNumInstances()
Number of instances: 3 <class 'spam_class.Other'>
```

Counting instances per class with class methods

```python
class Spam:
    numInstances = 0
    def count(cls): # Per-class instance counters
        cls.numInstances += 1 # cls is lowest class above instance
    def __init__(self):
        self.count() # Passes self.__class__ to count
    count = classmethod(count)

class Sub(Spam):
    numInstances = 0
    def __init__(self): # Redefines __init__
        Spam.__init__(self)

class Other(Spam): # Inherits __init__
    numInstances = 0

>>> from spam_class2 import Spam, Sub, Other
>>> x = Spam()
>>> y1, y2 = Sub(), Sub()
>>> z1, z2, z3 = Other(), Other(), Other()
>>> x.numInstances, y1.numInstances, z1.numInstances # Per-class data!
(1, 2, 3)
>>> Spam.numInstances, Sub.numInstances, Other.numInstances
(1, 2, 3)
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

```python
def count(aClass):
    aClass.numInstances = 0
    return aClass # Return class itself, instead of a wrapper

@count
class Spam: ... # Same as Spam = count(Spam)

@count
class Sub(Spam): ... # numInstances = 0 not needed here

@count
class Other(Spam): ...
```

# ？？？

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



# 参考：

learning python （python学习手册）



