/* http://vger.kernel.org/~davem/skb_data.html */

/*http://www.91linux.com/html/article/kernel/20090730/17655.html*/


/*******************************************************************************
@size:数据区的大小，实际申请的大小是 size + sizeof(struct skb_shared_info)

head
 |
\|/
 +-------------------------------------------------------------------+
 |           |       |                 |       | kmalloc(size) might |
 |  raw size | align | skb_shared_info | align | give us more room   |
 |           |       |                 |       | than requested.     |
 +---------------------------------------------+---------------------+
/|\                                                                 /|\
 |                                                                   |
tail                                                        end(skb->tail + size)
data
 
*******************************************************************************/
static inline struct sk_buff *alloc_skb(unsigned int size,gfp_t priority);



/*******************************************************************************
 skb_reserve - adjust headroom
 @skb: buffer to alter
 @len: bytes to move

 Increase the headroom of an empty &sk_buff by reducing the tail room. This is 
 only allowed for an empty buffer.

 Typically, when building output packets, we reserve enough bytes for the maximum 
 amount of header space we think we'll need. Most IPV4 protocols can do this by 
 using the socket value sk->sk_prot->max_header.

 When setting up receive packets that an ethernet device will DMA into, we 
 typically call skb_reserve(skb, NET_IP_ALIGN). By default NET_IP_ALIGN is defined 
 to '2'. This makes it so that, after the ethernet header, the protocol header will 
 be aligned on at least a 4-byte boundary. Nearly all of the IPV4 and IPV6 protocol 
 processing assumes that the headers are properly aligned.

 head         data
  |            |
 \|/          \|/
  +-------------------------+
  |            |            |  skb->data += len;
  |  head room |  tail room |  skb->tail += len;
  |            |            |
  +-------------------------+
              /|\          /|\
  |<-- len  -->|            |
 old tail     tail          end
 ******************************************************************************/
static inline void skb_reserve(struct sk_buff *skb, int len);



/*******************************************************************************
 skb_put - add data to a buffer
 @skb: buffer to use
 @len: amount of data to add

 This function extends the used data area of the buffer. If this would exceed the 
 total buffer size the kernel will panic. A pointer to the first byte of the extra 
 data is returned.

 skb_put() advances 'skb->tail' by the specified number of bytes, it also increments 
 'skb->len' by that number of bytes as well. This routine must not be called on 
 a SKB that has any paged data. You must also be sure that there is enough tail 
 room in the SKB for the amount of bytes you are trying to put. Both of these 
 conditions are checked for by skb_put() and an assertion failure will trigger 
 if either rule is violated.

 head         data
  |            |
 \|/          \|/
  +-----------------------------------+
  |            |           |          |     skb->len  += len;
  |  head room | user data |tail room |     skb->tail += len;
  |            |           |          |
  +-----------------------------------+
                          /|\        /|\
               |<-- len -->|          |
            old tail      tail        end
 ******************************************************************************/
unsigned char *skb_put(struct sk_buff *skb, unsigned int len);


/*******************************************************************************
 skb_push - add data to the start of a buffer
 @skb: buffer to use
 @len: amount of data to add

 This function extends the used data area of the buffer at the buffer start. If 
 this would exceed the total buffer headroom the kernel will panic. A pointer to 
 the first byte of the extra data is returned.

 skb_push() will decrement the 'skb->data' pointer by the specified number of bytes. 
 It will also increment 'skb->len' by that number of bytes as well. The caller must 
 make sure there is enough head room for the push being performed. This condition 
 is checked for by skb_push() and an assertion failure will trigger if this rule 
 is violated.

  head        data       old data
  |            |<-- len --> |
 \|/          \|/          \|/
  +------------------------------------------------+   skb_push(skb, sizeof(struct udphdr));
  |            |            |           |          |     
  |  head room | udp header | user data |tail room |   skb->len  += len;
  |            |            |           |          |   skb->data -= len;
  +------------------------------------------------+
                                       /|\        /|\
                                        |          |
                                       tail        end
 ******************************************************************************/
unsigned char *skb_push(struct sk_buff *skb, unsigned int len);





/*******************************************************************************
 如果data_len非0，这个sk_buffer管理的数据就是"非线性"的。skb->len-skb->data_len
 就是非paged数据的长度。在有"paged data"情况下，skb_put()就无法使用了，必须使用
 pskb_put()
 ******************************************************************************/
static inline unsigned int skb_headlen(const struct sk_buff *skb);



/*******************************************************************************
 * skb_fill_page_desc - initialise a paged fragment in an skb
 * @skb: buffer containing fragment to be initialised
 * @i: paged fragment index to initialise
 * @page: the page to use for this fragment
 * @off: the offset to the data with @page
 * @size: the length of the data
 *
 * As per __skb_fill_page_desc() -- initialises the @i'th fragment of
 * @skb to point to @size bytes at offset @off within @page. In
 * addition updates @skb such that @i is the last fragment.
 *
 * Does not take any additional reference on the fragment.
 ******************************************************************************/
void skb_fill_page_desc(struct sk_buff *skb, int i,struct page *page, int off, int size);


/*******************************************************************************
 当数据包进入协议栈往上层递交的过程中，比如在IP层，它需要对数据包的IP头部进行分
 析，比如头部合法性等，这时候就需要确保IP头部在线性缓冲区中，这样才能对它进行分
 析，如果在非线性缓冲区中，而非线性缓冲区是unmapped的page，因此就需要从这些
 unmapped page当中把数据复制到线性缓冲区中。这个艰难的工作就是__pskb_pull_tail完
 成的。

 例子:ip_rcv
 ******************************************************************************/
static inline int pskb_may_pull(struct sk_buff *skb, unsigned int len);




/**
 *	skb_share_check - check if buffer is shared and if so clone it
 *	@skb: buffer to check
 *	@pri: priority for memory allocation
 *
 *	If the buffer is shared the buffer is cloned and the old copy
 *	drops a reference. A new clone with a single reference is returned.
 *	If the buffer is not shared the original buffer is returned. When
 *	being called from interrupt status or with spinlocks held pri must
 *	be GFP_ATOMIC.
 *
 *	NULL is returned on a memory allocation failure.

 skb_share_check checks whether the reference count of the packet is bigger than 1,
 which means that other parts of the kernel have references to the buffer. As 
 discussed in earlier chapters, sniffers and other users might be interested in 
 packets, so each packet contains a reference count. The netif_receive_skb function, 
 which is the one that calls ip_rcv, increments the reference count before it 
 calls a protocol handler. If the handler sees a reference count bigger than 1, 
 it creates its own copy of the buffer so that it can modify the packet. Any 
 following handlers will receive the original, unchanged buffer.  
 */
struct sk_buff *skb_share_check(struct sk_buff *skb,gfp_t pri);


