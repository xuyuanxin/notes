

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