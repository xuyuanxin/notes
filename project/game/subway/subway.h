#define SUBWAY_ERROR_MALLOC_FAIL 1
#define SUBWAY_ERROR_CONFLICT    2
#define SUBWAY_ERROR_REPEAT      3
#define SUBWAY_ERROR_PARAMETER   4




#define STN_NAME_MAX 20
#define LINE_NUM_MAX 10




typedef struct station_tag
{
    struct station_tag *stn_next; 
    int stn_id;
	int stn_line;
	char stn_name[STN_NAME_MAX + 1];
}station_t;

typedef struct line_tag
{
    station_t *stn_head;/*这条线上的站点个数，为NULL说明还没有创建这个线路*/	
    station_t *stn_tail;
	
	int stn_nums;   /*这条线上的站点个数*/
}line_t;

typedef struct record_tag
{
    struct record_tag *record_next;
    int person_id;
	int stn_in;
	int stn_out;
	int stn_nums;
}record_t;


typedef struct subway_tag
{
    int line_nums;
	int stn_nums;
	line_t   lines[LINE_NUM_MAX];	
	record_t *records;	
}subway_t;

extern 	void subway_show(void);


/*
 line    : 编号 0 ~ LINE_NUM_MAX
 station : */

