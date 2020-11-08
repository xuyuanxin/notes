http://my.oschina.net/syc2013/blog/333265?p=1   Python List���ݵı���

����б�
 del list[:]
 list=[]
 list[:]=[]

Python List���ݵı���
 app_list = [1234, 5677, 8899]
 for app_id in app_list:
     print app_id
 ����� 
 1234 
 5677 
 8899

 app_list = [1234, 5677, 8899]
 for index,app_id in enumerate(app_list):
     print index, app_id
 ����� 
 0 1234 
 1 5677 
 2 8899

 app_list = [1234, 5677, 8899]
 for i in range(len(app_list)):
     print i,app_list[i]
 ����� 
 0 1234 
 1 5677 
 2 8899

 app_list = [1234, 5677, 8899]
 for app_id in iter(app_list):
     print app_id
 ����� 
 1234 
 5677 
 8899


----> @list
@list actually a type, not a function, but the difference isn��t important right  now.
Because strings can��t be modified in the same way as lists, sometimes it can be usef-
ul to create a list from a string. You can do this with the list function:
>>> list('Hello')
['H', 'e', 'l', 'l', 'o']
Note that list works with all kinds of sequences, not just strings. To convert a lis-
t of characters back to a string, you would use the following expression:
''.join(somelist)
where @somelist is your list. 
>>> a=list('hello')
>>> a
['h', 'e', 'l', 'l', 'o']
>>> ''.join(a)
'hello'

1 Changing Lists: Item Assignments
You cannot assign to a position that doesn��t exist;
>>> x = [1, 1, 1]
>>> x[1] = 2 
>>> x
[1, 2, 1]

2 Deleting Elements
>>> names = ['Alice', 'Beth', 'Cecil', 'Dee-Dee', 'Earl']
>>> del names[2]
>>> names
['Alice', 'Beth', 'Dee-Dee', 'Earl']

3 Assigning to Slices
>>> name = list('Perl')
>>> name
['P', 'e', 'r', 'l']
>>> name[2:] = list('ar')
>>> name
['P', 'e', 'a', 'r']

>>> name = list('Perl')      # replace the slice with a sequence whose length is dif-
>>> name[1:] = list('ython') # ferent from that of the original:                      
>>> name
['P', 'y', 't', 'h', 'o', 'n']

>>> numbers = [1, 5]         # Slice assignments can even be used to insert  elements 
>>> numbers[1:1] = [2, 3, 4] # without replacing any of the original ones:
>>> numbers
[1, 2, 3, 4, 5]
>>> numbers[1:4] = []
>>> numbers
[1, 5]

----> List Methods
In general, a method is called like this:
object.method(arguments)
As you can see, a method call looks just like a function call, except that the object 
is put before the method name, with a dot separating them.

1 append
The append method is used to append an object to the end of a list:
>>> lst = [1, 2, 3]
>>> lst.append(4)
>>> lst
[1, 2, 3, 4]
It��s also important to note that append, like several similar methods, changes the l-
ist in place. This means that it does not simply return a new, modified list;instead, 
it modifies the old one directly. 

2 count
The count method counts the occurrences of an element in a list:
>>> ['to', 'be', 'or', 'not', 'to', 'be'].count('to')
2
>>> x = [[1, 2], 1, 1, [2, 1, [1, 2]]]
>>> x.count(1)
2
>>> x.count([1, 2])
1

3 extend
The extend method allows you to append several values at once by supplying a sequence 
of the values you want to append. In other words, your original list has been extend-
ed by the other one:
>>> a = [1, 2, 3]
>>> b = [4, 5, 6]
>>> a.extend(b)
>>> a
[1, 2, 3, 4, 5, 6]
This may seem similar to concatenation, but the important difference is that the ext-
ended sequence (in this case, a) is modified. This is not the case in ordinary conca-
tenation, in which a completely new sequence is returned:
>>> a = [1, 2, 3]
>>> b = [4, 5, 6]
>>> a + b
[1, 2, 3, 4, 5, 6]
>>> a
[1, 2, 3]

4 index
The index method is used for searching lists to find the index of the first occurren-
ce of a value:
>>> knights = ['We', 'are', 'the', 'knights', 'who', 'say', 'ni']
>>> knights.index('who')
4
>>> knights.index('herring')
Traceback (innermost last):
File "<pyshell#76>", line 1, in ?
knights.index('herring')
ValueError: list.index(x): x not in list

