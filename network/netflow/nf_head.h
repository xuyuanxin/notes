/*******************************************************************************
    dst port 9996    rfc 3954
********************************************************************************
    IP + UDP + NetFlow
********************************************************************************
                              Terminology
********************************************************************************
Export packet
    Built by a device (for example, a router) with NetFlow services enabled,this 
    type of packet is addressed to another device (for example, a NetFlow collector). 
    This other device processes the packet (parses, aggregates, and stores information 
    on IP flows).
    
Packet header
    The first part of an export packet, the packet header provides basic information 
    about the packet, such as the NetFlow version, number of records contained 
    within the packet, and sequence numbering, enabling lost packets to be detected.

FlowSet
    Following the packet header, an export packet contains information that must 
    be parsed and interpreted by the collector device. A FlowSet is a generic term 
    for a collection  of records that follow the packet header in an export packet. 
    There are two different types of FlowSets: template and data. An export packet 
    contains one or more FlowSets, and both template and data FlowSets can be mixed 
    within the same export packet.   

Template FlowSet
    a template FlowSet is a collection of one or more template records  that have 
    been grouped together in an export packet.
    
Template record
    a template record is used to define the format of subsequent data records 
    that may be received in current or future export packets. It is important 
    to note tha a template record within an export packet does not necessarily 
    indicate the format of data records within that same packet. A collector 
    application must cache any template records received, and then parse any 
    data records it encounters by locating the appropriate template record within 
    the cache. 

Template ID
    the template ID is a unique number that distinguishes this template record 
    from all other template records produced by the same export device. A collector 
    application that is receiving export packets from several devices should be 
    aware that uniqueness is not guaranteed across export devices. Thus, the 
    collector should also cache the address of the export device that produced 
    the template ID in order to enforce uniqueness. 

Data FlowSet 
    a data FlowSet is a collection of one or more data records that have been
    grouped together in an export packet. 

Data record 
    a data record provides information about an IP flow that exists on the device 
    that produced an export packet. Each group of data records (that is, each data 
    FlowSet) references a previously transmitted template ID, which can be used to 
    parse the data contained within the records.

Options template
    an options template is a special type of template record used to communicate 
    the format of data related to the NetFlow process.
    
Options data record
    the options data record is a special type of data record (based on an options 
    template) with a reserved template ID that provides information about the 
    NetFlow process itself.  
********************************************************************************
                            Packet Layout
********************************************************************************
An Export Packet consists of a Packet Header followed by one or more FlowSets.The 
FlowSets can be any of the possible three types: Template,Data,or Options Template.
	+--------+-------------------------------------------+
	|		| +----------+ +---------+ +----------+	   |
	| Packet | | Template | | Data	  | | Options  |	   |
	| Header | | FlowSet  | | FlowSet | | Template | ... |
	|		| |		    | |		  | | FlowSet  |	   |
	|		| +----------+ +---------+ +----------+	   |
	+--------+-------------------------------------------+
A FlowSet ID is used to distinguish the different types of FlowSets.FlowSet IDs 
lower than 256 are reserved for special FlowSets, such as the Template FlowSet(ID 0) 
and the Options Template FlowSet (ID 1).The Data FlowSets have a FlowSet ID greater 
than 255.

Following are some examples of export packets:   
1 An Export Packet consisting of interleaved Template, Data, and Options Template 
  FlowSets.
2 An Export Packet consisting entirely of Data FlowSets. 
3 An Export Packet consisting entirely of Template and Options Template FlowSets.
********************************************************************************
                  NetFlow Version 9 Packet Header Format
********************************************************************************
Version
    The version of NetFlow records exported in this packet; for Version 9, this 
    value is 0x0009
    
count
    Number of FlowSet records (both template and data) contained within this packet

System Uptime
    Time in milliseconds since this device was first booted 

UNIX Secs	
    Time in seconds since 0000 UTC 1970,at which the Export Packet leaves the Exporter.

Sequence Number
    Incremental sequence counter of all export packets sent by this export device; 
    this value is  cumulative, and it can be used to identify whether any export 
    packets have been missed.

Source ID: 
    32-bit value that is used to guarantee uniqueness for all flows exported from 
    a particular device.The format of this field is vendor specific.In the Cisco 
    implementation, the first two bytes are reserved for future expansion,and will 
    always be zero. Byte 3 provides uniqueness with respect to the routing engine 
    on the exporting device. Byte 4 provides uniqueness with respect to the 
    particular line card or Versatile Interface Processor on the exporting device. 
    Collector devices should use the combination of the source IP address plus the 
    Source ID field to associate an incoming NetFlow export packet with a unique 
    instance of NetFlow on a particular device. 
*******************************************************************************/

struct nfv9_hdr
{
    u16 ver;
    u16 count;
    u32 sys_uptime;
    u32 unix_seconds; 
    u32 pkt_seq;  
    u32 sid;    
};

