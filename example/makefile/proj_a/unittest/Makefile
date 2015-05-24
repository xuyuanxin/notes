.PHONY: all clean forcerun dbginfo

# 本次构建要生成的exe文件
EXE = ut.exe

# 本次构建要生成的lib
LIB = 

# 本次构建所依赖的头文件路径 
INCLUDE_DIRS = $(ROOT)/inc

# 本次构建所依赖的库 			   
LINK_LIBS = pja

#------------------------------------------------------------------------------------

ROOT = $(realpath ..)
RM = rm          # rm命令删除目录及文件。#-r, -R, --recursive 递归删除目录及其内容
RMFLAGS = -fr    # -f, --force 强制删除。忽略不存在的文件，不提示确认
CC = gcc         # gcc
AR = ar          # ar:管理静态库。
ARFLAGS = crs    # c:创建档案文件;r:将文件增加到所创建的档案文件;s:生成库索引，提高连接效率; 
#CCFLAGS = -shared -fPIC -Wall -Werror
#CCFLAGS = -shared -fPIC -Wall
CCFLAGS = -shared -Wall -Werror

OBJS_DIR=objs

DIRS = $(OBJS_DIR)

RMS = $(OBJS_DIR)

SRCS = $(wildcard *.c)

LIBS_DIR = $(ROOT)/build/libs
# 中间文件

OBJS = $(SRCS:.c=.o)
OBJS := $(addprefix $(OBJS_DIR)/, $(OBJS))

# 可执行文件
EXES_DIR = $(ROOT)/unittest
ifneq ("$(EXE)", "")
EXE := $(addprefix $(EXES_DIR)/, $(EXE))
endif

# 添加-I参数
ifneq ("$(INCLUDE_DIRS)", "")
INCLUDE_DIRS := $(strip $(INCLUDE_DIRS))
INCLUDE_DIRS := $(addprefix -I,$(INCLUDE_DIRS))
endif

ifneq ("$(LINK_LIBS)", "")                                     # 假设传入 bar.a     foo.a
LINK_LIBS := $(strip $(LINK_LIBS))                             # strip:去掉多余空格 bar.a foo.a
LIB_ALL := $(notdir $(wildcard $(LIBS_DIR)/*))                 # LIBS_DIR目录里的.a文件, 假设有 libfoo.a libbar.a a.a
LIB_FILTERED := $(addsuffix %, $(addprefix lib, $(LINK_LIBS))) # libbar% libfoo%
$(eval DEP_LIBS = $(filter $(LIB_FILTERED), $(LIB_ALL)))       # 从所有的库文件中过滤出 libbar.a libfoo.a
DEP_LIBS := $(addprefix $(LIBS_DIR)/, $(DEP_LIBS))             # 给两个.a文件加上路径
LINK_LIBS := $(addprefix -l,$(LINK_LIBS))                      # -lfoo -lbar
endif

ifeq ("$(wildcard $(DIR_OBJS))", "")
DEP_DIR_OBJS := $(OBJS_DIR)
endif

#all的依赖, 注意顺序.
all: $(OBJS) $(EXE)

$(DIRS):
	mkdir $@

$(OBJS_DIR)/%.o: $(DEP_DIR_OBJS) %.c
	$(CC) $(CCFLAGS) $(INCLUDE_DIRS) -o $@ -c $(filter %.c, $^)

#多个dir之间用冒号分隔: 
#-Wl,-rpath,dir1:dir2:...:dirN  	
$(EXE): $(OBJS) forcerun
#	$(CC) -Bdynamic  -o $@ $(filter %.o, $^) -L$(LIBS_DIR) $(LINK_LIBS)
	$(CC) -Wall -Wl,-rpath=$(LIBS_DIR) -o $@ $(filter %.o, $^) -L$(LIBS_DIR) $(LINK_LIBS)
	
clean:
	$(RM) $(RMFLAGS) $(RMS)
	$(RM) $(RMFLAGS) *.exe
	$(RM) $(RMFLAGS) *.out

forcerun:
	

	
	
	
	
	
	
	
	
