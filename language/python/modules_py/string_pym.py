'''
----> String Formatting
To the left of the %, you place a string (the format string); to the right of it, yo-
u place the value you want to format. You can use a single value such as a string  or 
a number, you can use a tuple of values (if you want to format more than one), or, d-
ictionary. The most common case is the tuple. If you use a list or some other sequen-
ce instead of a tuple, the sequence will be interpreted as a single value. Only     -
tuples and dictionaries will allow you to format more than one value.
'''
>>> format = "Hello, %s. %s enough for ya?"
>>> values = ('world', 'Hot')
>>> print format % values
Hello, world. Hot enough for ya?

'''Note 
To actually include a percent sign in the format string, you must write %% so  Python 
doesn¡¯t mistake it for the beginning of a conversion specifier.
'''

>>> format = "Pi with three decimals: %.3f"
>>> from math import pi
>>> print format % pi
Pi with three decimals: 3.142




