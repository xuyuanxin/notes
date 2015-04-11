/*

                                  ip_rcv
                                     |
                            netfilter|NF_IP_PRE_ROUTING
                                     |
                               ip_rcv_finish
                                     |
                                 dst_input
                                     |
                                     |
                                     |
                                skb->dst->input
               --------------------------------------------
               |                                          |
            ip_forward                              ip_local_deliver(ip_defrag)
                                                          |
                                                 netfilter|NF_IP_LOCAL_IN
                                                          |
                                                 ip_local_deliver_finish  



*/


/*******************************************************************************
 


 1 inet_init -> dev_add_pack(&ip_packet_type); 注册协议处理函数
 2 netif_receive_skb 中调用
 
 ******************************************************************************/
int ip_rcv(struct sk_buff *skb, struct net_device *dev, struct packet_type *pt, struct net_device *orig_dev);


/*******************************************************************************
 Deciding whether the packet has to be locally delivered or forwarded
 Parsing and processing some of the IP options
 ******************************************************************************/
static int ip_rcv_finish(struct sk_buff *skb);


/*******************************************************************************

 ip_rcv_finish -> dst_input

 ******************************************************************************/

int ip_local_deliver(struct sk_buff *skb);


/*******************************************************************************
 find the correct protocol handler based on the protocol field of the input IP 
 packet's header and to hand the packet to that handler. At the same time, 
 @ip_local_deliver_finish needs to handle raw IP and enforce security policies if 
 they are configured. 

 ip_local_deliver_finish extracts the number of this protocol from the 8-bit 
 field of the IP header. If the @inet_protos table doesn't contain a handler for 
 this number and no raw socket is interested in the packet, the packet is dropped 
 and an ICMP unreachable message is sent back to the sender.

 ******************************************************************************/
static int ip_local_deliver_finish(struct sk_buff *skb);



/*******************************************************************************
 handle all input packets that are not addressed to the local system

 ip_rcv_finish -> dst_input

 Forwarding consists of the following steps:
 1. Process the IP options. This may involve recording the local IP address and a
 timestamp if options in the IP header require them.
 2. Make sure that the packet can be forwarded, based on the IP header fields.
 3. Decrement the Time To Live (TTL) field of the IPheader and discard the packet
 if the TTL becomes 0.
 4. Handle fragmentation if needed, based on the MTU associated with the route.
 5. Send the packet out to the outgoing device. 
 ******************************************************************************/
int ip_forward(struct sk_buff *skb);



