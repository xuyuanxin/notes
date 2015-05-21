#------------------------------------------------------------------------------------
.PHONY: all clean 

#ROOT是当前目录的前一级
ROOT = $(realpath ..)

#所有要编译的目录
DIRS += $(ROOT)/src/bar
DIRS += $(ROOT)/src/foo
DIRS += $(ROOT)/src/huge
DIRS += $(ROOT)/src 

#默认目录
DIRS+=$(ROOT)/build/objs
DIRS+=$(ROOT)/src/main

#单元测试目录


#clean操作 
RM = rm
RMFLAGS = -fr
#RMS = $(ROOT)/build/exes $(ROOT)/build/libs

# -r 禁用隐式规则
# make a=test 给 makefile 中的变量 a 赋值 test
# Makefile中的shell，每一行是一个进程，不同行之间变量值不能传递。
# 所以，Makefile中的shell不管多长也要写在一行。

all dbginfo:
	@set -e; \
	for dir in $(DIRS); \
    do \
	    echo "" && echo ""; \
	    cd $$dir ; \
	    $(MAKE) -r ROOT=$(ROOT) $@; \
	done
	
	@echo ""
	@echo ""
	@echo ":-) Completed"
	@echo ""
	
clean:
	$(RM) $(RMFLAGS) $(ROOT)/build/objs/*.o
	$(RM) $(RMFLAGS) $(ROOT)/build/libs/*.a	
	$(RM) $(RMFLAGS) $(ROOT)/build/libs/*.so*
	$(RM) $(RMFLAGS) $(ROOT)/build/libs/*.dll
	$(RM) $(RMFLAGS) $(ROOT)/build/deps/*.dep
	$(RM) $(RMFLAGS) $(ROOT)/build/deps/*.tmp
	$(RM) $(RMFLAGS) $(ROOT)/build/exes/*.exe
	
# 更改所有文件的时间戳	
touch:
	@echo "Processing ..."
	@find $(ROOT) -exec touch {} \;
	@echo ""
	@echo ":-) Completed"
	@echo ""

test:
	@echo "ROOT:"$(ROOT)	
	
	