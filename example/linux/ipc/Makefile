.PHONY: fifow fifor fifoserv fifocli

fifor:
	gcc -o fifor fifo_reader.c
fifow:
	gcc -o fifow fifo_writer.c
fifoserv:
	gcc -o fifoserv fifo_server.c ipc_pub.c
fifocli:
	gcc -o fifocli fifo_client.c ipc_pub.c	
