#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "sa_cmd.h"

#ifdef __READLINE_DEBUG
#include <readline/readline.h>
#include <readline/history.h>
static const char * const pszCmdPrompt = "clover>>";

//退出交互式调测器的命令(不区分大小写)
static const char *pszQuitCmd[] = {"Quit", "Exit", "End", "Bye", "Q", "E", "B"};
static const unsigned char ucQuitCmdNum = sizeof(pszQuitCmd) / sizeof(pszQuitCmd[0]);



//返回gCmdMap中的CmdStr列(必须为只读字符串)，以供CmdGenerator使用
static char *GetCmdByIndex(unsigned int dwCmdIndex)
{
    if(dwCmdIndex >=  CMD_MAP_NUM)
        return NULL;
	return gCmdMap[dwCmdIndex].pszCmd;
}
	  
//执行命令
static int ExecCmd(char *pszCmdLine)
{
    unsigned int dwCmdIndex = 0;

    if(NULL == pszCmdLine)
        return -1;

    for(; dwCmdIndex < CMD_MAP_NUM; dwCmdIndex++)
    {
        if(!strcmp(pszCmdLine, gCmdMap[dwCmdIndex].pszCmd))
            break;
    }
	
    if(CMD_MAP_NUM == dwCmdIndex)
        return -1;

    gCmdMap[dwCmdIndex].fpCmd(); //调用相应的函数
        
    return 0;
}

#ifdef __READLINE_DEBUG

static int IsUserQuitCmd(char *pszCmd)
{
    unsigned char ucQuitCmdIdx = 0;

	for(; ucQuitCmdIdx < ucQuitCmdNum; ucQuitCmdIdx++)
    {
        if(!strcasecmp(pszCmd, pszQuitCmd[ucQuitCmdIdx]))
            return 1;
        }
        return 0;
    }

//剔除字符串首尾的空白字符(含空格)
static char *StripWhite(char *pszOrig)
{
    if(NULL == pszOrig)
        return "NUL";

    char *pszStripHead = pszOrig;
    while(isspace(*pszStripHead))
        pszStripHead++;

     if('\0' == *pszStripHead)
         return pszStripHead;

    char *pszStripTail = pszStripHead + strlen(pszStripHead) - 1;

	while(pszStripTail > pszStripHead && isspace(*pszStripTail))
        pszStripTail--;
    *(++pszStripTail) = '\0';
    return pszStripHead;
}

static char *pszLineRead = NULL;  //终端输入字符串
static char *pszStripLine = NULL; //剔除前端空格的输入字符串

char *ReadCmdLine()
{
    //若已分配命令行缓冲区，则将其释放
    if(pszLineRead)
    {
        free(pszLineRead);
        pszLineRead = NULL;
    }

    //读取用户输入的命令行
    pszLineRead = readline(pszCmdPrompt);
 
    //剔除命令行首尾的空白字符。若剔除后的命令不为空，则存入历史列表
    pszStripLine = StripWhite(pszLineRead);

    if(pszStripLine && *pszStripLine)
        add_history(pszStripLine);

    return pszStripLine;
}
 
static char* CmdGenerator(const char *pszText, int dwState)
{
    static int dwListIdx = 0, dwTextLen = 0;

	if(!dwState)
    {
        dwListIdx = 0;
        dwTextLen = strlen(pszText);
    }
 
    //当输入字符串与命令列表中某命令部分匹配时，返回该命令字符串
    const char *pszName = NULL;
    while((pszName = GetCmdByIndex(dwListIdx)))
    {
        dwListIdx++;
        if(!strncmp (pszName, pszText, dwTextLen))
            return strdup(pszName);
    }
    return NULL;
}

static char** CmdCompletion (const char *pszText, int dwStart, int dwEnd)
{
    //rl_attempted_completion_over = 1;
    char **pMatches = NULL;
    if(0 == dwStart)
        pMatches = rl_completion_matches(pszText, CmdGenerator);
	return pMatches;
}

//初始化Tab键能补齐的Command函数
static void InitReadLine(void)
{
    rl_attempted_completion_function = CmdCompletion;
}
 
#endif



int main_cmd(void)
{
#ifndef __READLINE_DEBUG
    printf("Note: Macro __READLINE_DEBUG is Undefined, thus InteractiveCmd is Unavailable!!!\n\n");
#else
    printf("Note: Welcome to Interactive Command!\n");
    printf(" 	 Press 'Quit'/'Exit'/'End'/'Bye'/'Q'/'E'/'B' to quit!\n\n");
    InitReadLine();

	while(1)
    {
        char *pszCmdLine = ReadCmdLine();
        if(IsUserQuitCmd(pszCmdLine))
        {
            free(pszLineRead);
            break;
        }
        ExecCmd(pszCmdLine);
    }
#endif

    return 0;
}

#else
cmd_para cmdpara;

char *get_para(int idx)
{
    return cmdpara.para[idx];
}

char *get_cmd_name()
{
    return cmdpara.name;
}

