

def domains_init(dwhite=False):
    if False != dwhite:
        dwhite.setdefault('a.com','w')
    else:
        print('dict is None')

def domains_test():
    white1 = dict()
    domains_init(dwhite=white1)
    print('white1:%s'%white1)


domains_test()


def tracer(func, *pargs, **kargs):         # Accept arbitrary arguments
    print('calling:', func.__name__)
    return func(*pargs, **kargs)           # Pass along arbitrary arguments

def func(a, b, c, d):
    return a + b + c + d

print(tracer(func, 1, 2, c=3, d=4))