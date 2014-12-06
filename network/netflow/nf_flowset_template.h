/*******************************************************************************
Templates greatly enhance the flexibility of the NetFlow record format, because 
they allow a NetFlow collector or display application to process NetFlow data 
without necessarily knowing the format of the data in advance. Templates are used 
to describe the type and length of individual fields within a NetFlow data record 
that match a template ID.

            The format of the Template FlowSet is as follows:
    0                   1                   2                   3
    0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
   |       FlowSet ID = 0          |          Length               |
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
   |      Template ID 256          |         Field Count           |
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
   |        Field Type 1           |         Field Length 1        |
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
   |        Field Type 2           |         Field Length 2        |
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
   |             ...               |              ...              |
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
   |        Field Type N           |         Field Length N        |
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
   |      Template ID 257          |         Field Count           |
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
   |        Field Type 1           |         Field Length 1        |
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
   |        Field Type 2           |         Field Length 2        |
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
   |             ...               |              ...              |
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
   |        Field Type M           |         Field Length M        |
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
   |             ...               |              ...              |
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
   |        Template ID K          |         Field Count           |
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
   |             ...               |              ...              |
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

FlowSet ID
    is used to distinguish template records from data records. A template record 
    always has a FlowSet ID in the range of 0-255. Currently, the template record 
    that describes flow fields has a FlowSet ID of zero and the template record 
    that describes option fields (described below) has a FlowSet ID of 1. A data 
    record always has a nonzero FlowSet ID greater than 255. 

Length
    Total length of this FlowSet.  Because an individual Template FlowSet MAY
    contain multiple Template Records, the Length value MUST be used to determine 
    the position of the next FlowSet record, which could be any type of FlowSet. 
    Length is the sum of the lengths of the FlowSet ID, the Length itself, and 
    all Template Records within this FlowSet.

Template ID
    Each of the newly generated Template Records is given a unique Template ID.
    This uniqueness is local to the Observation Domain that generated the Template 
    ID.Template IDs 0-255 are reserved for Template FlowSets, Options FlowSets, 
    and other reserved FlowSets yet to be created.Template IDs of Data FlowSets 
    are numbered from 256 to 65535.
    
Field Count
    Number of fields in this Template Record.Because a Template FlowSet usually 
    contains multiple Template Records, this field allows the Collector to 
    determine the end of the current Template Record and the start of the next.
    
Field Type
    A numeric value that represents the type of the field.  Refer to the 
    "Field Type Definitions" section.
    
Field Length
    The length of the corresponding Field Type, in bytes.  Refer to the 
    "Field Type Definitions" section.
*******************************************************************************/

/* v9 as aggre template */
struct t_as
{
    u16   flowid;         /* 0 */
	u16   total_len;      /* sizeof(struct t_as) */
	
    u16   templateid;	
    u16   filedcnt;       /* 11 */ 	
    u16   flows_type;     /* 1 */   
    u16   flows_len;	
    u16   pkts_type;      /* 2 */   
    u16   pkts_len;	
    u16   octets_type;    /* 3 */   
    u16   octets_len;	
    u16   first_type;     /* 4 */   
    u16   first_len;	
    u16   last_type;      /* 5 */   
    u16   last_len;	
    u16   input_type;     /* 6 */   
    u16   input_len;	
    u16   output_type;    /* 7 */   
    u16   output_len;	
    u16   srcas_type;     /* 8 */   
    u16   srcas_len;	
    u16   dstas_type;     /* 9 */   
    u16   dstas_len;	
    u16   direction_type; /* 10 */    
    u16   direction_len;	
    u16   pad_type;       /* 11 */   
    u16   pad_len;
};



