/*******************************************************************************
 Routers   Routes   Routing Tables
    router can be defined as a network device that is equipped with more than 
    one network interface card (NIC), and that uses its knowledge of the network 
    to forward ingress traffic appropriately.
 
    The information required to decide whether an ingress packet is addressed to 
    the local host or should be forwarded, together with the information needed 
    to correctly forward the packets in the latter case, is stored in a database 
    called the Forwarding Information Base (FIB). It is often referred to simply 
    as the routing table.

    The routing table is nothing but a collection of routes. A route is a collection 
    of parameters used to store the information necessary to forward traffic toward 
    a given destination.
    
                                            
  +------+ Routing table                     +------+ Default GW
  |  pc  | 10.0.0.0/24  Local (eth0)         |  RT  |
  |      | 0.0.0.0/0    Next hop 10.0.0.1    |      |----------[ internet ]
  | eth0 |                                   | eth0 |
  +------+                                   +------+
     |                                          |
     | eth0: 10.0.0.2                           | eth0: 10.0.0.1
 ------------------------------------------------------------Subnet 10.0.0.0/24

     Figure 30-2. Basic example of router and routing table

 Most hosts, not being routers, have only one interface. The host is configured 
 to use a default gateway to reach any nonlocal addresses. Thus, in Figure, 
 traffic for any host outside the 10.0.0.0/24 network (designated by 0.0.0.0/0) 
 is sent to the gateway on 10.0.0.1. For hosts on the 10.0.0.0/24 network, the 
 neighboring subsystem is used.

 the minimum set of parameters needed to define a route
 1 Destination network
  The routing table is used to forward traffic toward its destination. It should 
  not come as a surprise that this is the most important field used by the routing
  lookup routines. Figure 30-2 shows a routing table with two routes: one that
  leads to the local subnet 10.0.0.0/24 and another one that leads everywhere 
  else.The latter is called the default route and is recorded as a network of 
  all zeros in the table .
 2 Egress device
  This is the device out of which packets matching this route should be transmitted. 
  For example, packets sent to the address 10.0.0.100 would be sent out eth0.
 3 Next hop gateway 
  When the destination network is not directly connected to the local host, you 
  need to rely on other routers to reach it. For example, the host in Figure 30-2 
  needs to rely on the router RT to reach any host located outside the 10.0.0.0/24 
  subnet. The next-hop gateway is the address of that router.

 *******************************************************************************
 common scopes for IP addresses
 Host
 An address has host scope when it is used only to communicate within the host 
 itself. Outside the host this address is not known and cannot be used. An example 
 is the loopback address, 127.0.0.1.
 Link
 An address has link scope when it is meaningful and can be used only within a
 LAN (that is, a network on which every computer is connected to every other one 
 on the link layer). An example is a subnet¡¯s broadcast address. Packets sent to 
 the subnet broadcast address are sent by a host on that subnet to the other hosts 
 on the same subnet.
 Universe
 An address has universe scope when it can be used anywhere. This is the default 
 scope for most addresses.
 
 the meaning of the same three scopes when applied to routes:
 Host
 A route has host scope when it leads to a destination address on the local host.
 Link
 A route has link scope when it leads to a destination address on the local network.
 Universe
 A route has universe scope when it leads to addresses more than one hop away
 *******************************************************************************
 Primary and Secondary Addresses 
 if configure multiple IPaddresses on the same interface, you need to specify a 
 netmask for each one. An address is considered secondary if it falls within the 
 subnet of another already configured address on the same NIC.
 The following is the configuration of a single NIC named eth0 after it is configured
 with two addresses having the same netmask, first 10.0.0.1/24 and then 10.0.0.2/24.
 Since the two addresses fall within the same 10.0.0.0/24 subnet, the first one 
 configured will be primary and the other one will be secondary.
 [root@router kernel]# ip address add 10.0.0.1/24 broadcast 10.0.0.255 dev eth0
 [root@router kernel]# ip address list dev eth0
 4: eth0: <BROADCAST,MULTICAST,UP> mtu 1500 qdisc pfifo_fast qlen 100
 link/ether 00:60:97:77:d1:8c brd ff:ff:ff:ff:ff:ff
 inet 10.0.0.1/24 brd 10.0.0.255 scope global eth0
 [root@router kernel]# ip address add 10.0.0.2/24 broadcast 10.0.0.255 dev eth0
 [root@router kernel]# ip address list dev eth0
 4: eth0: <BROADCAST,MULTICAST,UP> mtu 1500 qdisc pfifo_fast qlen 100
 link/ether 00:60:97:77:d1:8c brd ff:ff:ff:ff:ff:ff
 inet 10.0.0.1/24 brd 10.0.0.255 scope global eth0
 inet 10.0.0.2/24 brd 10.0.0.255 scope global secondary eth0

 if we added the 10.0.0.3/25 address to the previous two, it would be classified 
 as another primary address on eth0. This would be the output of ip address list:
 [root@router kernel]# ip address add 10.0.0.3/25 broadcast 10.0.0.127 dev eth0
 [root@router kernel]# ip address list dev eth0
 4: eth0: <BROADCAST,MULTICAST,UP> mtu 1500 qdisc pfifo_fast qlen 100
 link/ether 00:60:97:77:d1:8c brd ff:ff:ff:ff:ff:ff
 inet 10.0.0.1/24 brd 10.0.0.255 scope global eth0
 inet 10.0.0.2/24 brd 10.0.0.255 scope global secondary eth0
 inet 10.0.0.3/25 brd 10.0.0.127 scope global eth0

 When you configure an aliasing device, the primary/secondary status is still 
 assigned based on the same rule we introduced in the section ¡°Primary and 
 Secondary Addresses.¡± However, the output of ip address list now adds a reference 
 to the aliasing device. The following snapshot shows an example where we start 
 with an interface with one configured address (eth1 ), add an address within 
 the same subnet on an aliasing device (eth1:1 ), and then add another address 
 in a different subnet on another aliasing device (eth1:2). Because of the 
 differing subnets, eth1:1 becomes secondary and eth1:2 becomes primary.

 [root@router kernel]# ip address list
 ...
 11: eth1: <BROADCAST,MULTICAST,UP> mtu 1500 qdisc pfifo_fast qlen 1000
 link/ether 00:0a:41:04:bd:16 brd ff:ff:ff:ff:ff:ff
 inet 192.168.1.101/24 brd 192.168.1.255 scope global eth1
 ...
 [root@router kernel]# ifconfig eth1:1 192.168.1.102 netmask 255.255.255.0
 [root@router kernel]# ifconfig eth1:2 192.168.1.103 netmask 255.255.255.128
 [root@router kernel]# ip address list
 ...
 11: eth1: <BROADCAST,MULTICAST,UP> mtu 1500 qdisc pfifo_fast qlen 1000
 link/ether 00:0a:41:04:bd:16 brd ff:ff:ff:ff:ff:ff
 inet 192.168.1.101/24 brd 192.168.1.255 scope global eth1
 inet 192.168.1.103/25 brd 192.168.1.255 scope global eth1:2
 inet 192.168.1.102/24 brd 192.168.1.255 scope global secondary eth1:1
 ...

 An obvious question is whether you can configure multiple addresses on an aliasing
 device using IPROUTE2. This is not possible, because IPROUTE2 does not treat
 aliasing devices as real, independent devices as ifconfig does: an aliasing device 
 to IPROUTE2 is just a label on an address.
 [root@router kernel]# ip address add 192.168.1.104/24 dev eth1:1
 Cannot find device "eth1:1"
*/


