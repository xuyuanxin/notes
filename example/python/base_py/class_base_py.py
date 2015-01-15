#coding=utf-8
##################################################################################### 
############ self
#类的方法与普通的函数只有一个特别的区别——它们必须有一个额外的第一个参数名称，但是在调
#用这个方法的时候你不为这个参数赋值，Python会提供这个值。这个特别的变量指对象本身，按
#照惯例它的名称是self。虽然你可以给这个参数任何名称，但是 强烈建议 你使用self这个名称
#你一定很奇怪Python如何给self赋值以及为何你不需要给它赋值。举一个例子会使此变得清晰。
#假如你有一个类称为MyClass和这个类的一个实例MyObject。当你调用这个对象的方法
#        MyObject.method(arg1, arg2)
#的时候，这会由Python自动转为
#        MyClass.method(MyObject, arg1, arg2)
#这就是self的原理了。这也意味着如果你有一个不需要参数的方法，你还是得给这个方法定义一
#个self参数。
############ __init__
#__init__方法在类的一个对象被建立时，马上运行。这个方法可以用来对你的对象做一些你希望
#的初始化 。注意，这个名称的开始和结尾都是双下划线。

class Student(object):
    def __init__(self, name, score):
        self.name = name
        self.score = score
		
    def print_score(self):
        print '%s: %s' % (self.name, self.score)

bar = Student('bar',90)
bar.print_score()

#类的属性(类的变量)
#两种类型的域:
#    类的变量和对象的变量，它们根据是类还是对象 拥有这个变量而区分。
#类的变量:
#    由一个类的所有对象（实例）共享使用。只有一个类变量的拷贝，所以当某个对象对类的变
#    量做了改动的时候，这个改动会反映到所有其他的实例上。
#对象的变量
#    由类的每个对象/实例拥有。因此每个对象有自己对这个域的一份拷贝，即它们不是共享的，
#    在同一个类的不同实例中，虽然对象的变量有相同的名称，但是是互不相关的。
#通过一个例子会使这个易于理解。
class Person:
	'''Represents a person.'''
	population=0

#population属于Person类，因此是一个类的变量。name变量属于对象（它使用self赋值）因此是
#对象的变量。self.name的值根据每个对象指定，这表明了它作为对象的变量的本质。

	def __init__(self,name):
		'''Initializes the person's data.'''
		self.name=name
		print '(Initializing %s)' %self.name

		#When this person is created, he/she adds to the population
		Person.population+=1
	
	def __del__(self):
		'''I am dying.'''
		print '%s says bye.' %self.name

		Person.population-=1

		if Person.population==0:
			print 'I am the last one.'
		else:
			print 'There are still %d people left.' %Person.population
	
	def sayHi(self):
		'''Greeting by the person.

		Really, that's all it does.'''
		print 'Hi, my name is %s.' %self.name
	
	def howMany(self):
		'''Prints the current population.'''
		if Person.population==1:
			print 'I am the only person here.'
		else:
			print 'We have %d persons here.' %Person.population
#output:
#(Initializing Swaroop)
#Hi, my name is Swaroop.
#I am the only person here.
#(Initializing Abdul Kalam)
#Hi, my name is Abdul Kalam.
#We have 2 persons here.
#Hi, my name is Swaroop.
#We have 2 persons here.
#Abdul Kalam says bye.
#There are still 1 people left.
#Swaroop says bye.
#I am the last one.
 
swaroop=Person('Swaroop')
swaroop.sayHi()
swaroop.howMany()

kalam=Person('Abdul Kalam')
kalam.sayHi()
kalam.howMany()

swaroop.sayHi()
swaroop.howMany()


