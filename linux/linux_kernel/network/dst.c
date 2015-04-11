

static inline int dst_input(struct sk_buff *skb);


/*******************************************************************************
 All transmissions, whether generated locally or forwarded from other hosts, 
 pass through dst_output on their way to a destination host
 ******************************************************************************/
static inline int dst_output(struct sk_buff *skb);


