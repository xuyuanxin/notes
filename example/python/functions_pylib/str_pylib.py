#!/usr/bin/env python
#coding=utf-8
# Filename: str_pylib.py
#####################################################################################
'''
class str(object='')
Return a string containing a nicely printable representation of an object. For strin-
gs, this returns the string itself. The difference with repr(object) is that str(object) 
does not always attempt to return a string that is acceptable to eval(); its goal is 
to return a printable string. If no argument is given, returns the empty string, ''.
'''
print str(4.53-2j) #'(4.53-2j)'
print str(1) #'1'
print str(2e10) #'20000000000.0'
print str([0, 5, 9, 9]) #'[0, 5, 9, 9]'
print repr([0, 5, 9, 9]) #'[0, 5, 9, 9]'
print `[0, 5, 9, 9]` #'[0, 5, 9, 9]'