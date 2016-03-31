//http://www.linuxidc.com/Linux/2012-01/51292.htm

#include <string.h>

#include "sa_cfg.h"


int find_header( FILE *fp,char * header)
{
	char keyName[100];

	if( fp == NULL )
	{
		return -1;
	}

	while( !feof(fp) )
	{
		fscanf(fp,"%s",keyName);
		if( strcmp(keyName,header) == 0 )
		{
			return 0;
		}
	} 

	printf("cannot find %s in file \n",header);

	return -1;
}


#define USER_CFG_FILE   "user.cfg"
#define USERINFO_HEADER "[UserInfo]"

typedef struct _userInfo
{
	char name[20];
	int  ssno;
	char sex[4];

}UserInfo;

int save_cfg( char *filename,UserInfo *pInfo)
{
	FILE *fp = NULL;

	if( ( fp = fopen(filename,"wt") ) == NULL )
	{
		printf("cannot open file %s\n",filename);
		return -1;
	}

	WRITE_PARAM_HEADER(fp,USERINFO_HEADER);

	SAVE_PARAM_STR(fp,name,pInfo->name);
	SAVE_PARAM_INT(fp,ssno,pInfo->ssno);
	SAVE_PARAM_STR(fp,sex,pInfo->sex);

	if (fp)
	{
		fclose(fp);
	}

	return 0;
}

int read_cfg( char *filename,UserInfo * pInfo )
{
	FILE *fp = NULL;
	char keyName[100];

	if( ( fp = fopen(filename,"rt") ) == NULL )
	{
		printf("cannot open file %s\n",filename);
		return -1;
	}

	if( FIND_PARAM_HEADER(fp,USERINFO_HEADER) != 0)
	{
		return -1;
	}

	LOAD_PARAM_STR(fp,keyName,pInfo->name);
	LOAD_PARAM_INT(fp,keyName,&pInfo->ssno);
	LOAD_PARAM_STR(fp,keyName,pInfo->sex);

	if (fp)
	{
		fclose(fp);
	}

	return 0;
}

void main_cfg()
{
	UserInfo user = { "lujun",110,"boy"};
	UserInfo userRead;

	save_cfg(USER_CFG_FILE,&user);

	printf("enter any key to show user.cfg\n");

	getchar();

	read_cfg(USER_CFG_FILE,&userRead);

	printf("userInfo:\nname:%s\nssno:%d\nsex:%s\n",userRead.name,userRead.ssno,userRead.sex);

	getchar();
	getchar();
}


