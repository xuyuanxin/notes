/*

 Not all the L4 protocols are implemented in kernel space.an application can use 
 raw sockets, as shown earlier in the Zebra code, to bypass L4 in kernel space. 
 Some L4 protocols, therefore, are implemented entirely in kernel space (e.g., 
 TCPand UDP), some entirely in user space (e.g., OSPF), and some partially in 
 kernel space and partially in user space(e.g., ICMP). 

 When you ping a host, the ping application generates ICMP packets and passes 
 them to the kernel as IP packets. The kernel does not touch the ICMP header. 
 However, the receiving host processes ICMP_ECHO_REQUEST in kernel space by 
 replying back with an ICMP_ECHO_REPLY message.

*/


/*******************************************************************************
 @prot: tcp_protocol etc
 @protocol: IPPROTO_UDP etc
 fun:Add a protocol handler to the hash tables

 inet_init -> inet_add_protocol
 ip_local_deliver_finish 调用这几加入的协议回调函数
 ******************************************************************************/
int inet_add_protocol(struct net_protocol *prot, unsigned char protocol);

