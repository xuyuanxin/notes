#$(eval _text)                                                                       |
#eval函数使得Makefile具有动态语言的特性。eval函数使得make将再一次解析_text语句. eval |
#函数返回值为空字符串。

.PHONY: all
sources = foo.c bar.c baz.s ugh.h
$(eval sources := $(filter %.c %.s, $(sources)))

all:
	@echo $(sources)
	
#make
#main.c
