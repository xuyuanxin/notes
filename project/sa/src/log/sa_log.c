#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <string.h>
#include <stdarg.h>
#include <unistd.h>

#include "sa_log.h"

log_st *log_init(char *path, int size, int level, int num)  
{  
    char new_path[128] = {0};  
    if (NULL == path || 0 == level) return NULL;  
    log_st *log = (log_st *)malloc(sizeof(log_st));  
    memset(log, 0, sizeof(log_st));  
    if (level != 3)  
    {  
        //the num use to control file naming  
        log->num = num;  
        if(num)  
            snprintf(new_path, 128, "%s%d", path, (int)time(NULL));  
        else  
            snprintf(new_path, 128, "%s.new", path);  
        if(-1 == (log->fd = open(new_path, O_RDWR|O_APPEND|O_CREAT|O_SYNC, S_IRUSR|S_IWUSR|S_IROTH)))  
        {  
            free(log);  
            log = NULL;  
            return NULL;  
        }  
    }  
    strncpy(log->path, path, 128);  
    log->size = (size > 0 ? size:0);  
    log->level = (level > 0 ? level:0);
    return log;  
}  

void log_debug(log_st *log, const char *msg, ...)  
{  
    va_list ap;  
    time_t now;  
    char *pos;  
    char _n = '\n';  
    char message[BUF_SIZE] = {0};  
    int nMessageLen = 0;  
    int sz;  
    if(NULL == log || 0 == log->level) return;  
    now = time(NULL);  
    pos = ctime(&now);  
    sz = strlen(pos);  
    pos[sz-1]=']';  
    snprintf(message, BUF_SIZE, "[%s ", pos);  
    for (pos = message; *pos; pos++);  
    sz = pos - message;
	
    va_start(ap, msg);  
    nMessageLen = vsnprintf(pos, BUF_SIZE - sz, msg, ap);  
    va_end(ap); 
	
    if (nMessageLen <= 0) {
        return;  
    }

    if (3 == log->level)  
    {  
        printf("%s\n", message);  
        return;  
    }

    if (2 == log->level) {
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
    if(NULL == log || 3 == log->level || '\0' == log->path[0]) return;  
    memset(&stat_buf, 0, sizeof(struct stat));  
    fstat(log->fd, &stat_buf);  
    if(stat_buf.st_size > log->size)  
    {  
        close(log->fd);  
        if(log->num) 
        {
            snprintf(new_path, 128, "%s%d", log->path, (int)time(NULL)); 
        }
        else  
        {  
            snprintf(bak_path, 128, "%s.bak", log->path);  
            snprintf(new_path, 128, "%s.new", log->path);  
            remove(bak_path); //delete the file *.bak first  
            rename(new_path, bak_path); //change the name of the file *.new to *.bak  
        }  
        //create a new file  
        log->fd = open(new_path, O_RDWR|O_APPEND|O_CREAT|O_SYNC, S_IRUSR|S_IWUSR|S_IROTH);  
    }  
}  


