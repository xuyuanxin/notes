.PHONY: all clean forcerun dbginfo

# ���ι���Ҫ���ɵ�exe�ļ�
EXE = ut.exe

# ���ι���Ҫ���ɵ�lib
LIB = 

# ���ι�����������ͷ�ļ�·�� 
INCLUDE_DIRS = $(ROOT)/inc

# ���ι����������Ŀ� 			   
LINK_LIBS = pja

#------------------------------------------------------------------------------------

ROOT = $(realpath ..)
RM = rm          # rm����ɾ��Ŀ¼���ļ���#-r, -R, --recursive �ݹ�ɾ��Ŀ¼��������
RMFLAGS = -fr    # -f, --force ǿ��ɾ�������Բ����ڵ��ļ�������ʾȷ��
CC = gcc         # gcc
AR = ar          # ar:������̬�⡣
ARFLAGS = crs    # c:���������ļ�;r:���ļ����ӵ��������ĵ����ļ�;s:���ɿ��������������Ч��; 
#CCFLAGS = -shared -fPIC -Wall -Werror
#CCFLAGS = -shared -fPIC -Wall
CCFLAGS = -shared -Wall -Werror

OBJS_DIR=objs

DIRS = $(OBJS_DIR)

RMS = $(OBJS_DIR)

SRCS = $(wildcard *.c)

LIBS_DIR = $(ROOT)/build/libs
# �м��ļ�

OBJS = $(SRCS:.c=.o)
OBJS := $(addprefix $(OBJS_DIR)/, $(OBJS))

# ��ִ���ļ�
EXES_DIR = $(ROOT)/unittest
ifneq ("$(EXE)", "")
EXE := $(addprefix $(EXES_DIR)/, $(EXE))
endif

# ����-I����
ifneq ("$(INCLUDE_DIRS)", "")
INCLUDE_DIRS := $(strip $(INCLUDE_DIRS))
INCLUDE_DIRS := $(addprefix -I,$(INCLUDE_DIRS))
endif

ifneq ("$(LINK_LIBS)", "")                                     # ���贫�� bar.a     foo.a
LINK_LIBS := $(strip $(LINK_LIBS))                             # strip:ȥ������ո� bar.a foo.a
LIB_ALL := $(notdir $(wildcard $(LIBS_DIR)/*))                 # LIBS_DIRĿ¼���.a�ļ�, ������ libfoo.a libbar.a a.a
LIB_FILTERED := $(addsuffix %, $(addprefix lib, $(LINK_LIBS))) # libbar% libfoo%
$(eval DEP_LIBS = $(filter $(LIB_FILTERED), $(LIB_ALL)))       # �����еĿ��ļ��й��˳� libbar.a libfoo.a
DEP_LIBS := $(addprefix $(LIBS_DIR)/, $(DEP_LIBS))             # ������.a�ļ�����·��
LINK_LIBS := $(addprefix -l,$(LINK_LIBS))                      # -lfoo -lbar
endif

ifeq ("$(wildcard $(DIR_OBJS))", "")
DEP_DIR_OBJS := $(OBJS_DIR)
endif

#all������, ע��˳��.
all: $(OBJS) $(EXE)

$(DIRS):
	mkdir $@

$(OBJS_DIR)/%.o: $(DEP_DIR_OBJS) %.c
	$(CC) $(CCFLAGS) $(INCLUDE_DIRS) -o $@ -c $(filter %.c, $^)

#���dir֮����ð�ŷָ�: 
#-Wl,-rpath,dir1:dir2:...:dirN  	
$(EXE): $(OBJS) forcerun
#	$(CC) -Bdynamic  -o $@ $(filter %.o, $^) -L$(LIBS_DIR) $(LINK_LIBS)
	$(CC) -Wall -Wl,-rpath=$(LIBS_DIR) -o $@ $(filter %.o, $^) -L$(LIBS_DIR) $(LINK_LIBS)
	
clean:
	$(RM) $(RMFLAGS) $(RMS)
	$(RM) $(RMFLAGS) *.exe
	$(RM) $(RMFLAGS) *.out

forcerun:
	

	
	
	
	
	
	
	
	