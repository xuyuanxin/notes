/*******************************************************************************
             The format of the Data FlowSet is as follows:
    0                   1                   2                   3
    0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
   |   FlowSet ID = Template ID    |          Length               |
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
   |   Record 1 - Field Value 1    |   Record 1 - Field Value 2    |
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
   |   Record 1 - Field Value 3    |             ...               |
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
   |   Record 2 - Field Value 1    |   Record 2 - Field Value 2    |
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
   |   Record 2 - Field Value 3    |             ...               |
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
   |   Record 3 - Field Value 1    |             ...               |
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
   |              ...              |            Padding            |
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

FlowSet ID = Template ID
    Each Data FlowSet is associated with a FlowSet ID. The FlowSet ID maps to a 
    (previously generated) Template ID. The Collector MUST use the FlowSet ID to 
    find the corresponding Template Record and decode the Flow Records from the FlowSet.

Length
    The length of this FlowSet. Length is the sum of the lengths of the FlowSet ID, 
    Length itself, all Flow Records within this FlowSet, and the padding bytes, if any.

Record N - Field Value M
    The remainder of the Data FlowSet is a collection of Flow Data Record(s), 
    each containing a set of field values. The Type and Length of the fields have 
    been previously defined in the Template Record referenced by the FlowSet ID or 
    Template ID.

Padding
    The Exporter SHOULD insert some padding bytes so that the subsequent FlowSet 
    starts at a 4-byte aligned boundary.It is important to note that the Length 
    field includes the padding bytes. Padding SHOULD be using zeros.

*******************************************************************************/


/*******************************************************************************
假设as聚合的数据结构如下所示(可以任意添加)，要想接收端理解这个结构，首先发送as模
板(t_as)，as模板要和这个结构对应
*******************************************************************************/
struct d_as
{
    u16   flowid;
	u16   total_len;

    u32   as_flows;      /* 1  聚合流的个数*/
    u32   as_pkts;       /* 2  流过IP包数 */
    u32   as_octets;     /* 3  流过字节数 */
    u32   as_first;      /* 4  流创建时间 */
    u32   as_last;       /* 5  最后一个报文时间 */
    u16   as_input;      /* 6  输入接口 */
    u16   as_output;     /* 7  输出接口 */  
    u16   as_srcas;      /* 8  源自治系统号 */
    u16   as_dstas;      /* 9  目的自治系统号 */
    u8    as_direction;  /* 10 出入接口方向*/
    u8    as_pad[3];     /* 11 四字节对齐*/
};

