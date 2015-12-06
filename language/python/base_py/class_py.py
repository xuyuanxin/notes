'''
----> 1 
---->====> 1.1
---->====>####> 1.1.1


----> Attributes, Functions, and Methods
The self parameter is, in fact, what distinguishes methods from functions. Methods (-
or, more technically, bound methods) have their first parameter bound to the instance 
they belong to, so you don’t have to supply it. While you can certainly bind an attr-
ibute to a plain function, it won’t have that special self parameter:
>>> class Class:
        def method(self):
            print 'I have a self!'
>>> def function():
print "I don't..."
>>> instance = Class()
>>> instance.method()
I have a self!
>>> instance.method = function
>>> instance.method()
I don't...
Note that the self parameter is not dependent on calling the method the way I’ve done
until now, as instance.method. You’re free to use another variable that refers to the 
same method:
>>> class Bird:
song = 'Squaawk!'
def sing(self):
print self.song
>>> bird = Bird()
>>> bird.sing()
Squaawk!
>>> birdsong = bird.sing
>>> birdsong()
Squaawk!
Even though the last method call looks exactly like a function call, the variable   -
birdsong refers to the bound method bird.sing, which means that it still has access -
to the self parameter (that is, it is still bound to the same instance of the class).

----> The Class Namespace
The following two statements are (more or less) equivalent:
    def foo(x): return x*x
    foo = lambda x: x*x
Both create a function that returns the square of its argument, and both bind the va-
riable foo to that function. The name foo may be defined in the global (module) scop-
e, or it may be local to some function or method. The same thing happens when you de-
fine a class: all the code in the class statement is executed in a special  namespace 
, the class namespace.This namespace is accessible later by all members of the class. 
Not all Python programmers know that class definitions are simply code sections  that 
are executed, but it can be useful information. For example, you aren’t restricted to 
def statements inside the class definition block:
>>> class C:
print 'Class C being defined...'
Class C being defined...
>>>
Okay, that was a bit silly. But consider the following:
class MemberCounter:
members = 0
def init(self):
MemberCounter.members += 1
>>> m1 = MemberCounter()
>>> m1.init()
>>> MemberCounter.members
1
>>> m2 = MemberCounter()
>>> m2.init()
>>> MemberCounter.members
2
In the preceding code, a variable is defined in the class scope, which can be access-
ed by all the members (instances), in this case to count the number of class members. 
Note the use of init to initialize all the instances: I’ll automate that (that is, t-
urn it into a proper constructor) in Chapter 9.
This class scope variable is accessible from every instance as well, just as  methods 
are:
>>> m1.members
2
>>> m2.members
2
What happens when you rebind the members attribute in an instance?
>>> m1.members = 'Two'
>>> m1.members
'Two'
>>> m2.members
2
The new members value has been written into an attribute in m1, shadowing the       -
class-wide variable. This mirrors the behavior of local and global variables in func-
tions, as discussed in the sidebar "The Problem of Shadowing" in Chapter 6.

----> Specifying a Superclass
subclasses expand on the definitions in their superclasses. You indicate the supercl-
ass in a class statement by writing it in parentheses after the class name:
class Filter:
    def init(self):
    self.blocked = []
    def filter(self, sequence):
        return [x for x in sequence if x not in self.blocked]

class SPAMFilter(Filter): # SPAMFilter is a subclass of Filter
    def init(self): # Overrides init method from Filter superclass
        self.blocked = ['SPAM']

Note two important points in the definition of SPAMFilter:
1 I override the definition of init from Filter by simply providing a new definition.
2 The definition of the filter method carries over (is inherited) from Filter, so yo-
  u don’t need to write the definition again.

>>> issubclass(SPAMFilter, Filter)
True
>>> issubclass(Filter, SPAMFilter)
False
>>> SPAMFilter.__bases__
(<class __main__.Filter at 0x171e40>,)
>>> Filter.__bases__
()
>>> s = SPAMFilter()
>>> isinstance(s, SPAMFilter)
True
>>> isinstance(s, Filter)
True
>>> isinstance(s, str)
False
>>> s.__class__
<class __main__.SPAMFilter at 0x1707c0>

----> Multiple Superclasses
classes:
    class Calculator:
        def calculate(self, expression):
        self.value = eval(expression)

class Talker:
    def talk(self):
        print 'Hi, my value is', self.value

class TalkingCalculator(Calculator, Talker):
    pass

The subclass (TalkingCalculator) does nothing by itself; it inherits all its behavior 
from its superclasses. The point is that it inherits both calculate from Calculator -
and talk from Talker, making it a talking calculator:
>>> tc = TalkingCalculator()
>>> tc.calculate('1+2*3')
>>> tc.talk()
Hi, my value is 7

This is called multiple inheritance, and can be a very powerful tool. However, unles-
s you know you need multiple inheritance, you may want to stay away from it, as it c-
an, in some cases, lead to unforeseen complications.
If you are using multiple inheritance, there is one thing you should look out for: i-
f a method is implemented differently by two or more of the superclasses (that is, y-
ou have two different methods with the same name), you must be careful about the ord-
er of these superclasses (in the class statement). The methods in the earlier classes 
override the methods in the later ones. So if the Calculator class in the preceding -
example had a method called talk, it would override (and make inaccessible) the  talk 
method of the Talker. Reversing their order,
like this:
class TalkingCalculator(Talker, Calculator): pass
would make the talk method of the Talker accessible. If the superclasses share a com-
mon superclass, the order in which the superclasses are visited while looking for a -
given attribute or method is called the method resolution order (MRO), and follows  a 
rather complicated algorithm. Luckily, it works very well, so you probably don’t need 
to worry about it.
  
+-----------------------------------------------------------------------------------+|
|-->-->-->-->-->-->-->-->-->-->-->-->      类 基础         <--<--<--<--<--<--<--<-- ||
+-----------------------------------------------------------------------------------+|
                                                                                     |
类是创建实例的模板，实例是具体的对象。                                               |
                                                                                     |
----> 1 通过class关键字定义类                                                        |
| class Student(object):                                                             |
|     pass	                                                                         |
class后是类名Student，类名通常是大写开头的单词。紧接着是(object)，表示该类是从哪个类 |
继承下来的，通常，如果没有合适的继承类，就使用object类，这是所有类最终都会继承的类。 |
创建实例是通过 类名+() 实现的                                                        |
bart = Student() #创建了一个类的实例bart                                             |
------------------------------------------------------------------------------------+|
----> 2 类的属性和方法                                                               |
self的概念(todo)                                                                     |
---->====> 2.1 属性：类中封装的变量 如下面的 name 、 score                           |
实例的变量名如果以__开头，就变成了一个私有变量（private），只有内部可以访问，外部不能|
访问。不能直接访问__name是因为Python解释器对外把__name变量改成了_Student__name，所以 |
，仍然可以通过_Student__name来访问__name变量：                                       |
* >>> bart._Student__name                                                            |
* 'Bart Simpson'                                                                     |
#变量名类似__xxx__的，是特殊变量，特殊变量是可以直接访问的，不是private变量。以一个下|
划线开头的实例变量名，比如_name表示虽然我可以被访问，但是，请把我视为私有变量，不要随|
意访问。                                                                             |
---->====> 2.2 方法：类中封装的函数 如下面的print_score                              |
------------------------------------------------------------------------------------+|
----> 3 创建实例的时候，可以初始化一些默认属性                                       |
通过定义一个特殊的__init__方法，在创建实例的时候，就把name，score等属性绑上去：      |
*  class Student(object):
*
*   def __init__(self, name, score):
*       self.name = name
*       self.score = score
*		
*   def print_score(self):
*       print '%s: %s' % (self.name, self.score)		                             |
__init__方法的第一个参数永远是self，表示创建的实例本身，因此，在__init__方法内部，就 |
可以把各种属性绑定到self，因为self就指向创建的实例本身。有了__init__方法，在创建实例 |
的时候，就不能传入空的参数了，必须传入与__init__方法匹配的参数，但self不需要传，     |		
* >>> bart = Student('Bart Simpson', 59)
* >>> bart.name
* 'Bart Simpson'
* >>> bart.score
* 59
* >>> bart.print_score()
* Bart Simpson: 59                                                                   |
Python允许对实例变量绑定任何数据，也就是说，对于两个实例变量，虽然它们都是同一个类的 |
不同实例，但拥有的变量名称都可能不同：                                               |
* >>> bart = Student('Bart Simpson', 59)
* >>> lisa=Student('Lisa Simpson', 87)
* >>> bart.age = 8
* >>> bart.age
* 8
* >>> lisa.age
* Traceback (most recent call last):
*   File "<stdin>", line 1, in <module>
* AttributeError: 'Student' object has no attribute 'age'
------------------------------------------------------------------------------------+|
----> 4 继承和多态                                                                   |
子类：定义一个class的时候，可以从某个现有的class继承，新的class称为子类(Subclass)子类|
      获得父类的全部功能，如果子类定义了相同的方法则覆盖父类的方法。
#     在继承关系中，如果一个实例的数据类型是某个子类，那它的数据类型也可以被看做是父类。但是，反过来就不行
#父类:被继承的class称为基类、父类或超类（Base class、Super class）。
#多态:有了继承，才能有多态。多态是指同一个方法在父类和子类中有不同的功能。
#     例如父类A定义了一个方法f,他的子类B和C分别重新定义了方法f.如果一个函数的入参是父类类型,此时子类也可以直接调用
#     子类B调用使用B中定义的方法,子类C调用使用C中定义的方法。
#************************************************************************************** 
#-->-->-->-->-->-->-->-->-->-->-->--> 5 动态添加属性和方法 <--<--<--<--<--<--<--<--<--*
#**************************************************************************************  
#正常情况下，当我们定义了一个class，创建了一个class的实例后，我们可以给该实例绑定任何属性和方法，这就是动态语言的灵活性。先定义class：
>>> class Student(object):
...     pass
...
#然后，尝试给实例绑定一个属性：
>>> s = Student()
>>> s.name = 'Michael' # 动态给实例绑定一个属性
>>> print s.name
Michael
#还可以尝试给实例绑定一个方法：
>>> def set_age(self, age): # 定义一个函数作为实例方法
...     self.age = age
...
>>> from types import MethodType
>>> s.set_age = MethodType(set_age, s, Student) # 给实例绑定一个方法
>>> s.set_age(25) # 调用实例方法
>>> s.age # 测试结果
25
#但是，给一个实例绑定的方法，对另一个实例是不起作用的：
>>> s2 = Student() # 创建新的实例
>>> s2.set_age(25) # 尝试调用方法
Traceback (most recent call last):
  File "<stdin>", line 1, in <module>
AttributeError: 'Student' object has no attribute 'set_age'
#为了给所有实例都绑定方法，可以给class绑定方法：
>>> def set_score(self, score):
...     self.score = score
...
>>> Student.set_score = MethodType(set_score, None, Student)
#给class绑定方法后，所有实例均可调用：
>>> s.set_score(100)
>>> s.score
100
>>> s2.set_score(99)
>>> s2.score
99
#************************************************************************************** 
#-->-->-->-->-->-->-->-->-->-->-->--> 6 限制类的属性和方法 <--<--<--<--<--<--<--<--<--*
#************************************************************************************** 
#如果我们想要限制class的属性怎么办？比如，只允许对Student实例添加name和age属性。
#为了达到限制的目的，Python允许在定义class的时候，定义一个特殊的__slots__变量，来限制该class能添加的属性：
>>> class Student(object):
...     __slots__ = ('name', 'age') # 用tuple定义允许绑定的属性名称
...
#然后，我们试试：
>>> s = Student() # 创建新的实例
>>> s.name = 'Michael' # 绑定属性'name'
>>> s.age = 25 # 绑定属性'age'
>>> s.score = 99 # 绑定属性'score'
Traceback (most recent call last):
  File "<stdin>", line 1, in <module>
AttributeError: 'Student' object has no attribute 'score'
#由于'score'没有被放到__slots__中，所以不能绑定score属性，试图绑定score将得到AttributeError的错误。
#使用__slots__要注意，__slots__定义的属性仅对当前类起作用，对继承的子类是不起作用的：
>>> class GraduateStudent(Student):
...     pass
...
>>> g = GraduateStudent()
>>> g.score = 9999
#除非在子类中也定义__slots__，这样，子类允许定义的属性就是自身的__slots__加上父类的__slots__。
#************************************************************************************** 
#-->-->-->-->-->-->-->-->-->-->--> 7 把方法变成属性@property <--<--<--<--<--<--<--<-- *
#************************************************************************************** 
#Python内置的@property装饰器就是负责把一个方法变成属性调用的：
class Student(object):

    @property
    def score(self):
        return self._score

    @score.setter
    def score(self, value):
        if not isinstance(value, int):
            raise ValueError('score must be an integer!')
        if value < 0 or value > 100:
            raise ValueError('score must between 0 ~ 100!')
        self._score = value
#@property的实现比较复杂，我们先考察如何使用。把一个getter方法变成属性，
#只需要加上@property就可以了，此时，@property本身又创建了另一个装饰器@score.setter，
#负责把一个setter方法变成属性赋值，于是，我们就拥有一个可控的属性操作：
>>> s = Student()
>>> s.score = 60 # OK，实际转化为s.set_score(60)
>>> s.score # OK，实际转化为s.get_score()
60
>>> s.score = 9999
Traceback (most recent call last):
  ...
ValueError: score must between 0 ~ 100!
#注意到这个神奇的@property，我们在对实例属性操作的时候，就知道该属性很可能不是直接暴露的，而是通过getter和setter方法来实现的。
#还可以定义只读属性，只定义getter方法，不定义setter方法就是一个只读属性：
class Student(object):

    @property
    def birth(self):
        return self._birth

    @birth.setter
    def birth(self, value):
        self._birth = value

    @property
    def age(self):
        return 2014 - self._birth
#上面的birth是可读写属性，而age就是一个只读属性，因为age可以根据birth和当前时间计算出来。
#
#
#
#
#

#
#
#
#
#
#
'''
