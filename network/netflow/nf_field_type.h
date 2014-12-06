

#define NFT_AS      256          /* NetFlow Template as template id */
#define NFT_OT_SYS  1301         /*Option template id system*/


/*******************************************************************************
                     Field Type Definitions
********************************************************************************
The following table describes all the field type definitions that an Exporter MAY 
support. The fields are a selection of Packet Header fields, lookup results (for 
example, the autonomous system numbers or the subnet masks), and properties of the 
packet such as length.
********************************************************************************/
#define IN_BYTES        1
#define IN_PKTS         2
#define FLOWS           3

                                           
#define INPUT_SNMP     10  /* Input interface index. */
#define OUTPUT_SNMP    14   /* Output interface index.*/
										
#define SRC_AS		   16   /* Source BGP autonomous system number */	
#define DST_AS		   17   /* Destination BGP autonomous system number*/
#define LAST_SWITCHED  21  /* sysUptime in msec at which the last packet of this Flow was switched */
#define FIRST_SWITCHED 22  /* sysUptime in msec at which the first packet of this Flow was switched */
                                          
                                            
#define TOTAL_PKTS_EXP  41   /* Counter with length N x 8 bits for the number of packets exported by the Observation Domain. By default N is 4 */                                         
#define TOTAL_FLOWS_EXP 42   /* Counter with length N x 8 bits for the number of 
Flows exported by the Observation Domain. By default N is 4	*/									
#define DIRECTION	   61  /* Flow direction:0 - ingress flow 1 - egress flow */

