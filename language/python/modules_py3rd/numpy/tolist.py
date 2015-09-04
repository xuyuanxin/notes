'''
numpy.chararray.tolist

chararray.tolist()
Return the array as a (possibly nested) list.

Return a copy of the array data as a (nested) Python list. Data items are converted -
to the nearest compatible Python type.

Parameters:	
none :
Returns:	
y : list
    The possibly nested list of array elements.
Notes
    The array may be recreated, a = np.array(a.tolist()).

Examples
>>>
>>> a = np.array([1, 2])
>>> a.tolist()
[1, 2]
>>> a = np.array([[1, 2], [3, 4]])
>>> list(a)
[array([1, 2]), array([3, 4])]
>>> a.tolist()
[[1, 2], [3, 4]]
'''
def tolist():
    pass
	