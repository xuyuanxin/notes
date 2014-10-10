#include "subway.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>


char *add_result_to_str(int id)
{
    switch(id)
    {
        case 0:
			return "success";
		case SUBWAY_ERROR_MALLOC_FAIL:
			return "fail malloc mem fail";
		case SUBWAY_ERROR_CONFLICT:
			return "fail station name and id conflict";
		case SUBWAY_ERROR_REPEAT:
			return "fail station add again";
		case SUBWAY_ERROR_PARAMETER:
			return "fail inparameter error";
		default:
			return "fail unknown";
   	}
}

int subway_test01(void) /**/
{
    int  ret;
	int  id;
	int  line;	
	char *name = NULL;

    line = 1;
	id   = 0;
	name = "pingguoyuan";
	printf("\r\nadd station %d %-20s  to line %d %s",id,name,line,add_result_to_str(add_station(line,id,name)));

    line = 1;
	id   = 1;
	name = "gucheng";
	printf("\r\nadd station %d %-20s  to line %d %s",id,name,line,add_result_to_str(add_station(line,id,name)));
	 
	line = 1;
	id   = 2;
	name = "bajiaoyouleyuan";
	printf("\r\nadd station %d %-20s  to line %d %s",id,name,line,add_result_to_str(add_station(line,id,name)));
	 
    line = 1;
	id   = 3;
	name = "babaoshan";
	printf("\r\nadd station %d %-20s  to line %d %s",id,name,line,add_result_to_str(add_station(line,id,name)));

	 subway_show();

	 subway_clear();
}

int subway_test00(void)
{
    int *p1;
	int *p2;
	p1 = malloc(4);
	p2 = malloc(4);
	free(p1);
	
	free(p2);
}



int main()
{
    subway_test01();
}

