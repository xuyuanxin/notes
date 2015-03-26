$(wildcard pattern)
The argument pattern is a file name pattern, typically containing wildcard characters (as in shell file name patterns). The result of wildcard is a space-separated list of the names of existing files that match the pattern.
Wildcard expansion does not happen when you define a variable. Thus, if you write this:

objects = *.o
then the value of the variable objects is the actual string ‘*.o’. However, if you use the value of objects in a target or prerequisite, wildcard expansion will take place there. If you use the value of objects in a recipe, the shell may perform wildcard expansion when the recipe runs. To set objects to the expansion, instead use:

objects := $(wildcard *.o)
	