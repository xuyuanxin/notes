

yield
 http://www.ibm.com/developerworks/cn/opensource/os-cn-python-yield/
 �嵥 5. ʹ�� yield �ĵ��İ�
  def fab(max): 
     n, a, b = 0, 0, 1 
     while n < max: 
         yield b 
         # print b 
         a, b = b, a + b 
         n = n + 1 
                                                                                     |
 ���ĸ��汾�� fab �͵�һ����ȣ������� print b ��Ϊ�� yield b�����ڱ��ּ���Ե�ͬʱ��|
 ���� iterable ��Ч�������õ��İ�� fab �͵ڶ���� fab ��ȫһ�£�
 >>> for n in fab(5): 
 ...     print n 
 ... 
 1 
 1 
 2 
 3 
 5
 �򵥵ؽ���yield �����þ��ǰ�һ���������һ�� generator������ yield �ĺ���������һ�� |
 ��ͨ������Python �������Ὣ����Ϊһ�� generator������ fab(5) ����ִ�� fab ����������|
 ����һ�� iterable ������ for ѭ��ִ��ʱ��ÿ��ѭ������ִ�� fab �����ڲ��Ĵ��룬ִ��|
 �� yield b ʱ��fab �����ͷ���һ������ֵ���´ε���ʱ������� yield b ����һ��������|
 ִ�У��������ı��ر������������ϴ��ж�ִ��ǰ����ȫһ���ģ����Ǻ�������ִ�У�ֱ���ٴ�|
 ���� yield��Ҳ�����ֶ����� fab(5) �� next() ��������Ϊ fab(5) ��һ�� generator ���� |
 ���ö������ next() ���������������ǾͿ��Ը�����ؿ��� fab ��ִ�����̣�
 �嵥 6. ִ������
 >>> f = fab(5) 
 >>> f.next() 
 1 
 >>> f.next() 
 1 
 >>> f.next() 
 2 
 >>> f.next() 
 3 
 >>> f.next() 
 5 
 >>> f.next() 
 Traceback (most recent call last): 
  File "<stdin>", line 1, in <module> 
 StopIteration
 ������ִ�н���ʱ��generator �Զ��׳� StopIteration �쳣����ʾ������ɡ��� for ѭ���� |
 �����账�� StopIteration �쳣��ѭ�����������������ǿ��Եó����½��ۣ�
 һ������ yield �ĺ�������һ�� generator��������ͨ������ͬ������һ�� generator ������ |
 �������ã�������ִ���κκ������룬ֱ��������� next()���� for ѭ���л��Զ�����     |
 next()���ſ�ʼִ�С���Ȼִ�������԰�����������ִ�У���ÿִ�е�һ�� yield ���ͻ��ж�|
 ��������һ������ֵ���´�ִ��ʱ�� yield ����һ��������ִ�С��������ͺ���һ����������|
 ��ִ�еĹ����б� yield �ж������Σ�ÿ���ж϶���ͨ�� yield ���ص�ǰ�ĵ���ֵ��
 yield �ĺô����Զ��׼��ģ���һ��������дΪһ�� generator �ͻ���˵������������������|
 ʵ������״̬��������һ�� next() ��ֵ�����������࣬����ִ�������쳣������
 ����ж�һ�������Ƿ���һ������� generator �������������� isgeneratorfunction �жϣ�
 �嵥 7. ʹ�� isgeneratorfunction �ж�
 >>> from inspect import isgeneratorfunction 
 >>> isgeneratorfunction(fab) 
 True
 Ҫע������ fab �� fab(5)��fab ��һ�� generator function���� fab(5) �ǵ��� fab ���ص� |
 һ�� generator���ñ���Ķ�������ʵ��������
 �嵥 8. ��Ķ�������ʵ��
 >>> import types 
 >>> isinstance(fab, types.GeneratorType) 
 False 
 >>> isinstance(fab(5), types.GeneratorType) 
 True
 fab ���޷������ģ��� fab(5) �ǿɵ����ģ�
 >>> from collections import Iterable 
 >>> isinstance(fab, Iterable) 
 False 
 >>> isinstance(fab(5), Iterable) 
 True
 ÿ�ε��� fab ������������һ���µ� generator ʵ������ʵ������Ӱ�죺
 >>> f1 = fab(3) 
 >>> f2 = fab(5) 
 >>> print 'f1:', f1.next() 
 f1: 1 
 >>> print 'f2:', f2.next() 
 f2: 1 
 >>> print 'f1:', f1.next() 
 f1: 1 
 >>> print 'f2:', f2.next() 
 f2: 1 
 >>> print 'f1:', f1.next() 
 f1: 2 
 >>> print 'f2:', f2.next() 
 f2: 2 
 >>> print 'f2:', f2.next() 
 f2: 3 
 >>> print 'f2:', f2.next() 
 f2: 5
                                                                                     |
 return ������ 
 ��һ�� generator function �У����û�� return����Ĭ��ִ����������ϣ������ִ�й��� |
 �� return����ֱ���׳� StopIteration ��ֹ������
 
 
 
 
 
 
