
#define INITSEQNUM_A 500 /*A的 initial sequence number 一般是随机生成*/
#define INITSEQNUM_B 300 /*B的 initial sequence number 一般是随机生成*/

/*******************************************************************************
                   Establishing A TCP Connection
 *******************************************************************************                 
 假设A主动向B发起TCP连接(可以同时发起连接，这里先说明最简单的情况:A发起B接收)
 1 首先A调用 tcp_open_1 发起连接
 2 B收到SYN后，调用 tcp_open_2 回应A
 3 A收到B的回应后，调用 tcp_open_3 回应B，连接建立。

 三次握手的目的
 1 分别告诉对方自己的"初始序列号"
 *******************************************************************************/


/* A send SYN  SYN占用1个序列号*/
int tcp_open_1(struct np_tcphdr *sendhdr,struct np_tcphdr *recvhdr)
{
    sendhdr->seq     = INITSEQNUM_A;/*把自己的初始序列号告诉对方*/ 
	sendhdr->ack_seq = 0;   /*一般指定为0，这次传输这个值没有用途*/
	sendhdr->syn     = 1;
}

/* B send SYN+ACK  ACK不占用序列号*/
int tcp_open_2(struct np_tcphdr *sendhdr,struct np_tcphdr *recvhdr)
{
    sendhdr->seq     = INITSEQNUM_B;     /*把自己的初始序列号告诉对方*/  
	sendhdr->ack_seq = recvhdr->seq + 1; /*告诉A，我期望下次收到这个序列号*/
	sendhdr->syn = 1;	
	sendhdr->ack = 1;
}

/* A send ACK */
int tcp_open_3(struct np_tcphdr *sendhdr,struct np_tcphdr *recvhdr)
{
    sendhdr->seq     = INITSEQNUM_A + 1;
	sendhdr->ack_seq = recvhdr->seq + 1;/*告诉B，我期望下次收到这个序列号*/
	sendhdr->ack     = 1;
}

/*三次握手后，连接建立。双发都知道了对方的初始序列号，往后可以发送数据了。
  建立连接后，A第一次向B发数据
  A  seq:INITSEQNUM_A + 1    ack:INITSEQNUM_B + 1
  */

/* A 假设A接着发送http get ，其数据长度是1150，即封装在tcp后面的数据长度是1150*/
int http_get_send(struct np_tcphdr *sendhdr,struct np_tcphdr *recvhdr)
{
    sendhdr->seq     = INITSEQNUM_A + 1;
	sendhdr->ack_seq = INITSEQNUM_B + 1;
	//sendhdr->ack     = 1;

	/*http data len :1150*/
}

/* B 返回http ack*/
int http_ack_send(struct np_tcphdr *sendhdr,struct np_tcphdr *recvhdr)
{
    sendhdr->seq     = INITSEQNUM_B + 1;
	sendhdr->ack_seq = recvhdr->seq + 1150;/*http data len 1150*/
}

/*A 再发数据 seq: INITSEQNUM_A + 1 + 1150 */
