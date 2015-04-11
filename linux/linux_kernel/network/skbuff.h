
/******************************************************************************* 
 尽量避免数据包的拷贝，提高网络处理性能。目前linux协议栈接收数据的时候需要拷贝
 两次:数据报进入网卡驱动拷贝一次，从内核空间递交给用户空间时再拷贝一次
 ******************************************************************************/

struct sk_buff {
	/* These two members must be first. */
	struct sk_buff		*next;
	struct sk_buff		*prev;

	struct sock		*sk;
	ktime_t			tstamp;
	struct net_device	*dev;

	struct  dst_entry	*dst;
	struct	sec_path	*sp;

	/*
	 * This is the control buffer. It is free to use for every
	 * layer. Please put your private variables there. If you
	 * want to keep them across layers you have to do a skb_clone()
	 * first. This is owned by whoever has the skb queued ATM.
	 */
	char			cb[48];

/*******************************************************************************
 len表示skb管理的data buffer的总长度。通常data buffer是一个简单的线性buffer，这
 时候len就是线性buffer的数据长度。在有"paged data"情况下，data buffer不仅包括第
 一个线性的buffer，还包括多个page buffer。在这种情况下data_len表示page buffer中
 数据的长度，len是线性buffer加page buffer的长度。mac_len表示MAC头得长度。
 ******************************************************************************/
	unsigned int len,  data_len;
	__u16		 mac_len, hdr_len;
	union {
		__wsum		csum;
		struct {
			__u16	csum_start;
			__u16	csum_offset;
		};
	};
	__u32			priority;

/*
@pkt_type	eth_type_trans
  skb->pkt_type is set to PACKET_OTHERHOST when the L2 destination address of the
  frame is different from the address of the receiving interface. Normally those 
  packets are discarded by the NIC itself. However, if the interface has been put 
  into promiscuous mode, it receives all packets regardless of the destination L2 
  address and passes them up to higher layers. The kernel invokes sniffers that 
  have requested access to all packets, as described in Chapter 10. But ip_rcv is 
  not concerned with packets for other addresses and simply drops them.



*/
	__u8			local_df:1,
				cloned:1,
				ip_summed:2,
				nohdr:1,
				nfctinfo:3;
	__u8			pkt_type:3,
				fclone:2,
				ipvs_property:1,
				nf_trace:1;
	__be16			protocol;

	void			(*destructor)(struct sk_buff *skb);
#if defined(CONFIG_NF_CONNTRACK) || defined(CONFIG_NF_CONNTRACK_MODULE)
	struct nf_conntrack	*nfct;
	struct sk_buff		*nfct_reasm;
#endif
#ifdef CONFIG_BRIDGE_NETFILTER
	struct nf_bridge_info	*nf_bridge;
#endif

	int			iif;
#ifdef CONFIG_NETDEVICES_MULTIQUEUE
	__u16			queue_mapping;
#endif
#ifdef CONFIG_NET_SCHED
	__u16			tc_index;	/* traffic control index */
#ifdef CONFIG_NET_CLS_ACT
	__u16			tc_verd;	/* traffic control verdict */
#endif
#endif
	/* 2 byte hole */

#ifdef CONFIG_NET_DMA
	dma_cookie_t		dma_cookie;
#endif
#ifdef CONFIG_NETWORK_SECMARK
	__u32			secmark;
#endif

	__u32			mark;

	sk_buff_data_t		transport_header;
	sk_buff_data_t		network_header;
	sk_buff_data_t		mac_header;
	/* These elements must be at the end, see alloc_skb() for details.  */
	
/*******************************************************************************
  head							  end
  |								   |
 \|/ 							  \|/
  +-------------------------------------+
  |           |             |           |  
  | head room | packet data | tail room | 
  |           |             |           |
  +-------------------------------------+
		    /|\		    /|\
              |             |
		    data		    tail
			 
 head room   : 空闲区域，需要增加协议头从这个区域中分出一块
 packet data : 真正的数据
 tail room   : 空闲区域 如果需要增加数据从这个区域中分出一块
 ******************************************************************************/
	sk_buff_data_t	 tail; /* 实际数据的结束 */
	sk_buff_data_t	 end;  /* buffer的结束 */
	unsigned char	*head; /* buffer的开始 */
	unsigned char	*data; /* 实际数据的开始 */
	unsigned int	truesize;
	atomic_t		users;
};




/******************************************************************************* 
 This data is invariant across clones and lives at the end of the header data, 
 ie. at skb->end.

 1 用于管理paged data
 2 用于管理分片

 nr_frags
    how many frags there are active in the frags[] array.

 frag_list
    maintain a chain of SKBs organized for fragmentation purposes, it is _not_
    used for maintaining paged data.
    
 frags
    holds the frag descriptors themselves
 
 ******************************************************************************/
struct skb_shared_info 
{
    unsigned char nr_frags;
	
	__u8		tx_flags;
	unsigned short	gso_size;
	/* Warning: this field is not always filled in (UFO)! */
	unsigned short	gso_segs;
	unsigned short  gso_type;

	
	struct sk_buff	*frag_list;
	
	struct skb_shared_hwtstamps hwtstamps;
	u32		tskey;
	__be32          ip6_frag_id;

	/*
	 * Warning : all fields before dataref are cleared in __alloc_skb()
	 */
	atomic_t	dataref;

	/* Intermediate layers must ensure that destructor_arg
	 * remains valid until skb destructor */
	void *		destructor_arg;

	/* must be last field, see pskb_expand_head() */
	skb_frag_t	frags[MAX_SKB_FRAGS];
};

/*******************************************************************************
 有时希望能将保存在文件中的数据，通过socket直接发送出去，这样避免了把数据先从文件
 拷贝到缓冲区，从而提高了效率。linux采用一种"paged data"的技术，来提供这种支持。
 这种技术将文件中的数据直接映射为多个page。skb_frag_t用来管理这种page。
 ******************************************************************************/
typedef struct skb_frag_struct skb_frag_t;

struct skb_frag_struct {
	struct {
		struct page *p;
	} page;
#if (BITS_PER_LONG > 32) || (PAGE_SIZE >= 65536)
	__u32 page_offset;
	__u32 size;
#else
	__u16 page_offset;
	__u16 size;
#endif
};



