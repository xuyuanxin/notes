/*******************************************************************************
 RFC793指出初始序列号可以看作是一个32bit的计数器，每4ms加1。选择序列号的目的在于
 防止在网络中被延迟的分组在以后被重复传输，而导致某个连接的一端对它作错误的判断。
 ******************************************************************************/

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

/*******************************************************************************
 整个过程如下:
 客户端A发起连接，建立连接后发送"a",服务器回送"recv"，然后客户端关闭连接，随后服
 务器也关闭连接
 ******************************************************************************/

/* A send SYN  SYN占用1个序列号*/
int tcp_open_1(struct np_tcphdr *sendhdr,struct np_tcphdr *recvhdr)
{
    sendhdr->seq     = 0;   /*把自己的初始序列号告诉对方，假设是0*/ 
	sendhdr->ack_seq = 0;   /*一般指定为0，这次传输这个值没有用途*/
	sendhdr->syn     = 1;
	sendhdr->window  = 65535;
}


/* B send SYN+ACK  ACK不占用序列号*/
int tcp_open_2(struct np_tcphdr *sendhdr,struct np_tcphdr *recvhdr)
{
    sendhdr->seq     = 0;     /*initial sequence number 一般是随机生成*/  
	sendhdr->ack_seq = recvhdr->seq + 1; /*0+1，告诉对方，我下次期望接收1*/
	sendhdr->syn     = 1;	
	sendhdr->ack     = 1;	
	sendhdr->window  = 8192;/*根据情况调整窗口大小*/
}


/* A send ACK */
int tcp_open_3(struct np_tcphdr *sendhdr,struct np_tcphdr *recvhdr)
{
    sendhdr->seq     = 1;
	sendhdr->ack_seq = recvhdr->seq + 1;/*0+1，告诉对方，我下次期望接收1*/
	sendhdr->ack     = 1;
	sendhdr->window  = 212992;/*根据情况调整窗口大小*/

}


/* A 客户端A向服务器发送字符"a"*/
int tcp_send1(struct np_tcphdr *sendhdr,struct np_tcphdr *recvhdr)
{
    sendhdr->seq     = 1;
	sendhdr->ack_seq = 1;
	sendhdr->ack     = 1;
	sendhdr->psh     = 1;
	sendhdr->window  = 212992;/*根据情况调整窗口大小*/

	/*data len :2*/
}


/* B 服务器接收到"a"后，回送"recv"到客户端*/
int tcp_send2(struct np_tcphdr *sendhdr,struct np_tcphdr *recvhdr)
{
    sendhdr->seq     = 1;
	sendhdr->ack_seq = recvhdr->seq + 2;/*1+2==3*/
	sendhdr->ack     = 1;
	sendhdr->psh     = 1;
	sendhdr->window  = 65531;/*根据情况调整窗口大小*/
	/*data len :5*/	
}


/* A 接收到服务器发来的"recv"，响应ack*/
int tcp_send3(struct np_tcphdr *sendhdr,struct np_tcphdr *recvhdr)
{
    sendhdr->seq     = 3;
	sendhdr->ack_seq = recvhdr->seq + 4;/*1+5==6*/
	sendhdr->ack     = 1;
	sendhdr->window  = 212988;/*根据情况调整窗口大小*/
	/*data len :0*/	
}


/*******************************************************************************
 A 客户端A首先关闭tcp连接 发送fin
 客户端A完成它的数据发送任务后，会向服务器发送一个终止数据包，以关闭在这个方向上
 的TCP连接。该数据包中，序列号为服务器发送的上一个数据包中的确认号值，而确认号为
 服务器接收的上一个数据包中的序列号+该数据包所带的数据的大小；
 
 FIN和SYN一样，也要占一个序号。理论上服务器在TCP连接关闭时发送的终止数据包中，
 只有终止位是置1，然后客户端进行确认。但是在实际的 TCP实现中，在终止数据包中，
 确认位和终止位是同时置为1的，确认位置为1表示对最后一次传输的数据进行确认，终止
 位置为1表示关闭该方向的TCP连接。

 ******************************************************************************/
int tcp_close_1(struct np_tcphdr *sendhdr,struct np_tcphdr *recvhdr)
{
    sendhdr->seq     = 3;
	sendhdr->ack_seq = 6;	
	sendhdr->ack     = 1;
	sendhdr->fin     = 1;
	sendhdr->window  = 212988;/*根据情况调整窗口大小*/
}


/******************************************************************************* 
 B 服务器B响应ack 
 服务器收到客户端发送的终止数据包后，将对客户端发送确认信息，以关闭该方向上的TCP
 连接。这时的数据包中，序列号为第1步中的确认号值，而确认号为第1步的数据包中的序
 列号+1；
 ******************************************************************************/
int tcp_close_2(struct np_tcphdr *sendhdr,struct np_tcphdr *recvhdr)
{  
    sendhdr->seq     = 6;
	sendhdr->ack_seq = 3 + 1;/*1表示收到fin*/
	sendhdr->ack     = 1;	
	sendhdr->window  = 65533;/*根据情况调整窗口大小*/
}


/*******************************************************************************
 客户端到服务器的连接关闭了，但是服务器可以继续往客户端发送数据。发送结束后，再发
 送fin关闭连接，本例子中服务器直接关闭另一半链接

 B 服务器B发送fin
 服务器完成它的数据发送任务后，也会向客户端发送一个终止数据包，以关闭在这个方向
 上的TCP连接，该数据包中，序列号为客户端发送的上一个数据包中的确认号值，而确认号
 为服务器发送的上一个数据包中的序列号+该数据包所带数据的大小；
******************************************************************************/
int tcp_close_3(struct np_tcphdr *sendhdr,struct np_tcphdr *recvhdr)
{  
	sendhdr->seq	 = 6;/*tcp_ack_send中的acknum*/
	sendhdr->ack_seq = 4;/*目前为止收到:syn(1) "a"(2) fin(1)*/
	sendhdr->ack	 = 1;	
	sendhdr->fin     = 1;
	sendhdr->window  = 65533;/*根据情况调整窗口大小*/
}


/*******************************************************************************
 A 客户端A响应ack
 客户端收到服务器发送的终止数据包后，将对服务器发送确认信息，以关闭该方向上的TCP
 连接。这时在数据包中，序列号为第3步中的确认号值，而确认号为第3步数据包中的序列号+1；
 ******************************************************************************/
int tcp_close_4(struct np_tcphdr *sendhdr,struct np_tcphdr *recvhdr)
{  
	sendhdr->seq	 = 4;/*A发送了:syn(1) ack(0) "a"(2) fin(1)*/
	sendhdr->ack_seq = 7;/*A收到了:ack(0)+syn(1) "recv"(5) fin(1) */
	sendhdr->ack	 = 1;	
	sendhdr->window  = 212988;/*根据情况调整窗口大小*/
}

