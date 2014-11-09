/*np:notes not project 避免和project重名，阅读不方便。
  示例等非project中的命名加前缀"np"*/


/*tcp 基本头部，不包括可选部分*/
struct np_tcphdr 
{
	__be16	source; /*源端口*/
	__be16	dest;   /*目的端口*/
	__be32	seq;    /*发送序列号*/
	__be32	ack_seq;/*期望接收的序列号*/
#if defined(__LITTLE_ENDIAN_BITFIELD)
	__u16	res1:4,/**/
		doff:4,/**/
		fin:1,/**/
		syn:1,/*建立连接*/
		rst:1,/**/
		psh:1,/**/
		ack:1,/*应答标志*/
		urg:1,/**/
		ece:1,/**/
		cwr:1;/**/
#elif defined(__BIG_ENDIAN_BITFIELD)
	__u16	doff:4,/**/
		res1:4,/**/
		cwr:1,/**/
		ece:1,/**/
		urg:1,/**/
		ack:1,/**/
		psh:1,/**/
		rst:1,/**/
		syn:1,/**/
		fin:1;/**/
#else
#error	"Adjust your <asm/byteorder.h> defines"
#endif	
	__be16	window;/**/
	__sum16	check;/**/
	__be16	urg_ptr;/**/
};


/*
Transmission Control Protocol

+------------------------------------------+
|            tcp segment format            |
|------------------------------------------|
|0    4     10      16          24       31|
+------------------------------------------+
|      SOURCE PORT   |   DESTINATON PORT   |
+------------------------------------------+
|               SEQUENCE NUMBER            |
+------------------------------------------+
|         ACKNOWLEDGEMENT NUMBER           |
+------------------------------------------+
|HLEN|RESERVED|CODE BITS|     WINDOW       |
+------------------------------------------+
|      CHECKSUM         | URGENT POINTER   |
+------------------------------------------+
|     OPTIONS(IF ANY)          |  PADDING  |
+------------------------------------------+
|                PAYLOAD                   |
+------------------------------------------+
SOURCE PORT            : TCP port numbers that identify the application
DESTINATION PORT       : programs at the ends of the connection
SEQUENCE NUMBER        : identifies the position in the sender’s octet stream of the data in the segment
ACKNOWLEDGEMENT NUMBER : identifies the number of the octet that the source expects to receive next
HLEN(4-bit)            : specifies the length of the segment header measured in 32-bit multiples. 
RESERVED(6-bit)        : reserved for future use
CODE BITS(6-bit)       : determine the purpose and contents of the segment
                         Bit (left to right) | Meaning if bit set to 1
                                URG          | Urgent pointer field is valid
                                ACK          | Acknowledgement field is valid
                                PSH          | This segment requests a push
                                RST          | Reset the connection
                                SYN          | Synchronize sequence numbers
                                FIN          | Sender has reached end of its byte stream
WINDOW(16-bit)         : TCP software advertises how much data it is willing to accept every time it sends a segment by specifying its buffer size in the  field
URGENT POINTER         : When the URG bit is set, the  field specifies the position in the segment where urgent data ends
OPTIONS                : TCP header can contain zero or more options ;Each option begins with a 1-octet field that specifies
                         the option type followed by a 1-octet length field that specifies the size of the option in octets. 
PADDING                : the header length is specified in 32-bit multiples. If the options do not occupy an exact multiple of 32 bits, 
                         PADDING is added to the end of the header.
						 
						 
+------------------------------------------+						 
|     ipv4 tcp pseudo-header format        |
|------------------------------------------|
|0        8          16                  31|
+------------------------------------------+
|              SOURCE IP ADDRESS           |
+------------------------------------------+
|           DESTINATON IP ADDRESS          |    
+------------------------------------------+
|  ZERO  | PROTOCOL  |        TCP LENGTH   |
+------------------------------------------+


+------------------------------------------+
|     ipv6 tcp pseudo-header format        |
|------------------------------------------|
|0                             24        31| 
+------------------------------------------+
|                                          |
|              SOURCE  ADDRESS             |
|                                          |
|                                          |
+------------------------------------------+
|                                          |
|                                          |
|           DESTINATON  ADDRESS            |
|                                          |
+------------------------------------------+
|                 TCP LENGTH               |
+------------------------------------------+
| UNUSED(MUST BE ZERO)       | NEXT HEADER |
+------------------------------------------+
PROTOCOL field (IPv4) or the NEXT HEADER field (IPv6) is assigned the value 6, the value for datagrams carrying TCP. 
The TCP LENGTH field specifies the total length of the TCP segment including the TCP header.






*/



