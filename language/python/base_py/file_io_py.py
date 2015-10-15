'''
File Iterators
  In current versions of Python (from version 2.2), files are iterable, which means -
  that you can use them directly in for loops to iterate over their lines. 
  Listing 11-12. Iterating over a File
  |f = open(filename)
  |for line in f:
  |    process(line)
  |f.close()
  In these iteration examples, I have explicitly closed my files. Although this is g-
  enerally a good idea, it¡¯s not critical, as long as I don¡¯t write to the file. If -
  you are willing to let Python take care of the closing, you could simplify the exa-
  mple even further, as shown in Listing 11-13. Here, I don¡¯t assign the opened  file 
  to a variable (like the variable f I¡¯ve used in the other examples), and  therefore 
  I have no way of explicitly closing it.
  Listing 11-13. Iterating over a File Without Storing the File Object in a Variable
  |for line in open(filename):
  |    process(line)
  Note that sys.stdin is iterable, just like other files, so if you want to iterate -
  over all the lines in standard input, you can use this form:
  |import sys
  |for line in sys.stdin:
  |    process(line)
  Also, you can do all the things you can do with iterators in general, such as conv-
  erting them into lists of strings (by using list(open(filename))), which would sim-
  ply be equivalent to using readlines. Consider the following example:
  >>> f = open('somefile.txt', 'w')
  >>> f.write('First line\n')
  >>> f.write('Second line\n')
  >>> f.write('Third line\n')
  >>> f.close()
  >>> lines = list(open('somefile.txt)')
  >>> lines
  ['First line\n', 'Second line\n', 'Third line\n']
  >>> first, second, third = open('somefile.txt')
  >>> first
  'First line\n'
  >>> second
  'Second line\n'
  >>> third
  'Third line\n'

In this example, it¡¯s important to note the following:
? I¡¯ve used print to write to the file. This automatically adds newlines after the strings
I supply.
? I use sequence unpacking on the opened file, putting each line in a separate variable.
(This isn¡¯t exactly common practice because you usually won¡¯t know the number of lines
in your file, but it demonstrates the ¡°iterability¡± of the file object.)
? I close the file after having written to it, to ensure that the data is flushed to disk. (As you
can see, I haven¡¯t closed it after reading from it. Sloppy, perhaps, but not critical.)