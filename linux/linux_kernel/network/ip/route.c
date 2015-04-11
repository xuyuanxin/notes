

int __init ip_rt_init(void);



void fib_add_ifaddr(struct in_ifaddr *ifa);


/*******************************************************************************
 A memory pool used to allocate new cache entries is created by ip_rt_init at 
 boot time. 
 ******************************************************************************/
void *dst_alloc(struct dst_ops *ops, struct net_device *dev,
		int initial_ref, int initial_obsolete, unsigned short flags);


int ip_route_input(struct sk_buff *skb, __be32 daddr, __be32 saddr, u8 tos, struct net_device *dev);

