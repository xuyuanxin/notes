
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


/* A send SYN */
int tcp_open_1(struct np_tcphdr *sendhdr,struct np_tcphdr *recvhdr)
{
    sendhdr->seq     = INITSEQNUM_A;/*把自己的初始序列号告诉对方*/ 
	sendhdr->ack_seq = ;   /*好像这个不用指定*/
	sendhdr->syn     = 1;
}

/* B send SYN+ACK */
int tcp_open_2(struct np_tcphdr *sendhdr,struct np_tcphdr *recvhdr)
{
    sendhdr->seq     = INITSEQNUM_B;/*把自己的初始序列号告诉对方*/  
	sendhdr->ack_seq = recvhdr->seq + 1; /*告诉A我收到了你的初始序列号*/
	sendhdr->syn = 1;	
	sendhdr->ack = 1;
}

/* A send ACK */
int tcp_open_3(struct np_tcphdr *sendhdr,struct np_tcphdr *recvhdr)
{
    sendhdr->seq     = INITSEQNUM_A + 1 ;
	sendhdr->ack_seq = INITSEQNUM_B + 1;/*告诉B我收到了你的初始序列号*/ 
	sendhdr->ack     = 1;
}

/*三次握手后，连接建立。双发都知道了对方的初始序列号，往后可以发送数据了*/
