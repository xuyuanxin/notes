/*
rfc 791


    0                   1                   2                   3   
    0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
   |Version|  IHL  |Type of Service|          Total Length         |
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
   |         Identification        |Flags|      Fragment Offset    |
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
   |  Time to Live |    Protocol   |         Header Checksum       |
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
   |                       Source Address                          |
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
   |                    Destination Address                        |
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
   |                    Options                    |    Padding    |
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+


Version
    the version of the IP protocol,for IPv4,the version field contains the value 4.

IHL
    gives the datagram header length measured in 32-bit words.The most common 
    datagram header, which contains no options and no padding, measures 20 octets 
    and has a header length field equal to 5.

Total Length
    gives the length of the IP datagram measured in octets, including octets in 
    the header and payload. 

Protocol
    the value specifies which high-level protocol was used to create the message 
    carried in the PAYLOAD area of the datagram. In essence, the value of PROTOCOL 
    specifies the format of the PAYLOAD area. The mapping between a high-level 
    protocol and the integer value used in the PROTOCOL field must be administered 
    by a central authority to guarantee agreement across the entire Internet.

Header Checksum (IP header)
    The IP checksum is formed by treating the header as a sequence of 16-bit 
    integers (in network byte order), adding them together using one's complement 
    arithmetic, and then taking the one's complement of the result. For purposes 
    of computing the checksum, field HEADER CHECKSUM is assumed to contain zero.
    It is important to note that the checksum only applies to values in the IP 
    header and not to the payload.

Source Address  Destination Address
    The source address field in a datagram always refers to the original source 
    and the destination address field refers to the ultimate destination.

Options
    The IP OPTIONS field, discussed below, is variable length. 

Padding
    The field labeled PADDING, depends on the options selected. It represents bits
    containing zero that may be needed to ensure the datagram header extends to 
    an exact multiple of 32 bits (recall that the header length field is specified 
    in units of 32-bit words).
*/

struct iphdr {
#if defined(__LITTLE_ENDIAN_BITFIELD)
	__u8	ihl:4,
		version:4;
#elif defined (__BIG_ENDIAN_BITFIELD)
	__u8	version:4,
  		ihl:4;
#else
#error	"Please fix <asm/byteorder.h>"
#endif
	__u8	tos;
	__be16	tot_len;
	__be16	id;
	__be16	frag_off;
	__u8	ttl;
	__u8	protocol;
	__sum16	check;
	__be32	saddr;
	__be32	daddr;
	/*The options start here. */
};


/* IP options */
#define IPOPT_COPY		    0x80 /* 1000 0000 */
#define IPOPT_CLASS_MASK	0x60 /* 0110 0000 */
#define IPOPT_NUMBER_MASK	0x1f /* 0001 1111 */

#define	IPOPT_COPIED(o)		((o)&IPOPT_COPY)
#define	IPOPT_CLASS(o)		((o)&IPOPT_CLASS_MASK)
#define	IPOPT_NUMBER(o)		((o)&IPOPT_NUMBER_MASK)

#define	IPOPT_CONTROL		0x00
#define	IPOPT_RESERVED1		0x20
#define	IPOPT_MEASUREMENT	0x40
#define	IPOPT_RESERVED2		0x60

#define IPOPT_END	(0 |IPOPT_CONTROL)
#define IPOPT_NOOP	(1 |IPOPT_CONTROL)
#define IPOPT_SEC	(2 |IPOPT_CONTROL|IPOPT_COPY)
#define IPOPT_LSRR	(3 |IPOPT_CONTROL|IPOPT_COPY)
#define IPOPT_TIMESTAMP	(4 |IPOPT_MEASUREMENT)
#define IPOPT_CIPSO	(6 |IPOPT_CONTROL|IPOPT_COPY)
#define IPOPT_RR	(7 |IPOPT_CONTROL)
#define IPOPT_SID	(8 |IPOPT_CONTROL|IPOPT_COPY)
#define IPOPT_SSRR	(9 |IPOPT_CONTROL|IPOPT_COPY)
#define IPOPT_RA	(20|IPOPT_CONTROL|IPOPT_COPY)

/*
IP头中可以包含若干选项，主要用于网络测试和调试。

每个选项有一个8bit的选项码(option code)，结构如下

 +-------------------------------------------------------+
 | copy(1bit) | option class(2bit) | option number(5bit) |
 +-------------------------------------------------------+

 copy
     1表示复制到所有的分片中，0表示仅复制到第一个分片
 option class 
	 0 = control	  
	 1 = reserved for future use	   
	 2 = debugging and measurement	  
	 3 = reserved for future use

 option number
     可以认为是option clas下的子类。

End of Option List ( type 0 )	  
  +--------+		
  |00000000|		  
  +--------+
  
  This option indicates the end of the option list. 

No Operation	( type 1 )	
  +--------+		  
  |00000001|		
  +--------+

  This option may be used between options, for example, to align the beginning 
  of a subsequent option on a 32 bit boundary.

Loose Source and Record Route	( Type=131 )	 
    +--------+--------+--------+---------//--------+		 
    |10000011| length | pointer|	  route data	|		 
    +--------+--------+--------+---------//--------+		  


Strict Source and Record Route ( Type=137 )  
    +--------+--------+--------+---------//--------+		  
    |10001001| length | pointer|	   route data	 |		  
    +--------+--------+--------+---------//--------+		   


Record Route ( type 7 )
  +--------+--------+--------+---------//--------+
  |00000111| length | pointer|	   route data    |
  +--------+--------+--------+---------//--------+


Stream Identifier (  Type=136 Length=4 )       
  +--------+--------+--------+--------+        
  |10001000|00000010|    Stream ID    |        
  +--------+--------+--------+--------+                

  This option provides a way for the 16-bit SATNET stream identifier to be 
  carried through networks that do not support the stream concept.Must be copied 
  on fragmentation.  Appears at most once in a  datagram.    


Internet Timestamp ( Type = 68 )

  +--------+--------+--------+--------+
  |01000100| length | pointer|oflw|flg|
  +--------+--------+--------+--------+
  | 		internet address		      |
  +--------+--------+--------+--------+
  | 			timestamp			      |
  +--------+--------+--------+--------+
  | 				.				  |
					.
					.
  


*/
