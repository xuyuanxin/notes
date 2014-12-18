
struct net_device  /*描述网络设备的结构,存储网络设备的所有信息*/

alloc_netdev
netdev_priv  /* 获取私有数据区的指针*/

/*******************************************************************************
@sizeof_priv:驱动程序的私有数据区大小
@name:网络接口的名称，用户空间可见
@setup:回调函数，初始化一些结构体中的变量

function:分配一个net_device类型的对象来代表所管理的网卡设备
*******************************************************************************/

struct net_device *alloc_netdev_mqs(int sizeof_priv, const char *name,
		unsigned char name_assign_type,
		void (*setup)(struct net_device *),
		unsigned int txqs, unsigned int rxqs);

/**
 *	free_netdev - free network device
 *	@dev: device
 *
 *	This function does the last stage of destroying an allocated device
 * 	interface. The reference to the device object is released.
 *	If this is the last reference then it will be freed.
 */
void free_netdev(struct net_device *dev);


#define alloc_etherdev /*分配并初始化一个以太网设备*/





/*******************************************************************************
net_device对象是网络设备的一个软件抽象，只有当这个对象注册到系统中后，内核网络子
系统发送或者发送一个网络数据包时才会调用到net_device对象提供的函数。所以当分配一
个新的net_device对象并初始化后，要把它注册到系统中。register_netdev 函数完成这个
功能。

当一个NIC设备向系统成功注册后，它将被纳入到系统的网络设备列表管理体系中。当内核
的网络子系统高层要发送一个数据包时，通过查找路由表得到接口信息(比如找到了eth0)
然后再到设备列表中查找对应的设备。
*******************************************************************************/
int register_netdev(struct net_device *dev);


void unregister_netdev(struct net_device *dev);



/*******************************************************************************
网络设备驱动程序提供的所有功能的集合称之为设备方法
设备方法定义在 net_device_ops 结构中

int (*ndo_init)(struct net_device *dev);
    This function is called once when network device is registered.The network 
    device can use this to any late stage initializaton or semantic validattion. 
    It can fail with an error code which will be propogated back to register_netdev

void (*ndo_uninit)(struct net_device *dev);
    This function is called when device is unregistered or when registration fails. 
    It is not called if init fails.

int (*ndo_open)(struct net_device *dev);
    This function is called when network device transistions to the up state.
    当设备所在的网络接口被激活时，比如实用ipconfig激活某一网络接口时，接口将被打开。
    此时ndo_open将被调用，大概完成如下工作:分配接收发送网络数据包所需要的资源，初始
    化设备的硬件中断并向系统注册中断，启动watchdog定时器，通知上层网络子系统当前接口
    已就绪等。
    
int (*ndo_stop)(struct net_device *dev);
    This function is called when network device transistions to the down state.

netdev_tx_t (*ndo_start_xmit) (struct sk_buff *skb,struct net_device *dev);
    通过DMA将@skb中的数据拷贝到网络设备的存储空间中，然后由网络设备的硬件逻辑负
    责把设备存储空间中的数据发送出去，成功后设备产生一个硬件中断通知驱动程序进行
    相应的处理，比如释放@skb缓冲区，进行一些统计等。
    dev_queue_xmit

*******************************************************************************/

struct net_device_ops
{
    int   (*ndo_init)(struct net_device *dev);
    void  (*ndo_uninit)(struct net_device *dev);
    netdev_tx_t (*ndo_start_xmit) (struct sk_buff *skb,struct net_device *dev);
};

/*******************************************************************************
现实中的网络设备驱动程序需要根据实际情况决定如何调用 netif_stop_queue 和 
netif_start_queue函数。一个典型的情况是:打开一个网络设备的接口时，调用后者以告诉
内核，网络子系统高层代码可以调用dev_hard_start_xmit进行数据包的发送;当网络设备接
口被关闭时，对应的驱动程序应该调用前者以通知上层代码。

*******************************************************************************/



/**
 *	netif_stop_queue - stop transmitted packets
 *	@dev: network device
 *
 *	Stop upper layers calling the device hard_start_xmit routine.
 *	Used for flow control when transmit resources are unavailable.
 */
static inline void netif_stop_queue(struct net_device *dev);


/**
 *	netif_start_queue - allow transmit
 *	@dev: network device
 *
 *	Allow upper layers to call the device hard_start_xmit routine.
 */
static inline void netif_start_queue(struct net_device *dev);



/* 这个函数会判断网卡是否忙 */
int dev_hard_start_xmit(struct sk_buff *skb, struct net_device *dev,struct netdev_queue *txq);



/*
=================== 收包流程
1 网络设备收到包后利用DMA把数据拷贝到CPU的内存中，然后给CPU发送中断。
2 CPU调用预先注册的中断处理函数来处理处理数据包。
3 中断处理函数中分配一个套接字缓冲区skb，并确保数据包从设备内从中传输到了skb所指的系统内存。
4 然后调用netif_rx(skb)。netif_rx只是将收到的数据包放在一个接收队列上，然后触发NET_RX_SOFTIRQ软中断。

另外:
1 软中断处理函数在 net_dev_init() 中注册。
  open_softirq(NET_TX_SOFTIRQ, net_tx_action, NULL);
  open_softirq(NET_RX_SOFTIRQ, net_rx_action, NULL);
2 申请套接字缓冲区skb的接口 dev_alloc_skb()


********************************************************************************
NAPI(new api)
napi结合了中断与轮询的各自优势。当有数据包到达时会触发硬件中断，在中断处理中关闭
中断，然后进入轮询模式，直到所有的数据包接收完毕，再重新开启中断，进入下一个中断
轮询周期。

*/
