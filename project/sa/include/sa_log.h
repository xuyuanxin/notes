/*-----------------------------------------------------------------------------------
 log: sa_log.c sa_log.h
 dep: sa_util.h   mkdirs
 ----------------------------------------------------------------------------------*/

#ifndef __SA_LOG_H__
#define __SA_LOG_H__

/*
 http://blog.csdn.net/shanzhizi/article/details/17844509
 */


#define BUF_SIZE 1024  

typedef struct _log_st log_st;  
struct _log_st  
{  
    char path[128];
    char name[128];  
    int fd;  
    int size;  
    int level;  
    int num;  
};  


log_st *log_init(char *log_path, char *logfile_name, int logfile_size);
void log_print(log_st *log,char *type, const char *msg, ...);
void log_checksize(log_st *log);


#define log_info(format,args...) \
do{\
        log_print(format,"info",##args);\
}while(0);

#define log_error(format,args...) \
do{\
        log_print(format,"error",##args);\
}while(0);


#endif