5 insert
The insert method is used to insert an object into a list:
>>> numbers = [1, 2, 3, 5, 6, 7]
>>> numbers.insert(3, 'four')
>>> numbers
[1, 2, 3, 'four', 5, 6, 7]
As with extend, you can implement insert with slice assignments:
>>> numbers = [1, 2, 3, 5, 6, 7]
>>> numbers[3:3] = ['four']
>>> numbers
[1, 2, 3, 'four', 5, 6, 7]

6 pop
The pop method removes an element (by default, the last one) from the list and returns it:
>>> x = [1, 2, 3]
>>> x.pop()
3
>>> x
[1, 2]
>>> x.pop(0)
1
>>> x
[2]

7 remove
The remove method is used to remove the first occurrence of a value:
>>> x = ['to', 'be', 'or', 'not', 'to', 'be']
>>> x.remove('be')
>>> x
['to', 'or', 'not', 'to', 'be']
>>> x.remove('bee')
Traceback (innermost last):
File "<pyshell#3>", line 1, in ?
x.remove('bee')
ValueError: list.remove(x): x not in list
As you can see, only the first occurrence is removed, and you cannot remove somethin-
g (in this case, the string 'bee') if it isn��t in the list to begin with. It��s impor-
tant to note that this is one of the ��nonreturning in-place changing�� methods. It mo-
difies the list, but returns nothing.

8 reverse
The @reverse method reverses the elements in the list. 
>>> x = [1, 2, 3]
>>> x.reverse()
>>> x
[3, 2, 1]
Note that reverse changes the list and does not return anything. If you want to iter-
ate over a sequence in reverse, you can use the @reversed function. This function do-
esn��t return a list, though; it returns an iterator. You can convert the returned ob-
ject with @list:
>>> x = [1, 2, 3]
>>> list(reversed(x))
[3, 2, 1]

9 sort (returns nothing)
>>> x = [4, 6, 2, 1, 7, 9]
>>> x.sort()
>>> x
[1, 2, 4, 6, 7, 9]

>>> x = [4, 6, 2, 1, 7, 9]
>>> y = x.sort() # Don't do this!
>>> print y
None

>>> x = [4, 6, 2, 1, 7, 9]
>>> y = sorted(x)
>>> x
[4, 6, 2, 1, 7, 9]
>>> y
[1, 2, 4, 6, 7, 9]






----> Sequence Overview
Python has a basic notion of a kind of data structure called a container, which is b-
asically any object that can contain other objects. The two main kinds of  containers 
are sequences (such as lists and tuples) and mappings (such as dictionaries). While -
the elements of a sequence are numbered, each element in a mapping has a name (also -
called a key). For an example of a container type that is neither a sequence nor a  -
mapping, see the discussion of @sets in Chapter 10.

Python has six built-in types of sequences : lists, tuples, strings, Unicode strings,
buffer objects, and xrange objects. 

----> Common Sequence Operations
1 Indexing
All elements in a sequence are numbered -- from zero and upwards. When you use a neg-
ative index, Python counts from the right; that is, from the last element. The last -
element is at position �C1. [first, last)
>>> greeting = 'Hello'  # A string is just a sequence of characters. The index 0 ref-
                        # ers to the first element, in this case the letter H.
>>> greeting[0]
'H'
>>> greeting[-1]
'o'

String literals (and other sequence literals, for that matter) may be indexed direct-
ly, without using a variable to refer to them. The effect is exactly the same:
>>> 'Hello'[1]
'e'
If a function call returns a sequence, you can index it directly. For instance, if y-
ou are simply interested in the fourth digit in a year entered by the user, you could 
do something like this:
>>> fourth = raw_input('Year: ')[3]
Year: 2005
>>> fourth
'5'

2 Adding Sequences
Sequences can be concatenated with the addition (plus) operator. In general, you can-
not concatenate sequences of different types.
>>> [1, 2, 3] + [4, 5, 6]
[1, 2, 3, 4, 5, 6]
>>> 'Hello, ' + 'world!'
'Hello, world!'
>>> [1, 2, 3] + 'world!'
Traceback (innermost last):
File "<pyshell#2>", line 1, in ?
[1, 2, 3] + 'world!'
TypeError: can only concatenate list (not "string") to list

