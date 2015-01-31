

#define MAXLINE_01 4096
#define	FIFO1	"/tmp/fifo.1"
#define	FIFO2	"/tmp/fifo.2"

/* default permissions for new files This allows user-read, user-write, group-read, and other-read.*/
#define	FILE_MODE	(S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)

#define SERV_FIFO "/tmp/fifo.serv1"

void client(int, int);
void server(int, int);

