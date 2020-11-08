

def sorted(iterable[, cmp[, key[, reverse]]]):
  '''
  '''
  pass



################################################################################
#Python内置的sorted()函数
>>> sorted([36, 5, 12, 9, 21])
[5, 9, 12, 21, 36]
#sorted()函数也是一个高阶函数，它还可以接收一个比较函数来实现自定义的排序。比如，
#如果要倒序排序，我们就可以自定义一个reversed_cmp函数：
def reversed_cmp(x, y):
    if x > y:
        return -1
    if x < y:
        return 1
    return 0
#传入自定义的比较函数reversed_cmp，就可以实现倒序排序：
>>> sorted([36, 5, 12, 9, 21], reversed_cmp)
[36, 21, 12, 9, 5]

#我们再看一个字符串排序的例子：
>>> sorted(['about', 'bob', 'Zoo', 'Credit'])
['Credit', 'Zoo', 'about', 'bob']
#默认情况下，对字符串排序，是按照ASCII的大小比较的，由于'Z' < 'a'，结果，大写字
#母Z会排在小写字母a的前面。现在，我们提出排序应该忽略大小写，按照字母序排序。要
#实现这个算法，不必对现有代码大加改动，只要我们能定义出忽略大小写的比较算法就可
#以：
def cmp_ignore_case(s1, s2):
    u1 = s1.upper()
    u2 = s2.upper()
    if u1 < u2:
        return -1
    if u1 > u2:
        return 1
    return 0
#忽略大小写来比较两个字符串，实际上就是先把字符串都变成大写（或者都变成小写），
#再比较。这样，我们给sorted传入上述比较函数，即可实现忽略大小写的排序：
>>> sorted(['about', 'bob', 'Zoo', 'Credit'], cmp_ignore_case)
['about', 'bob', 'Credit', 'Zoo']
