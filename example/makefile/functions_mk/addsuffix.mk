#$(addsuffix suffix,names¡­)
#The argument names is regarded as a series of names, separated by whitespace; suffix 
#is used as a unit.The value of suffix is appended to the end of each individual name 
#and the resulting larger names are concatenated with single spaces between them. 

#For example,
#$(addsuffix .c,foo bar)
#produces the result ¡®foo.c bar.c¡¯.