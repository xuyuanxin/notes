/*
                               l4 protocols
                               
    ip_push_pending_frames      ip_queue_xmit        raw_send_hdrinc



                      
                         |
                         |
                         |
                     dst_output
                     skb->dst->output
                         |
                         |
      ------------------------------------ 
      |                  |                |
  ip_mc_output      ip_fragment      ip_output
      |                  |                |
      -------------------------------------
                         |
                  ip_finish_output
                         |
                netfilter|NF_IP_POST_ROUTING
                         |
                    dev_queue_xmit
                         |
                         |
                         |
                    hard_start_xmit
                      


*/

/*******************************************************************************
 used by TCP and SCTP 
 @ipfragok
 A flag used mainly by SCTP to say whether fragmentation is allowed.
 
 It receives only two input parameters, and all the information needed to process 
 the packet is accessible (directly or indirectly) through skb

 ******************************************************************************/
int ip_queue_xmit(struct sk_buff *skb, int ipfragok);



/* dst_output */
int ip_output(struct sk_buff *skb);


static int ip_finish_output(struct sk_buff *skb);





/*
 *	ip_append_data() and ip_append_page() can make one large IP datagram
 *	from many pieces of data. Each pieces will be holded on the socket
 *	until ip_push_pending_frames() is called. Each piece can be a page
 *	or non-page data.
 *
 *	Not only UDP, other transport protocols - e.g. raw sockets - can use
 *	this interface potentially.
 *
 *	LATER: length must be adjusted by pad at tail, when it is required.
 
 This is the function used by those L4 protocols that want to buffer data for 
 transmission.this function does not transmit data, but places it in conveniently 
 sized buffers for later functions to form into fragments (if necessary) and 
 transmit. Thus, it does not create or manipulate any IP header. To flush and 
 transmit the data buffered by ip_append_data, the L4 layer has to explicitly 
 call @ip_push_pending_frames, which also takes care of the IP header.

 
 */
int ip_append_data(struct sock *sk,
int getfrag(void *from, char *to, int offset, int len,int odd, struct sk_buff *skb),
void *from, int length, int transhdrlen,struct ipcm_cookie *ipc, struct rtable *rt,unsigned int flags);


