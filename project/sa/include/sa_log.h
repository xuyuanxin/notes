/*-----------------------------------------------------------------------------------
 log: sa_log.c sa_log.h
 dep: null
 ----------------------------------------------------------------------------------*/

#ifndef __SA_LOG_H__
#define __SA_LOG_H__

/*
 http://blog.csdn.net/shanzhizi/article/details/17844509

 该套函数由五部分组成，分别是宏变量BUF_SIZE、结构体log_st、log_init函数、log_debug函数和log_checksize函数。
 其中宏变量BUF_SIZE用来限制每次输出的日志的最大长度；
 结构体用来存储用户需求，包括文件路径、文件描述符号、单个文件最大大小、输出方式标志、文件命名标志等；
 log_init函数用来完成用户需求录入、文件创建等功能，在mian函数的开始调用一次即可；
 log_debug函数的功能跟printf很类似，是在printf基础上进行的扩充，实现将日志输出到屏幕或者写入到文件，
 在需要打印日志的地方调用该函数；
 log_checksize函数用来检测日志文件大小是否超过最大大小限制，它需要您定时或者定点调用它，
 如果一直不调用，则日志文件将不受指定的最大大小限制。
 */


#define BUF_SIZE 1024  

typedef struct _log_st log_st;  
struct _log_st  
{  
    char path[128];  
    int fd;  
    int size;  
    int level;  
    int num;  
};  



/*-----------------------------------------------------------------------------------
 @path: 您要存储的文件路径
 @size: 单个文件的最大大小，如果超过该大小则新建新的文件用来存储；
 @level: 
   日志输出方式，0表示日志既不输出到屏幕也不创建文件和保存到文件，1表示日志保存到文件
   但不输出到屏幕，2表示日志既输出到屏幕也保存到文件，3表示日志只输出到文件而不创建文
   件和存入文件；
 @num: 
   日志文件命名方式，非0表示以(int)time(NULL)作为文件名来保存文件，文件数量随着日志量的
   递增而递增；0表示以“.new”和“.bak”为文件名来保存文件，文件数量不超过两个，随着日
   志量的递增，旧的日志文件将被新的覆盖，更直观的说就是说.new”和“.bak”文件只保存最近
   的日志。
 ----------------------------------------------------------------------------------*/
log_st *log_init(char *path, int size, int level, int num);

void log_debug(log_st *log, const char *msg, ...);


#endif
