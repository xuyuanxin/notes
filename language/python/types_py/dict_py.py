'''
The only built-in mapping type in Python is the dictionary. The values in a dictiona-
ry don¡¯t have any particular order but are stored under a key, which may be a number, 
a string, or even a tuple.

Dictionaries are written like this:
phonebook = {'Alice': '2341', 'Beth': '9102', 'Cecil': '3258'}
Dictionaries consist of pairs (called items) of keys and their corresponding  values. 
In this example, the names are the keys and the telephone numbers are the values. Ea-
ch key is separated from its value by a colon (:), the items are separated by commas, 
and the whole thing is enclosed in curly braces. An empty dictionary (without any it-
ems) is written with just two curly braces, like this: {}. Keys are unique within a -
dictionary (and any other kind of mapping). Values do not need to be unique within  a 
dictionary.

The dict Function
You can use the dict function to construct dictionaries from other mappings (for exa-
mple, other dictionaries) or from sequences of (key, value) pairs:
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
? len(d) returns the number of items (key-value pairs) in d.
? d[k] returns the value associated with the key k.
? d[k] = v associates the value v with the key k.
? del d[k] deletes the item with key k.
? k in d checks whether there is an item in d that has the key k.
Although dictionaries and lists share several common characteristics, there are some
important distinctions:
Key types: Dictionary keys don¡¯t have to be integers (though they may be). They may be
any immutable type, such as floating-point (real) numbers, strings, or tuples.
Automatic addition: You can assign a value to a key, even if that key isn¡¯t in the dictionary
to begin with; in that case, a new item will be created. You cannot assign a value to an
index outside the list¡¯s range (without using append or something like that).
Membership: The expression k in d (where d is a dictionary) looks for a key, not a value.
The expression v in l, on the other hand (where l is a list) looks for a value, not an index.

'''






