$(filter pattern¡­,text)
Returns all whitespace-separated words in text that do match any of the pattern words, removing any words that do not match. The patterns are written using ¡®%¡¯, just like the patterns used in the patsubst function above.

The filter function can be used to separate out different types of strings (such as file names) in a variable. For example:

sources := foo.c bar.c baz.s ugh.h
foo: $(sources)
        cc $(filter %.c %.s,$(sources)) -o foo
says that foo depends of foo.c, bar.c, baz.s and ugh.h but only foo.c, bar.c and baz.s should be specified in the command to the compiler.