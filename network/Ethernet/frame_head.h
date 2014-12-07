/*******************************************************************************

+--------------------------------------------------------------------------+
| Destination Address | Source Address | Frame Type | Frame Payload (Data) |
|--------------------------------------------------------------------------|
|      6 octets       |   6 octets     |  2 octets  |    46�C1500 octets   |
+--------------------------------------------------------------------------+

each Ethernet frame contains a field that holds the 48-bit address of a destination 
and another field that holds the 48-bit address of the sender. 

The operating system examines the type field of each arriving frame to decide which 
module should process the contents. We will see that the type field can be used 
to define multiple protocols in the same family. For example, because the TCP/IP 
protocols include several protocols that can be sent over an Ethernet, TCP/IP 
defines several Ethernet types.

The maximum size of the payload in an Ethernet frame is 1500 octets.


we use the term frame to refer to a packet that is defined by hardware technologies
Ethernet frames are variable length, with no frame smaller than 64 octets or 
larger than 1514 octets (header and data).

When transmitted, the frame also includes a 4-octet Cyclic Redundancy Check (CRC) 
that is used to check for transmission errors. Because the CRC field is added by
the sending hardware and checked by the receiving hardware, the CRC is not visible 
to higher layers of protocol software.  


*******************************************************************************/
