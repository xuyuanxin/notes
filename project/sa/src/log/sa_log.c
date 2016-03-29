#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <string.h>
#include <stdarg.h>
#include <unistd.h>

#include "sa_util.h" /* mkdirs */
#include "sa_log.h"

/*-----------------------------------------------------------------------------------
 @log_path: /var/log/xxx
 @logfile_name; libsa.log
 @logfile_size: libsa.log -> libsa.log.old
 ----------------------------------------------------------------------------------*/
log_st *log_init(char *log_path, char *logfile_name, int logfile_size)
{  
    char fullname[128] = {0};
	log_st *logger;

    if (NULL == log_path || NULL == logfile_name) 
	{
		return NULL;
    }
	
    logger = (log_st *)malloc(sizeof(log_st));
	if(NULL == logger)
	{
	    printf("log init failed!\n");
        return NULL;
	}

    memset(logger, 0, sizeof(log_st));  

    if(-1 == mkdirs(log_path))
    {
        printf("log init failed! mkdirs %s failed!\n",log_path);
		return NULL;
    }

    snprintf(fullname, 128, "%s/%s", log_path,logfile_name);  

    if(-1 == (logger->fd = open(fullname, O_RDWR|O_APPEND|O_CREAT|O_SYNC, S_IRUSR|S_IWUSR|S_IROTH)))  
    {  
        free(logger);
        printf("Error! log init failed! open %s failed!\n",fullname);
        return NULL;  
    }  

    strncpy(logger->path, log_path, 128); 
    strncpy(logger->name, logfile_name, 128);

    logger->size = (logfile_size > 0 ? logfile_size:0);

    printf("Info log init ok.\n");

    return logger;  
}  

int log_header(char *buf)
{
	time_t nowtime = time(NULL);
    char *pos      = ctime(&nowtime);  
    size_t sz      = strlen(pos);

    pos[sz-1]=']';  
    snprintf(buf, BUF_SIZE, "[%s", pos);

    return strlen(buf);
}

void log_debug(log_st *log, const char *msg, ...)
{  
    va_list ap;  
    char _n = '\n';  
    char message[BUF_SIZE] = {0};  
    int msglen = 0;  
    size_t lh_size; 

    if(NULL == log) {
        return;
    }

	log_checksize(log);

    lh_size = log_header(message);
	
    va_start(ap, msg);  
    msglen = vsnprintf(message + lh_size, BUF_SIZE - lh_size, msg, ap);  
    va_end(ap); 
	
    if (msglen <= 0) {
        printf("msg len is zero. %s\n", message);
        return;  
    }

    if (0 == log->level) {
        printf("%s\n", message);
    }

    write(log->fd, message, strlen(message));  
    write(log->fd, &_n, 1);
    fsync(log->fd);  
} 

void log_checksize(log_st *log)
{  
    struct stat stat_buf;  
    char new_path[128] = {0};  
    char bak_path[128] = {0};
	
    if(NULL == log) 
	{ 
        return;
    }

    memset(&stat_buf, 0, sizeof(struct stat));  
    fstat(log->fd, &stat_buf);

    //printf("log file size %d",(int)stat_buf.st_size);
	
    if(stat_buf.st_size > log->size)  
    {  
        close(log->fd);
		
        snprintf(bak_path, 128, "%s/%s.old", log->path,log->name);  
        snprintf(new_path, 128, "%s/%s", log->path,log->name);  
        remove(bak_path); //delete the file *.bak first  
        rename(new_path, bak_path); //change the name of the file *.new to *.bak
		log->fd = open(new_path, O_RDWR|O_APPEND|O_CREAT|O_SYNC, S_IRUSR|S_IWUSR|S_IROTH);
    }        
}  


