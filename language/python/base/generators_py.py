

yield
 http://www.ibm.com/developerworks/cn/opensource/os-cn-python-yield/
 清单 5. 使用 yield 的第四版
  def fab(max): 
     n, a, b = 0, 0, 1 
     while n < max: 
         yield b 
         # print b 
         a, b = b, a + b 
         n = n + 1 
                                                                                     |
 第四个版本的 fab 和第一版相比，仅仅把 print b 改为了 yield b，就在保持简洁性的同时获|
 得了 iterable 的效果。调用第四版的 fab 和第二版的 fab 完全一致：
 >>> for n in fab(5): 
 ...     print n 
 ... 
 1 
 1 
 2 
 3 
 5
 简单地讲，yield 的作用就是把一个函数变成一个 generator，带有 yield 的函数不再是一个 |
 普通函数，Python 解释器会将其视为一个 generator，调用 fab(5) 不会执行 fab 函数，而是|
 返回一个 iterable 对象！在 for 循环执行时，每次循环都会执行 fab 函数内部的代码，执行|
 到 yield b 时，fab 函数就返回一个迭代值，下次迭代时，代码从 yield b 的下一条语句继续|
 执行，而函数的本地变量看起来和上次中断执行前是完全一样的，于是函数继续执行，直到再次|
 遇到 yield。也可以手动调用 fab(5) 的 next() 方法（因为 fab(5) 是一个 generator 对象 |
 ，该对象具有 next() 方法），这样我们就可以更清楚地看到 fab 的执行流程：
 清单 6. 执行流程
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
 当函数执行结束时，generator 自动抛出 StopIteration 异常，表示迭代完成。在 for 循环里 |
 ，无需处理 StopIteration 异常，循环会正常结束。我们可以得出以下结论：
 一个带有 yield 的函数就是一个 generator，它和普通函数不同，生成一个 generator 看起来 |
 像函数调用，但不会执行任何函数代码，直到对其调用 next()（在 for 循环中会自动调用     |
 next()）才开始执行。虽然执行流程仍按函数的流程执行，但每执行到一个 yield 语句就会中断|
 ，并返回一个迭代值，下次执行时从 yield 的下一个语句继续执行。看起来就好像一个函数在正|
 常执行的过程中被 yield 中断了数次，每次中断都会通过 yield 返回当前的迭代值。
 yield 的好处是显而易见的，把一个函数改写为一个 generator 就获得了迭代能力，比起用类的|
 实例保存状态来计算下一个 next() 的值，不仅代码简洁，而且执行流程异常清晰。
 如何判断一个函数是否是一个特殊的 generator 函数？可以利用 isgeneratorfunction 判断：
 清单 7. 使用 isgeneratorfunction 判断
 >>> from inspect import isgeneratorfunction 
 >>> isgeneratorfunction(fab) 
 True
 要注意区分 fab 和 fab(5)，fab 是一个 generator function，而 fab(5) 是调用 fab 返回的 |
 一个 generator，好比类的定义和类的实例的区别：
 清单 8. 类的定义和类的实例
 >>> import types 
 >>> isinstance(fab, types.GeneratorType) 
 False 
 >>> isinstance(fab(5), types.GeneratorType) 
 True
 fab 是无法迭代的，而 fab(5) 是可迭代的：
 >>> from collections import Iterable 
 >>> isinstance(fab, Iterable) 
 False 
 >>> isinstance(fab(5), Iterable) 
 True
 每次调用 fab 函数都会生成一个新的 generator 实例，各实例互不影响：
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
 return 的作用 
 在一个 generator function 中，如果没有 return，则默认执行至函数完毕，如果在执行过程 |
 中 return，则直接抛出 StopIteration 终止迭代。
 
 
 
 
 
 
