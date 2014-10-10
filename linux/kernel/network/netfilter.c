
NF_HOOK(
  uint8_t pf,                   /*协议族名，Netfilter架构同样可以用于IP层之外，因此这个变量还可以有诸如PF_INET6，PF_DECnet等名字*/
  unsigned int hook,            /*HOOK点的名字，对于IP层，就是取上面的五个值*/
  struct sk_buff *skb,          /**/
  struct net_device *in,        /*数据包进来的设备，以struct net_device结构表示*/
  struct net_device *out,       /*数据包出去的设备，以struct net_device结构表示*/
  int (*okfn)(struct sk_buff *))/*函数指针，当所有的该HOOK点的所有登记函数调用完后，转而走此流程*/

NF_HOOK_THRESH(
uint8_t pf, 
unsigned int hook, 
struct sk_buff *skb,
struct net_device *in, 
struct net_device *out,
int (*okfn)(struct sk_buff *), 
int thresh)/*指定通过该宏去遍历钩子函数时的优先级*/


nf_hooks


/*挂载点*/
nf_inet_hooks
nf_hook_ops
nf_hookfn


ip_rcv
ip_forward
ip_output
ip_local_deliver
ip_push_pending_frames


/*包过滤子系统iptable_filter*/
struct xt_af
struct xt_table  /*表自身的一些通用的基本信息，如表名称，所属的协议簇，所影响的hook点等等*/
struct xt_table_info /*表中规则的一些基本信息，同时在该结构的末尾指示了该表中所有规则的入口点，即表中的第一条规则*/
struct ipt_replace
struct ebt_replace_kernel

initial_table

xt_init
iptable_filter_init

iptable_filter_net_init
  ipt_register_table

	




