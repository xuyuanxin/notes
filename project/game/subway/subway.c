#include "subway.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

subway_t subway_ctrl;

/*在lineid线路上增加一个站点*/
int add_station(int lineid,int stationid,char *stn_name)
{
    int i;
    line_t *sw_line = NULL;
	station_t *station = NULL;
	station_t *head = NULL;
	station_t *tail = NULL;
    int transfer_station = 0;

	if( (lineid < 0 || lineid > LINE_NUM_MAX) || NULL == stn_name)
	{
	    return SUBWAY_ERROR_PARAMETER;
	}

    /*检查站点id和名字是否满足要求，一个id对应一个名字，同一条线上不能有相同的id，不同线上id相同则为换乘站*/
	for(i = 0; i < LINE_NUM_MAX; ++i)
	{
	    station = subway_ctrl.lines[i].stn_head;

		while(NULL != station)
		{
		    if( (stationid == station->stn_id && 0 != strncmp(station->stn_name,stn_name,STN_NAME_MAX)) ||
				 (stationid != station->stn_id && 0 == strncmp(station->stn_name,stn_name,STN_NAME_MAX)) )
		    {
				return SUBWAY_ERROR_CONFLICT;
		    }
			else if(stationid == station->stn_id && 0 == strncmp(station->stn_name,stn_name,STN_NAME_MAX))
			{			
		        if(lineid == i)
		        {
		            return SUBWAY_ERROR_REPEAT;
		        }
			    else
			    {
                     transfer_station = 1;
			    }
			}
			else
			{
			    /* ok */
			}

			station = station->stn_next;
		}
	}

    sw_line = &subway_ctrl.lines[lineid];

    station = NULL;
    station = (station_t *)malloc(sizeof(station_t));

	if(NULL == station){
		return SUBWAY_ERROR_MALLOC_FAIL;
	}

	(void)memset(station,0,sizeof(station_t));

	head = sw_line->stn_head;
	tail = sw_line->stn_tail;

	if(NULL == head){
		sw_line->stn_head = sw_line->stn_tail = station;
	}
	else {
		tail->stn_next   = station;
		sw_line->stn_tail = station;
	}
	
    sw_line->stn_nums++;
	station->stn_id   = stationid;
	station->stn_line = lineid;
	(void)strncpy(station->stn_name,stn_name,STN_NAME_MAX);
	station->stn_name[STN_NAME_MAX] = '\0';

    return 0;
}

void subway_clear(void)
{
    int i = 0;
	line_t    *line    = NULL;
	station_t *station = NULL;
	station_t *next    = NULL;

	for(i = 0; i < LINE_NUM_MAX; ++i)
	{
	    line    = &subway_ctrl.lines[i];
		station = line->stn_head;
		next    = NULL;

		while(NULL != station)
		{
		    next = station->stn_next;
			free(station);
			station = next;
		}
	}

	(void)memset(&subway_ctrl,0,sizeof(subway_t));
}


void subway_show(void)
{
    int i = 0;
	int j = 0;
	line_t    *line    = NULL;
	station_t *station = NULL;

	printf("\r\n-------- subway info --------");

	for(i = 0; i < LINE_NUM_MAX; ++i)
	{
	    line    = &subway_ctrl.lines[i];
		station = line->stn_head;
        j = 0;

		while(NULL != station)
		{
			j++;
			printf("\r\nline %d station %d-%d  --> id:0x%08x name:%s",
				   i,line->stn_nums,j,station->stn_id,station->stn_name);
		
			station = station->stn_next;
		}
	}
}

