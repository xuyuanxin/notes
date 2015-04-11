

#define AF_INET		2	/* Internet IP Protocol 	*/


/* 内核中的PF_***和AF_***其实可以混用 */
#define PF_INET		AF_INET 

/**
 * enum sock_type - Socket types
 * @SOCK_STREAM: stream (connection) socket
 * @SOCK_DGRAM: datagram (conn.less) socket
 * @SOCK_RAW: raw socket
 * @SOCK_RDM: reliably-delivered message
 * @SOCK_SEQPACKET: sequential packet socket
 * @SOCK_DCCP: Datagram Congestion Control Protocol socket
 * @SOCK_PACKET: linux specific way of getting packets at the dev level.
 *		  For writing rarp and other similar things on the user level.
 *
 * When adding some new socket type please
 * grep ARCH_HAS_SOCKET_TYPE include/asm-* /socket.h, at least MIPS
 * overrides this enum for binary compat reasons.
 */
enum sock_type {
	SOCK_STREAM	= 1,
	SOCK_DGRAM	= 2,
	SOCK_RAW	= 3,
	SOCK_RDM	= 4,
	SOCK_SEQPACKET	= 5,
	SOCK_DCCP	= 6,
	SOCK_PACKET	= 10,
};


/**
 *  struct socket - general BSD socket
 *  @state: socket state (%SS_CONNECTED, etc)
 *  @type: socket type (%SOCK_STREAM, etc)
 *  @flags: socket flags (%SOCK_ASYNC_NOSPACE, etc)
 *  @ops: protocol specific socket operations
 *  @file: File back pointer for gc
 *  @sk: internal networking protocol agnostic socket representation
 *  @wq: wait queue for several uses

 协议族层析的套接字结构体（BSD Socket）定义

 */
struct socket {
	socket_state		state;

	kmemcheck_bitfield_begin(type);
	short			type; /* enum sock_type */
	kmemcheck_bitfield_end(type);

	unsigned long		flags;

	struct socket_wq __rcu	*wq;

	struct file		*file;
	struct sock		*sk;
	const struct proto_ops	*ops; /* inet_stream_ops 等*/
};


/* Networking protocol blocks we attach to sockets.
 * socket layer -> transport layer interface
 * transport -> network interface is defined by struct inet_proto
 该结构体和proto_ops的区别是：该结构体和具体的传输层协议相关，其中的函数指针指向对应的协议的相应的操作函数。

 */
struct proto {
	void			(*close)(struct sock *sk,
					long timeout);
	int			(*connect)(struct sock *sk,
					struct sockaddr *uaddr,
					int addr_len);
	int			(*disconnect)(struct sock *sk, int flags);

	struct sock *		(*accept)(struct sock *sk, int flags, int *err);

	int			(*ioctl)(struct sock *sk, int cmd,
					 unsigned long arg);
	int			(*init)(struct sock *sk);
	void			(*destroy)(struct sock *sk);
	void			(*shutdown)(struct sock *sk, int how);
	int			(*setsockopt)(struct sock *sk, int level,
					int optname, char __user *optval,
					unsigned int optlen);
	int			(*getsockopt)(struct sock *sk, int level,
					int optname, char __user *optval,
					int __user *option);
#ifdef CONFIG_COMPAT
	int			(*compat_setsockopt)(struct sock *sk,
					int level,
					int optname, char __user *optval,
					unsigned int optlen);
	int			(*compat_getsockopt)(struct sock *sk,
					int level,
					int optname, char __user *optval,
					int __user *option);
	int			(*compat_ioctl)(struct sock *sk,
					unsigned int cmd, unsigned long arg);
#endif
	int			(*sendmsg)(struct kiocb *iocb, struct sock *sk,
					   struct msghdr *msg, size_t len);
	int			(*recvmsg)(struct kiocb *iocb, struct sock *sk,
					   struct msghdr *msg,
					   size_t len, int noblock, int flags,
					   int *addr_len);
	int			(*sendpage)(struct sock *sk, struct page *page,
					int offset, size_t size, int flags);
	int			(*bind)(struct sock *sk,
					struct sockaddr *uaddr, int addr_len);

	int			(*backlog_rcv) (struct sock *sk,
						struct sk_buff *skb);

	void		(*release_cb)(struct sock *sk);

	/* Keeping track of sk's, looking them up, and port selection methods. */
	void			(*hash)(struct sock *sk);
	void			(*unhash)(struct sock *sk);
	void			(*rehash)(struct sock *sk);
	int			(*get_port)(struct sock *sk, unsigned short snum);
	void			(*clear_sk)(struct sock *sk, int size);

	/* Keeping track of sockets in use */
#ifdef CONFIG_PROC_FS
	unsigned int		inuse_idx;
#endif

	bool			(*stream_memory_free)(const struct sock *sk);
	/* Memory pressure */
	void			(*enter_memory_pressure)(struct sock *sk);
	atomic_long_t		*memory_allocated;	/* Current allocated memory. */
	struct percpu_counter	*sockets_allocated;	/* Current number of sockets. */
	/*
	 * Pressure flag: try to collapse.
	 * Technical note: it is used by multiple contexts non atomically.
	 * All the __sk_mem_schedule() is of this nature: accounting
	 * is strict, actions are advisory and have some latency.
	 */
	int			*memory_pressure;
	long			*sysctl_mem;
	int			*sysctl_wmem;
	int			*sysctl_rmem;
	int			max_header;
	bool			no_autobind;

	struct kmem_cache	*slab;
	unsigned int		obj_size;
	int			slab_flags;

	struct percpu_counter	*orphan_count;

	struct request_sock_ops	*rsk_prot;
	struct timewait_sock_ops *twsk_prot;

	union {
		struct inet_hashinfo	*hashinfo;
		struct udp_table	*udp_table;
		struct raw_hashinfo	*raw_hash;
	} h;

	struct module		*owner;

	char			name[32];

	struct list_head	node;
#ifdef SOCK_REFCNT_DEBUG
	atomic_t		socks;
#endif
#ifdef CONFIG_MEMCG_KMEM
	/*
	 * cgroup specific init/deinit functions. Called once for all
	 * protocols that implement it, from cgroups populate function.
	 * This function has to setup any files the protocol want to
	 * appear in the kmem cgroup filesystem.
	 */
	int			(*init_cgroup)(struct mem_cgroup *memcg,
					       struct cgroup_subsys *ss);
	void			(*destroy_cgroup)(struct mem_cgroup *memcg);
	struct cg_proto		*(*proto_cgroup)(struct mem_cgroup *memcg);
#endif
}

