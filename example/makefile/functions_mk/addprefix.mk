#$(addprefix prefix,names¡­)
#The argument names is regarded as a series of names, separated by whitespace; prefix 
#is used as a unit . The value of prefix is prepended to the front of each individual 
#name and the resulting larger names are concatenated with single spaces between them. 

#For example,
#$(addprefix src/,foo bar)
#produces the result ¡®src/foo src/bar¡¯.