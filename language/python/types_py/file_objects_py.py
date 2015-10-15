'''

example: file_io_py_eg.py

File objects are implemented using C¡¯s stdio package and can be created with the    -
built-in open() function. File objects are also returned by some other built-in func-
tions and methods, such as os.popen() and os.fdopen() and the makefile() method of s-
ocket objects. Temporary files can be created using the tempfile module, and        -
high-level file operations such as copying, moving, and deleting files and directori-
es can be achieved with the @shutil module.
'''

def close():
    ''' file.close()
    |with open("somefile.txt") as somefile:
    |    do_something(somefile)
    The with statement lets you open a file and assign it to a variable name (in this 
	case,somefile). You then write data to your file (and, perhaps, do other  things) 
	in the body of the statement, and the file is automatically closed when the end -
	of the statement is reached, even if that is caused by an exception.
	
	the data may be buffered (stored temporarily somewhere in memory), and not writt-
	en until you close the file. If you want to keep working with the file (and not -
	close it) but still want to make sure the file on disk is updated to reflect your 
	changes, call the file object¡¯s flush method.
	
	You should always close a file you have written to because Python may buffer (ke-
	ep stored temporarily somewhere, for efficiency reasons) the data you have writt-
	en, and if your program crashes for some reason, the data might not be written to 
	the file at all. The safe thing is to close your files after you¡¯re finished with 
	them.
	
	Close the file. A closed file cannot be read or written any more. Any operation -
	which requires that the file be open will raise a ValueError after the file has -
	been closed. Calling close() more than once is allowed.
    '''