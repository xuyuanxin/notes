
struct net_device  /*描述网络设备的结构,存储网络设备的所有信息*/



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






*/
