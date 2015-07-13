#------------------------------------------------------------------------------------
.PHONY: all clean forcerun dbginfo

# xxx/sa
ROOT = $(realpath ..)

RM = rm          # rm命令删除目录及文件。#-r, -R, --recursive 递归删除目录及其内容
RMFLAGS = -fr    # -f, --force 强制删除。忽略不存在的文件，不提示确认
CC = gcc         # gcc
AR = ar          # ar:管理静态库。
ARFLAGS = crs    # c:创建档案文件;r:将文件增加到所创建的档案文件;s:生成库索引，提高连接效率; 

#CCFLAGS = -shared -fPIC -Wall -Werror
CCFLAGS = -shared -Wall -Werror

SRCS = $(wildcard *.c)

# 中间文件
OBJS_DIR=$(ROOT)/unittest
OBJS = $(SRCS:.c=.o)
OBJS := $(addprefix $(OBJS_DIR)/, $(OBJS))

LIBS_DIR+=-L$(ROOT)/build/libs
LINK_LIBS+=-lsa

# 可执行文件
EXES_DIR = $(ROOT)/unittest
EXE = ut.out
EXE := $(addprefix $(EXES_DIR)/, $(EXE))

#all的依赖, 注意顺序.
all: $(EXE)
	
# 生成目标文件	
$(OBJS_DIR)/%.o: %.c
	$(CC) $(CCFLAGS) $(INCLUDE_DIRS) -o $@ -c $(filter %.c, $^)

# 可执行文件
$(EXE): $(OBJS) forcerun
#	$(CC) -Bdynamic $(CCFLAGS)  -o $@ $(filter %.o, $^) -L$(LIBS_DIR) $(LINK_LIBS)
#	$(CC) -Wall -Wl,-rpath=$(LIBS_DIR) -o $@ $(filter %.o, $^) -L$(LIBS_DIR) $(LINK_LIBS)
	$(CC) -Wall -Werror -o $@ $(filter %.o, $^) $(LIBS_DIR) $(LINK_LIBS)

clean:
	$(RM) $(RMFLAGS) $(ROOT)/unittest/*.o
	$(RM) $(RMFLAGS) $(ROOT)/unittest/*.a	
	$(RM) $(RMFLAGS) $(ROOT)/unittest/*.so*
	$(RM) $(RMFLAGS) $(ROOT)/unittest/*.dll
	$(RM) $(RMFLAGS) $(ROOT)/unittest/*.dep
	$(RM) $(RMFLAGS) $(ROOT)/unittest/*.tmp
	$(RM) $(RMFLAGS) $(ROOT)/unittest/*.exe
	$(RM) $(RMFLAGS) $(ROOT)/unittest/*.out
	
forcerun:
	
dbginfo:
	@echo "----> $@ run beg"
	@echo "ROOT     : "$(ROOT)
	@echo "DEPS_DIR : "$(DEPS_DIR)
	@echo "DEPS     : "$(DEPS)	
	@echo "OBJS_DIR : "$(OBJS_DIR)
	@echo "OBJS     : "$(OBJS)
	@echo "LIBS_DIR : "$(LIBS_DIR)	
	@echo "LIB      : "$(LIB)
	@echo "LIBDYN   : "$(LIBDYN)
	@echo "----> $@ run end"	
