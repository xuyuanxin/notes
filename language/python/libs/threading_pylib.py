'''
Python 多线程 http://www.runoob.com/python/python-multithreading.html
Python多线程学习 http://www.cnblogs.com/tqsummer/archive/2011/01/25/1944771.html

Python实例浅谈之五Python守护进程和脚本单例运行 http://blog.csdn.net/taiyang1987912/article/details/44850999
[Python]守护进程daemon http://www.cnblogs.com/gmark/archive/2012/09/27/2706339.html
Python爬虫(四)--多线程 http://www.jianshu.com/p/86b8e78c418a?search_token=4d8e9a843325f3abd4be64fb668ec7812f760bc1f9aa7b10431fa8966453a868

Python实例浅谈之五Python守护进程和脚本单例运行 http://blog.csdn.net/taiyang1987912/article/details/44850999
'''

''' threading
This module constructs higher-level threading interfaces on top of the lower level  -
@thread module. The @dummy_threading module is provided for situations where        -
@threading cannot be used because @thread is missing.


Another reason to avoid using the thread module is that it does not support the conc-
ept of daemon (or daemonic) threads. When the main thread exits, all child threads w-
ill be killed, regardless of whether they are doing work. The concept of daemon thre-
ads comes into play here if you do not desire this behavior. A new child thread inhe-
rits its daemonic flag from its parent. The entire Python program ( read as: the main 
thread) will stay alive until all non-daemonic threads have exited, in other words, -
when no active non-daemonic threads are left.


'''



class Thread: # threading.Thread
    '''
	This class represents an activity that is run in a separate thread of control. T-
	here are two ways to specify the activity: by passing a callable object to the c-
	onstructor, or by overriding the run() method in a subclass. No other methods (e-
	xcept for the constructor) should be overridden in a subclass. In other words, o-
	nly override the __init__() and run() methods of this class.
	
    Thread object data attributes
    name        The name of a thread.
    ident       The identifier of a thread.
    daemon      Boolean flag indicating whether a thread is daemonic.	
	'''

    def Thread(group=None, target=None, name=None, args=(), kwargs={})
	    '''def __init__(self, group=None, target=None, name=None,args=(), 
		                kwargs=None, verbose=None):
	    This constructor should always be called with keyword arguments. Arguments a-
		re:
		@group 
		  should be None; reserved for future extension when a ThreadGroup class is -
		  implemented.
        @target 
		  is the callable object to be invoked by the run() method. Defaults to None, 
		  meaning nothing is called.
        @name 
		  is the thread name. By default, a unique name is constructed of the form  -
		  "Thread-N" where N is a small decimal number.
        @args 
		  is the argument tuple for the target invocation. Defaults to ().
        @kwargs 
		  is a dictionary of keyword arguments for the target invocation. Defaults t-
		  o {}.
        If the subclass overrides the constructor, it must make sure to invoke the b-
		ase class constructor (Thread.__init__()) before doing anything else to the -
		thread.
	    '''

  def join(self, timeout=None):
    '''
    Wait until the thread terminates. This blocks the calling thread until the thread 
    whose join() method is called terminates (either normally or through an unhandled 
	exception) or until the optional @timeout occurs.

    When the @timeout argument is present and not None, it should be a floating point 
	number specifying a timeout for the operation in seconds (or fractions thereof ). 
	As join() always returns None, you must call isAlive() after join() to decide wh-
	ether a timeout happened,if the thread is still alive, the join() call timed out.

    When the timeout argument is not present or None, the operation will block  until 
	the thread terminates. A thread can be join()ed many times. join() raises a     -
	RuntimeError if an attempt is made to join the current thread as that would cause 
	a deadlock. It is also an error to join() a thread before it has been started and 
	attempts to do so raises the same exception.	
	'''

  def start(self):
    """Start the thread's activity.
    It must be called at most once per thread object.It arranges for the object's   -
	run() method to be invoked in a separate thread of control. This method  will ra-
	ise a RuntimeError if called more than once on the same thread object.
    """	
	