/********************************************************************************

   Field Type                Value Length  Description
                                   (bytes)

                                           Incoming counter with
                                           length N x 8 bits for the
   IN_BYTES                     1    N     number of bytes associated
                                           with an IP Flow. By default
                                           N is 4

                                           Incoming counter with
                                           length N x 8 bits for the
   IN_PKTS                      2    N     number of packets
                                           associated with an IP Flow.
                                           By default N is 4

   FLOWS                        3    N     Number of Flows
                                           that were aggregated;
                                           by default N is 4

   PROTOCOL                     4    1     IP protocol byte

                                           Type of service byte
   TOS                          5    1     setting when entering
                                           the incoming interface

                                           TCP flags; cumulative of
   TCP_FLAGS                    6    1     all the TCP flags seen in
                                           this Flow

                                           TCP/UDP source port number
   L4_SRC_PORT                  7    2     (for example, FTP, Telnet,
                                           or equivalent)

   IPV4_SRC_ADDR                8    4     IPv4 source address

                                           The number of contiguous
                                           bits in the source subnet
   SRC_MASK                     9    1     mask (i.e., the mask in
                                           slash notation)

                                           Input interface index.
   INPUT_SNMP                   10   N     By default N is 2, but
                                           higher values can be used

                                           TCP/UDP destination port
   L4_DST_PORT                  11   2     number (for example, FTP,
                                           Telnet, or equivalent)




Claise                       Informational                     [Page 19]

RFC 3954        Cisco Systems NetFlow Services Export V9    October 2004


   IPV4_DST_ADDR                12   4     IPv4 destination address

                                           The number of contiguous
                                           bits in the destination
   DST_MASK                     13   1     subnet mask (i.e., the mask
                                           in slash notation)

                                           Output interface index.

   OUTPUT_SNMP                  14   N     By default N is 2, but
                                           higher values can be used

   IPV4_NEXT_HOP                15   4     IPv4 address of the next-
                                           hop router

                                           Source BGP autonomous
   SRC_AS                       16   N     system number where N could
                                           be 2 or 4. By default N is
                                           2

                                           Destination BGP autonomous
   DST_AS                       17   N     system number where N could
                                           be 2 or 4. By default N is
                                           2

   BGP_IPV4_NEXT_HOP            18   4     Next-hop router's IP
                                           address in the BGP domain

                                           IP multicast outgoing
                                           packet counter with length
   MUL_DST_PKTS                 19   N     N x 8 bits for packets
                                           associated with the IP
                                           Flow. By default N is 4

                                           IP multicast outgoing
                                           Octet (byte) counter with
                                           length N x 8 bits for the
   MUL_DST_BYTES                20   N     number of bytes associated
                                           with the IP Flow. By
                                           default N is 4

                                           sysUptime in msec at which
   LAST_SWITCHED                21   4     the last packet of this
                                           Flow was switched

                                           sysUptime in msec at which
   FIRST_SWITCHED               22   4     the first packet of this
                                           Flow was switched



Claise                       Informational                     [Page 20]

RFC 3954        Cisco Systems NetFlow Services Export V9    October 2004


                                           Outgoing counter with
                                           length N x 8 bits for the
   OUT_BYTES                    23   N     number of bytes associated
                                           with an IP Flow. By
                                           default N is 4

                                           Outgoing counter with
                                           length N x 8 bits for the
   OUT_PKTS                     24   N     number of packets
                                           associated with an IP Flow.
                                           By default N is 4

   IPV6_SRC_ADDR                27   16    IPv6 source address

   IPV6_DST_ADDR                28   16    IPv6 destination address

   IPV6_SRC_MASK                29   1     Length of the IPv6 source
                                           mask in contiguous bits

                                           Length of the IPv6
   IPV6_DST_MASK                30   1     destination mask in
                                           contiguous bits

   IPV6_FLOW_LABEL              31   3     IPv6 flow label as per
                                           RFC 2460 definition

                                           Internet Control Message
   ICMP_TYPE                    32   2     Protocol (ICMP) packet
                                           type; reported as
                                           ICMP Type * 256 + ICMP code

   MUL_IGMP_TYPE                33   1     Internet Group Management
                                           Protocol (IGMP) packet type

                                           When using sampled NetFlow,
                                           the rate at which packets
   SAMPLING_INTERVAL            34   4     are sampled; for example, a
                                           value of 100 indicates that
                                           one of every hundred
                                           packets is sampled

                                           For sampled NetFlow
                                           platform-wide:
   SAMPLING_ALGORITHM           35   1     0x01 deterministic sampling
                                           0x02 random sampling
                                           Use in connection with
                                           SAMPLING_INTERVAL




Claise                       Informational                     [Page 21]

RFC 3954        Cisco Systems NetFlow Services Export V9    October 2004


                                           Timeout value (in seconds)

   FLOW_ACTIVE_TIMEOUT          36   2     for active flow entries
                                           in the NetFlow cache

                                           Timeout value (in seconds)
   FLOW_INACTIVE_TIMEOUT        37   2     for inactive Flow entries
                                           in the NetFlow cache

                                           Type of Flow switching
   ENGINE_TYPE                  38   1     engine (route processor,
                                           linecard, etc...)

   ENGINE_ID                    39   1     ID number of the Flow
                                           switching engine

                                           Counter with length
                                           N x 8 bits for the number
   TOTAL_BYTES_EXP              40   N     of bytes exported by the
                                           Observation Domain. By
                                           default N is 4

                                           Counter with length
                                           N x 8 bits for the number
   TOTAL_PKTS_EXP               41   N     of packets exported by the
                                           Observation Domain. By
                                           default N is 4

                                           Counter with length
                                           N x 8 bits for the number
   TOTAL_FLOWS_EXP              42   N     of Flows exported by the
                                           Observation Domain. By
                                           default N is 4

   MPLS_TOP_LABEL_TYPE          46   1     MPLS Top Label Type:
                                           0x00 UNKNOWN
                                           0x01 TE-MIDPT
                                           0x02 ATOM
                                           0x03 VPN
                                           0x04 BGP
                                           0x05 LDP

                                           Forwarding Equivalent Class
   MPLS_TOP_LABEL_IP_ADDR       47   4     corresponding to the MPLS
                                           Top Label

   FLOW_SAMPLER_ID              48   1     Identifier shown
                                           in "show flow-sampler"



Claise                       Informational                     [Page 22]

RFC 3954        Cisco Systems NetFlow Services Export V9    October 2004


                                           The type of algorithm used
                                           for sampling data:
   FLOW_SAMPLER_MODE            49   1     0x02 random sampling
                                           Use in connection with
                                           FLOW_SAMPLER_MODE
                                           Packet interval at which to
   FLOW_SAMPLER_RANDOM_INTERVAL 50   4     sample. Use in connection
                                           with FLOW_SAMPLER_MODE

                                           Type of Service byte
   DST_TOS                      55   1     setting when exiting
                                           outgoing interface

   SRC_MAC                      56   6     Source MAC Address

   DST_MAC                      57   6     Destination MAC Address

                                           Virtual LAN identifier

   SRC_VLAN                     58   2     associated with ingress
                                           interface

                                           Virtual LAN identifier
   DST_VLAN                     59   2     associated with egress
                                           interface

                                           Internet Protocol Version
                                           Set to 4 for IPv4, set to 6
   IP_PROTOCOL_VERSION          60   1     for IPv6. If not present in
                                           the template, then version
                                           4 is assumed

                                           Flow direction:
   DIRECTION                    61   1     0 - ingress flow
                                           1 - egress flow

   IPV6_NEXT_HOP                62   16    IPv6 address of the
                                           next-hop router

   BGP_IPV6_NEXT_HOP            63   16    Next-hop router in the BGP
                                           domain

                                           Bit-encoded field
   IPV6_OPTION_HEADERS          64   4     identifying IPv6 option
                                           headers found in the flow

   MPLS_LABEL_1                 70   3     MPLS label at position 1 in
                                           the stack



Claise                       Informational                     [Page 23]

RFC 3954        Cisco Systems NetFlow Services Export V9    October 2004


   MPLS_LABEL_2                 71   3     MPLS label at position 2 in
                                           the stack

   MPLS_LABEL_3                 72   3     MPLS label at position 3 in
                                           the stack

   MPLS_LABEL_4                 73   3     MPLS label at position 4 in
                                           the stack

   MPLS_LABEL_5                 74   3     MPLS label at position 5 in
                                           the stack

   MPLS_LABEL_6                 75   3     MPLS label at position 6 in
                                           the stack

   MPLS_LABEL_7                 76   3     MPLS label at position 7 in
                                           the stack

   MPLS_LABEL_8                 77   3     MPLS label at position 8 in
                                           the stack

   MPLS_LABEL_9                 78   3     MPLS label at position 9 in
                                           the stack

   MPLS_LABEL_10                79   3     MPLS label at position 10
                                           in the stack

   The value field is a numeric identifier for the field type. The
   following value fields are reserved for proprietary field types: 25,
   26, 43 to 45, 51 to 54, and 65 to 69.

   When extensibility is required, the new field types will be added to
   the list.  The new field types have to be updated on the Exporter and
   Collector but the NetFlow export format would remain unchanged.
   Refer to the latest documentation at http://www.cisco.com for the
   newly updated list.

   In some cases the size of a field type is fixed by definition, for
   example PROTOCOL, or IPV4_SRC_ADDR.  However in other cases they are
   defined as a variant type.  This improves the memory efficiency in
   the collector and reduces the network bandwidth requirement between
   the Exporter and the Collector.  As an example, in the case IN_BYTES,
   on an access router it might be sufficient to use a 32 bit counter (N
   = 4), whilst on a core router a 64 bit counter (N = 8) would be
   required.

   All counters and counter-like objects are unsigned integers of size N
   * 8 bits.

