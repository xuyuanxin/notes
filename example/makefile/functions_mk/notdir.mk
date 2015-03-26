#$(notdir names¡­)
#Extracts all but the directory-part of each file name in @names. If the file name c-
#ontains no slash, it is left unchanged. Otherwise, everything through the last slash 
#is removed from it.

#A file name that ends with a slash becomes an empty string. This is unfortunate, be-
#cause it means that the result does not always have the same number of whitespace-separated 
#file names as the argument had; but we do not see any other valid alternative.

#For example,

#$(notdir src/foo.c hacks)
#produces the result ¡®foo.c hacks¡¯.