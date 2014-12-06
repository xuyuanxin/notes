/*******************************************************************************
Options Data Record Format
    The Options Data Records are sent in Data FlowSets, on a regular basis, but 
    not with every Flow Data Record. How frequently these Options Data Records 
    are exported is configurable.  See the "Templates Management" section for 
    more details.

   The format of the Data FlowSet containing Options Data Records follows.
    0                   1                   2                   3
    0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
   |    FlowSet ID = Template ID   |          Length               |
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
   |   Record 1 - Scope 1 Value    |Record 1 - Option Field 1 Value|
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
   |Record 1 - Option Field 2 Value|             ...               |
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
   |   Record 2 - Scope 1 Value    |Record 2 - Option Field 1 Value|
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
   |Record 2 - Option Field 2 Value|             ...               |
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
   |   Record 3 - Scope 1 Value    |Record 3 - Option Field 1 Value|
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
   |Record 3 - Option Field 2 Value|             ...               |
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
   |              ...              |            Padding            |
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

FlowSet ID = Template ID
    A FlowSet ID precedes each group of Options Data Records within a Data FlowSet.
    The FlowSet ID maps to a previously generated Template ID corresponding to 
    this Options Template Record. The Collector MUST use the FlowSet ID to map 
    the appropriate type and length to any field values that follow.

Length
    The length of this FlowSet. Length is the sum of the lengths of the FlowSet 
    ID, Length itself, all the Options Data Records within this FlowSet, and the 
    padding bytes, if any.

Record N - Option Field M Value
    The remainder of the Data FlowSet is a collection of Flow Records,each 
    containing a set of scope and field values. The type and length of the 
    fields were previously defined in the Options Template Record referenced 
    by the FlowSet ID or Template ID.

Padding
    The Exporter SHOULD insert some padding bytes so that the subsequent FlowSet 
    starts at a 4-byte aligned boundary. It is important to note that the Length 
    field includes the padding bytes. Padding SHOULD be using zeros.

   The Data FlowSet format can be interpreted only if the Options Template FlowSet 
   corresponding to the Template ID is available at the Collector.


Data FlowSet with Options Data Records Example

   In this example, we report the following two records:

   Line Card ID | Export Packet| Export Flow
   ------------------------------------------
   Line Card 1  | 345          | 10201
   Line Card 2  | 690          | 20402

    0                   1                   2                   3
    0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
   |    FlowSet ID = 257           |         Length = 16           |
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
   |             1                 |             345               |
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
   |           10201               |              2                |
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
   |            690                |            20402              |
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+




*/

/* option data */
struct otd_sys
{
    u16   flowid;         /* 1 */
	u16   total_len;      /* sizeof(struct od_sys) */   
    u32   total_flow_exp; /* 1 输出流的总个数*/
    u32   total_pkt_exp;  /* 2 路由器输出报文的个数*/
    u16   as_type;        /* 3 peer or origin ，0为peer，1为origin*/
    u16   pad;            /* 4 填充字段*/
};


