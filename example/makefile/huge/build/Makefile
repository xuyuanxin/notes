#------------------------------------------------------------------------------------
.PHONY: all clean

#ROOT是当前目录的前一级 ROOT:/cygdrive/f/test/Makefile/huge
ROOT = $(realpath ..)

DIRS = \
$(ROOT)/code/foo/src \
$(ROOT)/code/bar/src \
$(ROOT)/code/huge/src 
	   
RM = rm
RMFLAGS = -fr
RMS = $(ROOT)/build/exes $(ROOT)/build/libs

# -r 禁用隐式规则
# make a=test 给 makefile 中的变量 a 赋值 test
# Makefile中的shell，每一行是一个进程，不同行之间变量值不能传递。所以，Makefile中的
# shell不管多长也要写在一行。

all clean mytest:
	@set -e; \
	for dir in $(DIRS); \
    do \
	    echo "" && echo ""; \
	    cd $$dir ; \
	    $(MAKE) -r ROOT=$(ROOT) $@; \
	done

	@set -e; \
	if [ "$(MAKECMDGOALS)" = "clean" ]; then $(RM) $(RMFLAGS) $(RMS); fi
	
	@echo ""
	@echo ":-) Completed"
	@echo ""

# 更改所有文件的时间戳	
touch:
	@echo "Processing ..."
	@find $(ROOT) -exec touch {} \;
	@echo ""
	@echo ":-) Completed"
	@echo ""
	
callbat:
	@cmd /c "temp.bat";
	
test:
	@echo "ROOT:"$(ROOT)	