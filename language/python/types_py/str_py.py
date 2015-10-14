

String Formatting
 >>> format = "Hello, %s. %s enough for ya?"
 >>> values = ('world', 'Hot')
 >>> print format % values
 Hello, world. Hot enough for ya?
 
 String formatting uses the string formatting operator, the percent (%) sign. To  the 
 left of the %, you place a string (the format string); to the right of it, you place 
 the value you want to format. You can use a single value such as a string or a numb-
 er, you can use a tuple of values.
 
 To actually include a percent sign in the format string, you must write %% so Python 
 doesn’t mistake it for the beginning of a conversion specifier.
 
TEMPLATE STRINGS
 The string module offers another way of formatting values: template strings. 
 >>> from string import Template
 >>> s = Template('$x, glorious $x!')
 >>> s.substitute(x='slurm')
 'slurm, glorious slurm!'
 If the replacement field is part of a word, the name must be enclosed in braces,  in 
 order to clearly indicate where it ends:
 >>> s = Template("It's ${x}tastic!")
 >>> s.substitute(x='slurm')
 "It's slurmtastic!"
 In order to insert a dollar sign, use $$:
 >>> s = Template("Make $$ selling $x!")
 >>> s.substitute(x='slurm')
 'Make $ selling slurm!'
 Instead of using keyword arguments, you can supply the value-name pairs in a dictio-
 nary:
 >>> s = Template('A $thing must never $action.')
 >>> d = {}
 >>> d['thing'] = 'gentleman'
 >>> d['action'] = 'show his socks'
 >>> s.substitute(d)
 'A gentleman must never show his socks.'
 
str.split([sep[, maxsplit]])
    Return a list of the words in the string, using @sep as the delimiter string.
    '1,,2'.split(',') returns ['1', '', '2'])
	
str.strip([chars])
    Return a copy of the string with the leading and trailing characters removed. The 
	chars argument is a string specifying the set of characters to be removed. If om-
	itted or None, the chars argument defaults to removing whitespace. The chars arg-
	ument is not a prefix or suffix; rather, all combinations of its values are stri-
	pped:
>>>
>>> '   spacious   '.strip()
'spacious'
>>> 'www.example.com'.strip('cmowz.')
'example'

def rfind(sub[, start[, end]]):
    '''str.rfind(sub[, start[, end]])
    Return the highest index in the string where substring @sub is found, such that -
    @sub is contained within s[start:end]. Optional arguments @start and @end are  i-
    nterpreted as in slice notation. Return -1 on failure. '''
    pass    