int get_para_nums()
{
    return cmdpara.nums;
}

int cmd_quit()
{
    printf("you input quit or q, bye!.");
	exit(0);
}

int cmd_test()
{
    int i = 0;
    int paranums = get_para_nums();

    printf("cmd_test run, cmd name %s.\n",get_cmd_name());
    for(; i < paranums; ++i)
    {
        printf("para %d: %s\n",i, get_para(i));
    }

	if( 0 == i)
	{
	    printf("para nums is 0.\n");
	}

    return 0;
}

extern int cmd_help();


static cmd_item cmd_tbl[] = //cmd table
{
    {"quit",cmd_quit},
    {"q",cmd_quit},
	{"help",cmd_help},
	{"cmdtest", cmd_test},
    {NULL,NULL}
};

#define CMD_TBL_NUM (sizeof(cmd_tbl)/sizeof(cmd_item)) - 1 

int cmd_help()
{
    int j = 0;

    printf("supported cmd:\n");
    for(; j < CMD_TBL_NUM; j++)
    {
        printf("%s\n",cmd_tbl[j].cmd_name);
    }

	return 0;
}

int cmd_analyse(char *cmd)
{
    char * pch;
    int i = 0;
	
    memset(&cmdpara,0,sizeof(cmdpara));

	if(0 == strlen(cmd))
	{
	    printf("cmd len is 0\n");
		return -1;
	}

    cmd[strlen(cmd)-1] = '\0';
	
    pch = strtok(cmd, " ");
    while (pch != NULL)
    {
	    //printf("dbginfo. token %d, {%s} \n",i,pch);

        if(0 == i)
        {
			strncpy(cmdpara.name, pch, CMDNAME_LEN);
		}
		else
		{
		    strncpy(cmdpara.para[i-1], pch, PARA_LENS);
		}
        pch = strtok(NULL, " ");
	    ++i;
    }

    if(0 == i)
    {
        cmdpara.nums = 0;
    }
    else
    {
        cmdpara.nums = i-1; /* first is func name */
    }

    return 0;
}

int exec_cmd(char *cmd)
{
    int j = 0;
    int ret = 0;
	
    ret = cmd_analyse(cmd);
    if ( 0 != ret)
    {
        printf("cmd analyse failed(%d)\n.",ret);
        return ret;
    }

    if(0 == strlen(cmdpara.name))
    {
        return 0; /* \n */
    }

    for(; j < CMD_TBL_NUM; j++)
    {
        if(!strcmp(cmdpara.name, cmd_tbl[j].cmd_name))
        {
            break;
        }
    }

    if(CMD_TBL_NUM == j)
    {
        printf("cmd not found: %s \n",cmdpara.name);
        return -1;
    }

    cmd_tbl[j].cmd_cb();
	
    return 0;    
}

int main_cmd(void)
{
    char cmdbuf[512] = {0};
    char *cmdstr = NULL;
	int first = 1;

    while(1)
    {
        memset(cmdbuf, 0, 512);
		if(first)
		{
		    printf("->");
			first = 0;
		}
        cmdstr = fgets(cmdbuf, 512, stdin);
		(void)exec_cmd(cmdstr);
		printf("->");
    }
}



#endif



/*
1 [wangxiaoyuan_@localhost test1]$ gcc -Wall -o ReadLine ReadLine.c -D__READLINE_DEBUG -lreadline -lncurses
 2 [wangxiaoyuan_@localhost test1]$ ./ReadLine
 3 Note: Welcome to Interactive Command!
 4       Press 'Quit'/'Exit'/'End'/'Bye'/'Q'/'E'/'B' to quit!
 5 
 6 clover>>ShowMeInfo(完整输入)
 7   Enter ShowMeInfo!
 8 clover>>ShowMeInfo(UP键调出历史命令)
 9   Enter ShowMeInfo!
10 clover>>SetLogCtrl (输入'Se'自动补全)
11   Enter SetLogCtrl!
12 clover>>   TestEndianOper(错误输入)
13 clover>>TestEndian  (输入'T'自动补全为"Test"，再输入'E'自动补全为"TestEndian ")
14   Enter TestEndianOper!
15 clover>>  TestBatch   (命令首尾加空格，无法自动补全)
16   Enter TestBatch!
17 clover>>ReadLine (输入'R'自动补全文件名)
18 clover>>quit
19 [wangxiaoyuan_@localhost test1]$
不启用Readline库时，执行结果如下：

1 [wangxiaoyuan_@localhost test1]$ gcc -Wall -o ReadLine ReadLine.c                                        
2 ReadLine.c:41: warning: 'GetCmdByIndex' defined but not used
3 ReadLine.c:49: warning: 'ExecCmd' defined but not used
4 [wangxiaoyuan_@localhost test1]$ ./ReadLine
5 Note: Macro __READLINE_DEBUG is Undefined, thus InteractiveCmd is Unavailable!!!



http://www.tuicool.com/articles/zu2um27


*/
	

