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
    IP header can be up to 60 bytes long (20+40) 

Total Length (16bits)
    gives the length of the IP datagram measured in octets, including octets in 
    the header and payload. the maximum possible size of an IP datagram is 2^16 
    or 65,535 octets(64KB).

Identification (16bits)
    发送端发送的IP数据包标识字段都是一个唯一值，该值在分片时被复制到每个片中。

Flags (3bits |R|DF|MF| )    
    R：保留未用。
    DF：Don't Fragment，“不分片”位，如果将这一比特置1 ，IP层将不对数据报进行分片。
    MF：More Fragment，“更多的片”，除了最后一片外，其他每个组成数据报的片都要
    把该比特置1。

Fragment Offset (13 bits)
    该片偏移原始数据包开始处的位置。偏移的字节数是该值乘以8。当数据报被分片后，
    每个片的总长度值要改为该片的长度值。

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
  



Path MTU discovery is used to discover the biggest size a packet transmitted to 
a given destination address can have without being fragmented. That parameter 
is called the Path MTU (PMTU). Basically, the PMTU is the smallest MTU encountered 
along all the connections along the route from one host to the other.Furthermore, 
a change of route can lead to a change of PMTU.




校验和的计算
I.将校验和字段置为0,然后将IP包头按16比特分成多个
校验和Header Checksum：0x618D将其重置为0X0000

将IP包头分段：
    1.　　0x4500
    2.　　0x0029
    3.　　0x44F1
    4.　　0x4000
    5.　　0x8006
    6.　　0x0000 ------->这个为Header Checksum的值，我们前面将其重置为0了
    7.　　0xC0A8
    8.　　0x01AE
    9.　　0x4A7D
+　10.    0x477D
-------------------------------------------------------
将1至10相加求出来的和为：0x29E70 (注意进位保留，这里是2)

II.对各个单元采用反码加法运算(即高位溢出位会加到低位,通常的补码运算是直接丢掉溢
出的高位),将得到的和的反码填入校验和字段
0x0002+0x9E70=0x9E72
0x9E72二进制为：1001 1110 0111 0010
反码为：0110 0001 1000 1101
0110 0001 1000 1101的16进制为：0x618D



*/
