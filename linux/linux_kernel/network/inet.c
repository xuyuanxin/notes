

/* 系统初始化时用来管理协议族初始化的结构体 */
struct net_proto_family {
	int		family; /* 协议族的宏定义，如PF_INET */
	int		(*create)(struct net *net, struct socket *sock,int protocol, int kern);/* 协议族对应的初始化函数指针 */
	struct module	*owner;
};


/* 下面结构体是协议族操作集结构体定义 */
struct proto_ops 
{
int		family;
struct module	*owner;
int		(*release)   (struct socket *sock);
int		(*bind)	     (struct socket *sock,
			      struct sockaddr *myaddr,
			      int sockaddr_len);
int		(*connect)   (struct socket *sock,
			      struct sockaddr *vaddr,
			      int sockaddr_len, int flags);
int		(*socketpair)(struct socket *sock1,
			      struct socket *sock2);
int		(*accept)    (struct socket *sock,
			      struct socket *newsock, int flags);
int		(*getname)   (struct socket *sock,
			      struct sockaddr *addr,
			      int *sockaddr_len, int peer);
unsigned int	(*poll)	     (struct file *file, struct socket *sock,
			      struct poll_table_struct *wait);
int		(*ioctl)     (struct socket *sock, unsigned int cmd,
			      unsigned long arg);
#ifdef CONFIG_COMPAT
int	 	(*compat_ioctl) (struct socket *sock, unsigned int cmd,
			      unsigned long arg);
#endif
int		(*listen)    (struct socket *sock, int len);
int		(*shutdown)  (struct socket *sock, int flags);
int		(*setsockopt)(struct socket *sock, int level,
			      int optname, char __user *optval, unsigned int optlen);
int		(*getsockopt)(struct socket *sock, int level,
			      int optname, char __user *optval, int __user *optlen);
#ifdef CONFIG_COMPAT
int		(*compat_setsockopt)(struct socket *sock, int level,
			      int optname, char __user *optval, unsigned int optlen);
int		(*compat_getsockopt)(struct socket *sock, int level,
			      int optname, char __user *optval, int __user *optlen);
#endif
int		(*sendmsg)   (struct kiocb *iocb, struct socket *sock,
			      struct msghdr *m, size_t total_len);
/* Notes for implementing recvmsg:
 * ===============================
 * msg->msg_namelen should get updated by the recvmsg handlers
 * iff msg_name != NULL. It is by default 0 to prevent
 * returning uninitialized memory to user space.  The recvfrom
 * handlers can assume that msg.msg_name is either NULL or has
 * a minimum size of sizeof(struct sockaddr_storage).
 */
int		(*recvmsg)   (struct kiocb *iocb, struct socket *sock,
			      struct msghdr *m, size_t total_len,
			      int flags);
int		(*mmap)	     (struct file *file, struct socket *sock,
			      struct vm_area_struct * vma);
ssize_t		(*sendpage)  (struct socket *sock, struct page *page,
			      int offset, size_t size, int flags);
ssize_t 	(*splice_read)(struct socket *sock,  loff_t *ppos,
			       struct pipe_inode_info *pipe, size_t len, unsigned int flags);
int		(*set_peek_off)(struct sock *sk, int val);
}

static const struct net_proto_family inet_family_ops = {
	.family = PF_INET,
	.create = inet_create,
	.owner	= THIS_MODULE,
};

/* TCP协议在INET层操作集inet_stream_ops */
const struct proto_ops inet_stream_ops = {
	.family		   = PF_INET,
	.owner		   = THIS_MODULE,
	.release	   = inet_release,
	.bind		   = inet_bind,
	.connect	   = inet_stream_connect,
	.socketpair	   = sock_no_socketpair,
	.accept		   = inet_accept,
	.getname	   = inet_getname,
	.poll		   = tcp_poll,
	.ioctl		   = inet_ioctl,
	.listen		   = inet_listen,
	.shutdown	   = inet_shutdown,
	.setsockopt	   = sock_common_setsockopt,
	.getsockopt	   = sock_common_getsockopt,
	.sendmsg	   = inet_sendmsg,
	.recvmsg	   = inet_recvmsg,
	.mmap		   = sock_no_mmap,
	.sendpage	   = inet_sendpage,
	.splice_read	   = tcp_splice_read,
#ifdef CONFIG_COMPAT
	.compat_setsockopt = compat_sock_common_setsockopt,
	.compat_getsockopt = compat_sock_common_getsockopt,
	.compat_ioctl	   = inet_compat_ioctl,
#endif
}

/* UDP协议在INET层操作集inet_dgram_ops */
const struct proto_ops inet_dgram_ops = {
	.family		   = PF_INET,
	.owner		   = THIS_MODULE,
	.release	   = inet_release,
	.bind		   = inet_bind,
	.connect	   = inet_dgram_connect,
	.socketpair	   = sock_no_socketpair,
	.accept		   = sock_no_accept,
	.getname	   = inet_getname,
	.poll		   = udp_poll,
	.ioctl		   = inet_ioctl,
	.listen		   = sock_no_listen,
	.shutdown	   = inet_shutdown,
	.setsockopt	   = sock_common_setsockopt,
	.getsockopt	   = sock_common_getsockopt,
	.sendmsg	   = inet_sendmsg,
	.recvmsg	   = inet_recvmsg,
	.mmap		   = sock_no_mmap,
	.sendpage	   = inet_sendpage,
#ifdef CONFIG_COMPAT
	.compat_setsockopt = compat_sock_common_setsockopt,
	.compat_getsockopt = compat_sock_common_getsockopt,
	.compat_ioctl	   = inet_compat_ioctl,
#endif
}

