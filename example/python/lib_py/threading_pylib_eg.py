#!/usr/bin/python
# -*- coding: UTF-8 -*-

import threading
import time

exitFlag = 0

def print_time(threadName, delay, counter):
    while counter:
        if exitFlag:
            thread.exit()
        time.sleep(delay)
        print "%s: %s\n" % (threadName, time.ctime(time.time()))
        counter -= 1
		
class myThread (threading.Thread):   #继承父类threading.Thread
    def __init__(self, threadID, name, counter):
        threading.Thread.__init__(self)
        self.threadID = threadID
        self.name = name
        self.counter = counter
    def run(self):                   #把要执行的代码写到run函数里面 线程在创建后会直接运行run函数 
        print "Starting " + self.name + '\n'
        print_time(self.name, 1, self.counter)
        print "Exiting " + self.name + '\n'

# 创建新线程
thread1 = myThread(1, "Thread-1", 1)
thread2 = myThread(2, "Thread-2", 2)

# 开启线程
thread1.start()
thread2.start()

time.sleep(3)
print "Exiting Main Thread\n"