.PHONY: all clean

ROOT = $(realpath ..) 

DIRS = $(ROOT)/code/foo/src \
       $(ROOT)/code/bar/src \
	   $(ROOT)/code/huge/src 
	   
RM = rm
RMFLAGS = -fr
RMS = $(ROOT)/build/exes $(ROOT)/build/libs


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