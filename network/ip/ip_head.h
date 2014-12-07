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

