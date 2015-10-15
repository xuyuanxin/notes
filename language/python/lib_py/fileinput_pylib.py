'''
This module implements a helper class and functions to quickly write a loop over sta-
ndard input or a list of files. If you just want to read or write one file see      -
@open().

'''


def input([files[, inplace[, backup[, bufsize[, mode[, openhook]]]]]])
    '''fileinput.input
	Sometimes you need to iterate over the lines in a very large file, and @readlines 
	would use too much memory. You could use a while loop with readline, of course, -
	but in Python, for loops are preferable when they are available. It just so happ-
	ens that they are in this case. You can use a method called lazy line iteration -
	it¡¯s lazy because it reads only the parts of the file actually needed (more or l-
	ess). Note that the fileinput module takes care of opening the file. You just ne-
	ed to give it a file name.
    Listing 11-11. Iterating over Lines with fileinput
    |import fileinput
    |for line in fileinput.input(filename):
    |   process(line)
	'''