3 Multiplication
Multiplying a sequence by a number x creates a new sequence where the original seque-
nce is repeated x times:
>>> 'python' * 5
'pythonpythonpythonpythonpython'
>>> [42] * 10
[42, 42, 42, 42, 42, 42, 42, 42, 42, 42]

4 None, Empty Lists, and Initialization
An empty list is simply written as two brackets ([])��there��s nothing in it. But  what 
if you want to have a list with room for ten elements but with nothing useful in  it? 
You could use [42]*10, as before, or perhaps more realistically [0]*10. You now  have 
a list with ten zeros in it. Sometimes, however, you would like a value that  somehow 
means "nothing," as in "we haven��t put anything here yet." That��s when you use  None. 
None is a Python value and means exactly that��"nothing here." So if you want to init-
ialize a list of length 10, you could do the following:
>>> sequence = [None] * 10
>>> sequence
[None, None, None, None, None, None, None, None, None, None]

5 Membership
To check whether a value can be found in a sequence, you use the @in operator. It ch-
ecks whether something is true and returns a value accordingly: True for true and   -
False for false. 
>>> permissions = 'rw'
>>> 'w' in permissions
True
>>> 'x' in permissions
False
>>> users = ['mlh', 'foo', 'bar']
>>> raw_input('Enter your user name: ') in users
Enter your user name: mlh
True
>>> subject = '$$$ Get rich now!!! $$$'
>>> '$$$' in subject
True

In general, the @in operator checks whether an object is a member (that is, an eleme-
nt) of a sequence (or some other collection). However, the only members or elements -
of a string are its characters. So, the following makes perfect sense:
>>> 'P' in 'Python'
True

6 Length, Minimum, and Maximum
The built-in functions @len, @min, and @max can be quite useful. The function @len r-
eturns the number of elements a sequence contains. @min and @max return the  smallest 
and largest element of the sequence, respectively.
>>> numbers = [100, 34, 678]
>>> len(numbers)
3
>>> max(numbers)
678
>>> min(numbers)
34
>>> max(2, 3)
3
>>> min(9, 3, 2, 5)
2

7 Slicing
you can use slicing to access ranges of elements. You do this by using two indices, -
separated by a colon. The first index is the number of the first element you want  to 
include. However, the last index is the number of the first element after your slice.
>>> numbers = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10]
>>> numbers[3:6]
[4, 5, 6]
>>> numbers[0:1]
[1]

the leftmost index in a slice comes later in the sequence than the second one, the r-
esult is always an empty sequence.
>>> numbers[-3:0]
[]

if the slice continues to the end of the sequence, you may simply leave out the  last 
index:
>>> numbers[-3:]
[8, 9, 10]
The same thing works from the beginning:
>>> numbers[:3]
[1, 2, 3]

if you want to copy the entire sequence, you may leave out both indices:
>>> numbers[:]
[1, 2, 3, 4, 5, 6, 7, 8, 9, 10]

In a regular slice, the step length is one, which means that the slice ��moves�� from -
one element to the next, returning all the elements between the start and end:
>>> numbers[0:10:1]
[1, 2, 3, 4, 5, 6, 7, 8, 9, 10]
If the step size is set to a number greater than one, elements will be skipped. For -
example,
>>> numbers[0:10:2]
[1, 3, 5, 7, 9]
>>> numbers[::4]
[1, 5, 9]
for a positive step size, it moves from the beginning toward the end, and for a nega-
tive step size, it moves from the end toward the beginning.
>>> numbers[8:3:-1]
[9, 8, 7, 6, 5]
>>> numbers[10:0:-2]
[10, 8, 6, 4, 2]
>>> numbers[0:10:-2]
[]
>>> numbers[::-2]
[10, 8, 6, 4, 2]
>>> numbers[5::-2]
[6, 4, 2]
>>> numbers[:5:-2] # numbers = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10]
[10, 8]

As you can see, the first limit (the leftmost) is still inclusive, while the second -
(the rightmost) is exclusive. When using a negative step size, you need to have a fi-
rst limit (start index) that is higher than the second one. What may be a bit confus-
ing is that when you leave the start and end indices implicit, Python does the "right 
thing", for a positive step size, it moves from the beginning toward the end, and for
a negative step size, it moves from the end toward the beginning.


	
