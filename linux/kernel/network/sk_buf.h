/*******************************************************************************
@dev
    Device we arrived on/are leaving by

@head
    指向一个已分配空间的头部，包处理过程中固定。

@end 
    指向一个已分配空间的尾部，包处理过程中固定。

@data
    指向有效数据的头部，包处理过程中变动。

@tail
   指向有效数据的尾部，包处理过程中变动。
    


*******************************************************************************/

struct sk_buff 
{
	/* These two members must be first. */
	struct sk_buff		*next;
	struct sk_buff		*prev;

	union {
		ktime_t		tstamp;
		struct skb_mstamp skb_mstamp;
	};

	struct sock		*sk;
	struct net_device	*dev;

	/*
	 * This is the control buffer. It is free to use for every
	 * layer. Please put your private variables there. If you
	 * want to keep them across layers you have to do a skb_clone()
	 * first. This is owned by whoever has the skb queued ATM.
	 */
	char			cb[48] __aligned(8);

	unsigned long		_skb_refdst;
#ifdef CONFIG_XFRM
	struct	sec_path	*sp;
#endif
	unsigned int		len,
				data_len;
	__u16			mac_len,
				hdr_len;
	union {
		__wsum		csum;
		struct {
			__u16	csum_start;
			__u16	csum_offset;
		};
	};
	__u32			priority;
	kmemcheck_bitfield_begin(flags1);
	__u8			ignore_df:1,
				cloned:1,
				ip_summed:2,
				nohdr:1,
				nfctinfo:3;
	__u8			pkt_type:3,
				fclone:2,
				ipvs_property:1,
				peeked:1,
				nf_trace:1;
	kmemcheck_bitfield_end(flags1);
	__be16			protocol;

	void			(*destructor)(struct sk_buff *skb);
#if defined(CONFIG_NF_CONNTRACK) || defined(CONFIG_NF_CONNTRACK_MODULE)
	struct nf_conntrack	*nfct;
#endif
#ifdef CONFIG_BRIDGE_NETFILTER
	struct nf_bridge_info	*nf_bridge;
#endif

	int			skb_iif;

	__u32			hash;

	__be16			vlan_proto;
	__u16			vlan_tci;

#ifdef CONFIG_NET_SCHED
	__u16			tc_index;	/* traffic control index */
#ifdef CONFIG_NET_CLS_ACT
	__u16			tc_verd;	/* traffic control verdict */
#endif
#endif

	__u16			queue_mapping;
	kmemcheck_bitfield_begin(flags2);
#ifdef CONFIG_IPV6_NDISC_NODETYPE
	__u8			ndisc_nodetype:2;
#endif
	__u8			pfmemalloc:1;
	__u8			ooo_okay:1;
	__u8			l4_hash:1;
	__u8			sw_hash:1;
	__u8			wifi_acked_valid:1;
	__u8			wifi_acked:1;
	__u8			no_fcs:1;
	__u8			head_frag:1;
	/* Encapsulation protocol and NIC drivers should use
	 * this flag to indicate to each other if the skb contains
	 * encapsulated packet or not and maybe use the inner packet
	 * headers if needed
	 */
	__u8			encapsulation:1;
	__u8			encap_hdr_csum:1;
	__u8			csum_valid:1;
	__u8			csum_complete_sw:1;
	/* 2/4 bit hole (depending on ndisc_nodetype presence) */
	kmemcheck_bitfield_end(flags2);

#if defined CONFIG_NET_DMA || defined CONFIG_NET_RX_BUSY_POLL
	union {
		unsigned int	napi_id;
		dma_cookie_t	dma_cookie;
	};
#endif
#ifdef CONFIG_NETWORK_SECMARK
	__u32			secmark;
#endif
	union {
		__u32		mark;
		__u32		dropcount;
		__u32		reserved_tailroom;
	};

	__be16			inner_protocol;
	__u16			inner_transport_header;
	__u16			inner_network_header;
	__u16			inner_mac_header;
	__u16			transport_header;
	__u16			network_header;
	__u16			mac_header;
	/* These elements must be at the end, see alloc_skb() for details.  */
	sk_buff_data_t		tail;
	sk_buff_data_t		end;
	unsigned char		*head,
				*data;
	unsigned int		truesize;
	atomic_t		users;
}

void __init skb_init(void);


/*******************************************************************************
@size:套接字缓冲区所对应的数据区的大小


*******************************************************************************/
struct sk_buff *__alloc_skb(unsigned int size, gfp_t gfp_mask,int flags, int node);

static inline struct sk_buff *dev_alloc_skb(unsigned int length);

void kfree_skb(struct sk_buff *skb);


/**
 *	skb_put - add data to a buffer
 *	@skb: buffer to use
 *	@len: amount of data to add
 *
 *	This function extends the used data area of the buffer. If this would
 *	exceed the total buffer size the kernel will panic. A pointer to the
 *	first byte of the extra data is returned.
 */
unsigned char *skb_put(struct sk_buff *skb, unsigned int len);

/**
 *	skb_push - add data to the start of a buffer
 *	@skb: buffer to use
 *	@len: amount of data to add
 *
 *	This function extends the used data area of the buffer at the buffer
 *	start. If this would exceed the total buffer headroom the kernel will
 *	panic. A pointer to the first byte of the extra data is returned.
 */
unsigned char *skb_push(struct sk_buff *skb, unsigned int len);


/**
 *	skb_headroom - bytes at buffer head
 *	@skb: buffer to check
 *
 *	Return the number of bytes of free space at the head of an &sk_buff.
 */
static inline unsigned int skb_headroom(const struct sk_buff *skb)
{
	return skb->data - skb->head;
}

/**
 *	skb_tailroom - bytes at buffer end
 *	@skb: buffer to check
 *
 *	Return the number of bytes of free space at the tail of an sk_buff
 */
static inline int skb_tailroom(const struct sk_buff *skb)
{
	return skb_is_nonlinear(skb) ? 0 : skb->end - skb->tail;
}

/**
 *	skb_reserve - adjust headroom
 *	@skb: buffer to alter
 *	@len: bytes to move
 *
 *	Increase the headroom of an empty &sk_buff by reducing the tail
 *	room. This is only allowed for an empty buffer.
 */
static inline void skb_reserve(struct sk_buff *skb, int len)
{
	skb->data += len;
	skb->tail += len;
}

