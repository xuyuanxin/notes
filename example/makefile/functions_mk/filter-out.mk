$(filter-out pattern¡­,text)
Returns all whitespace-separated words in text that do not match any of the pattern words, removing the words that do match one or more. This is the exact opposite of the filter function.

For example, given:

objects=main1.o foo.o main2.o bar.o
mains=main1.o main2.o
the following generates a list which contains all the object files not in ¡®mains¡¯:

$(filter-out $(mains),$(objects))