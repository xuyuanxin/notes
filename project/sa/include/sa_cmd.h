#ifndef __SA_CMD_H__
#define __SA_CMD_H__

#ifdef __READLINE_DEBUG

//命令结构体
typedef int (*CmdProcFunc)(void);
typedef struct
{
    char         *pszCmd;
    CmdProcFunc  fpCmd;
}CMD_PROC;

//命令处理函数定义
#define MOCK_FUNC(funcName) int funcName(void){printf("  Enter "#funcName"!\n"); return 0;}

MOCK_FUNC(ShowMeInfo);
MOCK_FUNC(SetLogCtrl);
MOCK_FUNC(TestBatch);
MOCK_FUNC(TestEndianOper);

//命令表项宏，用于简化书写
#define CMD_ENTRY(cmdStr, func)     {cmdStr, func}
#define CMD_ENTRY_END               {NULL,   NULL}

//命令表
static CMD_PROC gCmdMap[] = {
    CMD_ENTRY("ShowMeInfo",       ShowMeInfo),
    CMD_ENTRY("SetLogCtrl",       SetLogCtrl),
    CMD_ENTRY("TestBatch",        TestBatch),
    CMD_ENTRY("TestEndian",       TestEndianOper),
    CMD_ENTRY_END
};

#define CMD_MAP_NUM     (sizeof(gCmdMap)/sizeof(CMD_PROC)) - 1/*End*/

#endif

#define PARA_NUMS 20
#define PARA_LENS 32
#define CMDNAME_LEN 64

typedef int (*pcmd_cb)(void);

typedef struct
{
    char   *cmd_name;
    pcmd_cb cmd_cb;
}cmd_item;

typedef struct
{
   int  nums;
   char name[CMDNAME_LEN];
   char para[PARA_NUMS][PARA_LENS];
}cmd_para;


#endif

