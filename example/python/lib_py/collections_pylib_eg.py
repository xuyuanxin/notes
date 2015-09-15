#_*_coding:UTF-8_*_
'''

'''
 
from collections import Counter

def Counter_test():
    c1 = Counter()                           # a new, empty counter
    c2 = Counter('gallahad')                 # a new counter from an iterable
    c3 = Counter({'red': 4, 'blue': 2})      # a new counter from a mapping
    c4 = Counter(cats=4, dogs=8)             # a new counter from keyword args
    print c1
    print c2
    print c3
    print c4

	
Counter_test()