.PHONY: tcpc tcps  tcpsp udpc udps utcps clean

tcpc:
	gcc -o tcpc tcp_client.c cliserv_pub.c
tcps:
	gcc -o tcps tcp_server.c cliserv_pub.c
tcpsp:
	gcc -o tcpsp tcp_server_poll.c cliserv_pub.c
udpc:
	gcc -o udpc udp_client.c cliserv_pub.c
udps:
	gcc -o udps udp_server.c cliserv_pub.c
tus:
	gcc -o tus tcpudpserv.c cliserv_pub.c
utcps:
	gcc -o utcps unix_domain_tcpserv.c cliserv_pub.c
utcpc:
	gcc -o utcpc unix_domain_tcpcli.c cliserv_pub.c