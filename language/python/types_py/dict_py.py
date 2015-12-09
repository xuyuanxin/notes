# adfasdfasdfasdf

'''
In this chapter, you learn about a data structure in which you can refer to each val-
ue by name. This type of structure is called a mapping. The only built-in mapping ty-
pe in Python is the dictionary. The values in a dictionary don¡¯t have any  particular 
order but are stored under a key, which may be a number, a string, or even a tuple.

----> Creating and Using Dictionaries
Dictionaries are written like this:
phonebook = {'Alice': '2341', 'Beth': '9102', 'Cecil': '3258'}
Dictionaries consist of pairs (called items) of keys and their corresponding  values. 
In this example, the names are the keys and the telephone numbers are the values. Ea-
ch key is separated from its value by a colon (:), the items are separated by commas, 
and the whole thing is enclosed in curly braces. An empty dictionary (without any it-
ems) is written with just two curly braces, like this: {}. Keys are unique within a -
dictionary (and any other kind of mapping). Values do not need to be unique within  a 
dictionary.

----> The dict Function
You can use the @dict function to construct dictionaries from other mappings (for ex-
ample, other dictionaries) or from sequences of (key, value) pairs:
>>> items = [('name', 'Gumby'), ('age', 42)]
>>> d = dict(items)
>>> d
{'age': 42, 'name': 'Gumby'}
>>> d['name']
'Gumby'
It can also be used with keyword arguments, as follows:
>>> d = dict(name='Gumby', age=42)
>>> d
{'age': 42, 'name': 'Gumby'}

The @dict function isn¡¯t really a function at all. It is a type, just like @list,   -
@tuple, and @str.

----> Basic Dictionary Operations
The basic behavior of a dictionary in many ways mirrors that of a sequence:
| len(d)    returns the number of items (key-value pairs) in d.
| d[k]      returns the value associated with the key k.
| d[k] = v  associates the value v with the key k.
| del d[k]  deletes the item with key k.
| k in d    checks whether there is an item in d that has the key k.
Although dictionaries and lists share several common characteristics, there are  some
important distinctions:
Key types: 
    Dictionary keys don¡¯t have to be integers (though they may be). They may be any -
	immutable type, such as floating-point (real) numbers, strings, or tuples.
Automatic addition: 
    You can assign a value to a key, even if that key isn¡¯t in the dictionary to beg-
	in with; in that case, a new item will be created. You cannot assign a value to -
	an index outside the list¡¯s range (without using append or something like that).
Membership: 
    The expression "k in d" (where d is a dictionary) looks for a key, not a value. -
	The expression "v in l", on the other hand (where l is a list) looks for a value, 
	not an index.

'''

class dict():


'''
The @clear method removes all items from the dictionary. This is an in-place operati-
on (like list.sort), so it returns nothing (or, rather, None):
>>> d = {}
>>> d['name'] = 'Gumby'
>>> d['age'] = 42
>>> d
{'age': 42, 'name': 'Gumby'}
>>> returned_value = d.clear()
>>> d
{}
>>> print returned_value
None
'''
def clear():
    pass


  def copy():
    '''
    The @copy method returns a new dictionary with the same key-value pairs (a shallow c-
    opy, since the values themselves are the same, not copies):
    >>> x = {'username': 'admin', 'machines': ['foo', 'bar', 'baz']}
    >>> y = x.copy()
    >>> y['username'] = 'mlh'
    >>> y['machines'].remove('bar')
    >>> y
    {'username': 'mlh', 'machines': ['foo', 'baz']}
    >>> x
    {'username': 'admin', 'machines': ['foo', 'baz']}
    '''
    pass
	
'''
>>> from copy import deepcopy
>>> d = {}
>>> d['names'] = ['Alfred', 'Bertrand']
>>> c = d.copy()
>>> dc = deepcopy(d)
>>> d['names'].append('Clive')
>>> c
{'names': ['Alfred', 'Bertrand', 'Clive']}
>>> dc
{'names': ['Alfred', 'Bertrand']}
'''
def deepcopy():
    pass

'''
The @fromkeys method creates a new dictionary with the given keys, each with a defau-
lt corresponding value of None:
>>> {}.fromkeys(['name', 'age'])
{'age': None, 'name': None}
This example first constructs an empty dictionary and then calls the @fromkeys metho-
d on that, in order to create another dictionary¡ªa somewhat redundant strategy. Inst-
ead, you can call the method directly on dict, which (as mentioned before) is the ty-
pe of all dictionaries. (The concept of types and classes is discussed more thorough-
ly in Chapter 7.)
>>> dict.fromkeys(['name', 'age'])
{'age': None, 'name': None}
If you don¡¯t want to use None as the default value, you can supply your own default:
>>> dict.fromkeys(['name', 'age'], '(unknown)')
{'age': '(unknown)', 'name': '(unknown)'}
'''
def fromkeys():
    pass

'''
The @get method is a forgiving way of accessing dictionary items. Ordinarily, when y-
ou try to access an item that is not present in the dictionary, things go very wrong:
>>> d = {}
>>> print d['name']
Traceback (most recent call last):
File "<stdin>", line 1, in ?
KeyError: 'name'
Not so with get:
>>> print d.get('name')
None
As you can see, when you use get to access a nonexistent key, there is no  exception.
Instead, you get the value None. You may supply your own ¡°default¡± value, which is t-
hen used instead of None:
>>> d.get('name', 'N/A')
'N/A'
'''
def get():
    pass


  def setdefault(key[, default]):
    '''
	If key is in the dictionary, return its value. If not, insert key with a value of 
	default and return default. default defaults to None.
    '''
    pass

