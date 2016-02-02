
raw_input
 It reads from standard input and assigns the string value to the variable you desig-
 nate. You can use the int() built-in function to convert any numeric input string to 
 an integer representation.
 >>> user = raw_input('Enter login name: ')
 Enter login name: root
 >>> print 'Your login is:', user
 Your login is: root
 
 >>> num = raw_input('Now enter a number: ')
 Now enter a number: 1024
 >>> print 'Doubling your number: %d' % (int(num) * 2)
 Doubling your number: 2048