/* hash table buckets */
struct dn_rt_hash_bucket
{
	struct dn_route __rcu *chain;
	spinlock_t lock;
};


/* Elements of the cache */
struct rtable {
	struct dst_entry	dst;

	int			rt_genid;
	unsigned int		rt_flags;
	__u16			rt_type;
	__u8			rt_is_input;
	__u8			rt_uses_gateway;

	int			rt_iif;

	/* Info on neighbour */
	__be32			rt_gateway;

	/* Miscellaneous cached information */
	u32			rt_pmtu;

	struct list_head	rt_uncached;
};















/*******************************************************************************
 Used by the routing table based classifier to keep statistics, expressed in both 
 bytes and number of packets, about the traffic for routes that have been associated 
 with a tag. The structure contains an array of counters, with 256 elements for 
 each processor.The size is 256 because route tags lie in the range from 0 to 255. 
 The vector is allocated by ip_rt_init for IPv4; nothing is allocated for IPv6. 
 The four fields of ip_rt_acct are updated in ip_rcv_finish.
 ******************************************************************************/
 struct ip_rt_acct {
	 __u32	 o_bytes;
	 __u32	 o_packets;
	 __u32	 i_bytes;
	 __u32	 i_packets;
 };


 /* rtm_scope
 
	Really it is not scope, but sort of distance to the destination.
	NOWHERE are reserved for not existing destinations, HOST is our
	local addresses, LINK are destinations, located on directly attached
	link and UNIVERSE is everywhere in the Universe.
 
	Intermediate values are also possible f.e. interior routes
	could be assigned a value between UNIVERSE and LINK.

 RT_SCOPE_NOWHERE
	 This value,is treated by the code as illegal.The literal meaning is that 
	 the route does not lead anywhere, which basically means there is no route 
	 to the destination.
 RT_SCOPE_HOST
	 Examples of these routes are the ones created automatically when configuring 
	 IP addresses on the local interfaces.
 RT_SCOPE_LINK
     This includes routes to the local network (as defined by the netmask) and 
     to the subnet broadcast addresses derived from locally configured addresses.
 RT_SCOPE_UNIVERSE
     This is used for all routes that lead to remote destinations not directly 
     connected (i.e., the ones that require a next-hop gateway).	
 */
 
 enum rt_scope_t 
 {
	 RT_SCOPE_UNIVERSE=0,
 /* User defined values  */
	 RT_SCOPE_SITE=200,
	 RT_SCOPE_LINK=253,
	 RT_SCOPE_HOST=254,
	 RT_SCOPE_NOWHERE=255
 };

/*
 The scope of an address is saved in the ifa_scope field of the in_ifaddr structure.
 The next-hop gateway in a route is another object type that is assigned a scope. 
 Each route can be assigned zero, one, or multiple next hops. Each next hop is 
 defined with an instance of a fib_nh structure.

 Two of the fib_nh's fields are nh_gw and nh_scope: nh_gw is the IPaddress of 
 the next-hop gateway, and fib_scope is the scope of that address (which consists 
 of the scope of the route needed to reach the next-hop gateway from the local host).
*/
 struct in_ifaddr


/*
 Primary and Secondary IP Addresses     in_ifaddr.ifa_flags
 Secondary IPv4 addresses are tagged with the IFA_F_SECONDARY flag in their 
 in_ifaddr data structures . Because there are only two configurations¡ªprimary 
 and secondary¡ªthere is no need for an IFA_F_PRIMARY flag: if an address is not
 secondary, it is considered primary. 


*/

/*
 for_ifa
 endfor_ifa
 Given a device, these two macros can be used to browse all of its in_device 
 data structures.
 
 for_primary_ifa
 endfor_ifa
 Given a device, these two macros can be used to selectively browse only the 
 in_device instances associated with primary IP addresses.*/
for_ifa {
    do something with ifa
} endfor_ifa


FIB_RES_DEV



struct net_device->ip_ptr;


