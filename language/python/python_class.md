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





## 参考：

learning python （python学习手册）



