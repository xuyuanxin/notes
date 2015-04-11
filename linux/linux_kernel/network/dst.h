struct dst_entry
{
	struct rcu_head		rcu_head;
	struct dst_entry	*child;
	struct net_device       *dev;
	short			error;
	short			obsolete;
	int			flags;
#define DST_HOST		1
#define DST_NOXFRM		2
#define DST_NOPOLICY		4
#define DST_NOHASH		8
	unsigned long		expires;

	unsigned short		header_len;	/* more space at head required */
	unsigned short		nfheader_len;	/* more non-fragment space at head required */
	unsigned short		trailer_len;	/* space to reserve at tail */

	u32			metrics[RTAX_MAX];
	struct dst_entry	*path;

	unsigned long		rate_last;	/* rate limiting for ICMP */
	unsigned long		rate_tokens;

	struct neighbour	*neighbour;
	struct hh_cache		*hh;
	struct xfrm_state	*xfrm;

/*
 @input   ip_route_input
 ip_forward ip_local_deliver 

 @output
 ip_output if the destination address is unicast 
 ip_mc_output if it is multicast 
 */
    int			(*input)(struct sk_buff*);  
    int			(*output)(struct sk_buff*);

#ifdef CONFIG_NET_CLS_ROUTE
	__u32			tclassid;
#endif

	struct  dst_ops	        *ops;
		
	unsigned long		lastuse;
	atomic_t		__refcnt;	/* client references	*/
	int			__use;
	union {
		struct dst_entry *next;
		struct rtable    *rt_next;
		struct rt6_info   *rt6_next;
		struct dn_route  *dn_next;
	};
	char			info[0];
}

