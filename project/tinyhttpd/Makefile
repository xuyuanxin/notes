all: httpd
#gcc -W -Wall -lsocket -lpthread -o httpd httpd.c
httpd: httpd.c
	gcc -W -Wall -o httpd httpd_linux.c -lpthread

clean:
	rm httpd

