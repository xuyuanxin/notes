#_*_coding:UTF-8_*_

'''
因为错误是class，捕获一个错误就是捕获到该class的一个实例。因此，错误并不是凭空产生的 |
，而是有意创建并抛出的。Python的内置函数会抛出很多类型的错误，我们自己编写的函数也可 |
以抛出错误。如果要抛出错误，首先根据需要，可以定义一个错误的class，选择好继承关系，然|
后，用raise语句抛出一个错误的实例：                                                  |

执行，可以最后跟踪到我们自己定义的错误：

$ python err.py
Traceback (most recent call last):
  ...
__main__.FooError: invalid value: 0
                                                                                     |
只有在必要的时候才定义我们自己的错误类型。如果可以选择Python已有的内置的错误类型（比 |
如ValueError，TypeError），尽量使用Python内置的错误类型。
'''
# err.py
class FooError(StandardError):
    pass

def foo(s):
    n = int(s)
    if n==0:
        raise FooError('invalid value: %s' % s)
    return 10 / n

foo(0)
