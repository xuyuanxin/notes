#ifndef __SA_CMD_H__
#define __SA_CMD_H__

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

#define CMD_TBL_NUM (sizeof(cmd_tbl)/sizeof(cmd_item)) - 1 


char *get_para(int idx);
char *get_cmd_name();
int get_para_nums();
int cmd_quit();
int cmd_test();
int cmd_help();





#endif

