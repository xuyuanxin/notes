#include<linux/kernel.h>
#include<linux/module.h>
#include<linux/ip.h>
#include<linux/version.h>
#include<linux/skbuff.h>
#include<linux/netfilter.h>
#include<linux/netfilter_ipv4.h>
#include<linux/moduleparam.h>
#include <linux/netfilter_ipv4/ip_tables.h>
 
MODULE_LICENSE("GPL");
MODULE_AUTHOR("xuyuanxin");
MODULE_DESCRIPTION("A simple test");
 
int dnspkt_cnt = 0;

static unsigned int dns_stat_func(unsigned int hooknum, struct sk_buff **skb, const struct net_device *in,const struct net_device *out, int (*okfn)(struct sk_buff *))
{
   const struct iphdr *iph = (struct iphdr *)(*skb)->network_header;
   const struct udphdr *udph = NULL;
   
   if(17 == iph->protocol)/*UDP 17*/
   {
       udph = (struct udphdr *)(*skb)->transport_header;
	   {
          dnspkt_cnt++;
	   }
   }
   return NF_ACCEPT;
}
 
static struct nf_hook_ops nfhook={
        .hook           = dns_stat_func,    
        .owner          = THIS_MODULE,
        .pf             = PF_INET,
        .hooknum        = 0, /*NF_IP_PRE_ROUTING*/ 
        .priority       = NF_IP_PRI_FIRST, 
};
 
static int __init dns_stat_init(void)
{
    return nf_register_hook(&nfhook);
}
 
static void __exit dns_stat_exit(void)
{
    nf_unregister_hook(&nfhook);
}

int get_dnspkt()
{
    
    return dnspkt_cnt;
}
EXPORT_SYMBOL(get_dnspkt);

module_init(dns_stat_init);
module_exit(dns_stat_exit);
