'''
This module implements a file-like class, @StringIO, that reads and writes a string -
buffer (also known as memory files). See the description of file objects for operati-
ons (section "File Objects"). (For standard strings, see @str and @unicode.)
'''


class StringIO.StringIO([buffer]):
  '''
  '''
  
  def 
  
'''
import StringIO

output = StringIO.StringIO()
output.write('First line.\n')
print >>output, 'Second line.'

# Retrieve file contents -- this will be
# 'First line.\nSecond line.\n'
contents = output.getvalue()

# Close object and discard memory buffer --
# .getvalue() will now raise an exception.
output.close()



StringIO类中的方法：

....● read

....● readline

....● readlines

....● write

....● writelines

....● getvalue

....● truncate

....● tell

....● seek

....● close

....● isatty

....● flush
'''