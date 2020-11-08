'''
1 thread_pylib_eg.py

This module provides low-level primitives for working with multiple threads (also ca-
lled light-weight processes or tasks) �� multiple threads of control sharing their gl-
obal data space.

Pythonͨ��������׼��thread��threading�ṩ���̵߳�֧�֡�thread�ṩ�˵ͼ���ġ�ԭʼ���߳��Լ�һ���򵥵�����
thread ģ���ṩ������������
threading.currentThread(): ���ص�ǰ���̱߳�����
threading.enumerate(): ����һ�������������е��̵߳�list����������ָ�߳������󡢽���ǰ������������ǰ����ֹ����̡߳�
threading.activeCount(): �����������е��߳���������len(threading.enumerate())����ͬ�Ľ����
����ʹ�÷����⣬�߳�ģ��ͬ���ṩ��Thread���������̣߳�Thread���ṩ�����·���:
run(): ���Ա�ʾ�̻߳�ķ�����
start():�����̻߳��
join([time]): �ȴ����߳���ֹ�������������߳�ֱ���̵߳�join() ������������ֹ-�����˳������׳�δ������쳣-�����ǿ�ѡ�ĳ�ʱ������
isAlive(): �����߳��Ƿ��ġ�
getName(): �����߳�����
setName(): �����߳�����
'''



def start_new_thread(function, args[, kwargs])
   '''thread.start_new_thread
   Start a new thread and return its identifier. The thread executes the function   -
   @function with the argument list args (which must be a tuple). The optional kwargs 
   argument specifies a dictionary of keyword arguments. When the function returns, -
   the thread silently exits. When the function terminates with an unhandled excepti-
   on, a stack trace is printed and then the thread exits (but other threads continu-
   e to run).
   '''