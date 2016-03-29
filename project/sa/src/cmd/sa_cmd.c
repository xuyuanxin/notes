#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "sa_cmd.h"

cmd_para cmdpara;

static cmd_item cmd_tbl[] = //cmd table
{
    {"quit",cmd_quit},
    {"q",cmd_quit},
	{"help",cmd_help},
	{"cmdtest", cmd_test},
    {NULL,NULL}
};

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






