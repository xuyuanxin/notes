.PHONY: all clean

#ROOT是当前目录的前一级 ROOT:/cygdrive/F:\notes\myproject\build
ROOT = $(realpath ..)

DIRS = $(ROOT)/tree \
       $(ROOT)/stack \
	   $(ROOT)/queue \
	   $(ROOT)/main
	   
RM = rm
RMFLAGS = -fr
RMS = $(ROOT)/build/exes $(ROOT)/build/libs

#-r禁用隐式规则
#make a=test 给makefile中的变量a赋值test
all clean mytest:
	rm -r $(ROOT)/build/exes/test.exe
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
	
test:
	@echo "ROOT:"$(ROOT)
	
touch:
	@echo "Processing ..."
	@find $(ROOT) -exec touch {} \;
	@echo ""
	@echo ":-) Completed"
	@echo ""
	
callbat:
	@cmd /c "temp.bat";
