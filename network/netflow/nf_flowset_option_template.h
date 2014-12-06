
#define SFT_SYS 1  /* Scope Field Type system*/
#define SFT_IF  2  /* Interface*/ 
#define SFT_LC  3  /* line card */
#define SFT_C   4  /* cache */
#define SFT_T   5  /* template */


/*******************************************************************************
选项模板
    目前有5中类型的选项模板(SFT_SYS SFT_IF SFT_LC SFT_C SFT_T),每个选择模板里可以
    包含多种类型的模板。
    
    每一种选项模板称为一个scope，用 scope filed type 和 scope file length 表示。type
    表示是那种选项模板，实际中是用一个变量表示模板类型，length表示这个变量占用几个字节
    length变量本身一般占2个字节。

Option Scope Length
    所有scope占用的字节，如果模板里包含两个选项模板，这个字段的值就是8.

Option Length
    每种类型的选项模板包含若干个option，每个option有一个option field type 和 一个
    option field length。type表示是那种option类型(TOTAL_PKTS_EXP等)，实际中是用
    一个变量表示模板类型，length表示这个变量占用几个字节，length变量本身一般占2
    个字节。

Options Template FlowSet Format
    The Options Template Record (and its corresponding Options Data Record) is 
    used to supply information about the NetFlow process configuration or NetFlow 
    process specific data, rather than supplying information about IP Flows.

    For example, the Options Template FlowSet can report the sample rate of a 
    specific interface, if sampling is supported, along with the sampling method 
    used.

          The format of the Options Template FlowSet follows.
    0                   1                   2                   3
    0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
   |       FlowSet ID = 1          |          Length               |
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
   |         Template ID           |      Option Scope Length      |
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
   |        Option Length          |       Scope 1 Field Type      |
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
   |     Scope 1 Field Length      |               ...             |
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
   |     Scope N Field Length      |      Option 1 Field Type      |
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
   |     Option 1 Field Length     |             ...               |
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
   |     Option M Field Length     |           Padding             |
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

FlowSet ID = 1
    A FlowSet ID value of 1 is reserved for the Options Template.

Length
    Total length of this FlowSet. Each Options Template FlowSet MAY contain 
    multiple Options Template Records. Thus, the Length value MUST be used 
    to determine the position of the next FlowSet record, which could be either 
    a Template FlowSet or Data FlowSet. Length is the sum of the lengths of the 
    FlowSet ID, the Length itself, and all Options Template Records within this 
    FlowSet Template ID.
    
Template ID 		
    Template ID of this Options Template.This value is greater than 255.

Option Scope Length 		
    The length in bytes of any Scope field definition contained in the Options 
    Template Record (The use of "Scope" is described below).

Option Length 
    The length (in bytes) of any options field definitions	contained in this 
    Options Template Record.
    
Scope 1 Field Type		   
    The relevant portion of the Exporter/NetFlow process to which the Options 
    Template Record refers. Currently defined values are:			  
    1 System  2 Interface  3 Line Card  4 Cache  5 Template		  
    For example, the NetFlow process can be implemented on a per-interface basis, 
    so if the Options Template Record were reporting on how the NetFlow process 
    is configured, the Scope for the report would be 2 (interface). The associated	
    interface ID would then be carried in the associated Options Data FlowSet. 
    The Scope can be limited further by listing multiple scopes that all must match 
    at the same time.Note that the Scope fields always precede the Option fields.

Scope 1 Field Length
    The length (in bytes) of the Scope field, as it would appear in an Options 
    Data Record. 

Option 1 Field Type		  
    A numeric value that represents the type of field that would appear in the 
    Options Template Record.Refer to the Field Type Definitions section.   

Option 1 Field Length		 
    The length (in bytes) of the Option field.



Options Template FlowSet Example

   Per line card (the Exporter is composed of two line cards), we want
   to report the following Field Types:
   - Total number of Export Packets
   - Total number of exported Flows

   The format of the Options Template FlowSet is as follows:

    0                   1                   2                   3
    0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
   |       FlowSet ID = 1          |          Length = 24          |
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
   |       Template ID 257         |    Option Scope Length = 4    |
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
   |       Option Length = 8       |  Scope 1 Field Type = 3       |
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
   |   Scope 1 Field Length = 2    |   TOTAL_EXP_PKTS_SENT = 41    |
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
   |       Field Length = 2        |     TOTAL_FLOWS_EXP = 42      |
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
   |       Field Length = 2        |           Padding             |
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
   
Option Scope Length = 4      
    一个选项模板有若干个scope，这里只有一个scope，这个scope有一个scope type
    和一个scope len。scope type表示scope的类型(这里是SFT_LC，占两个字节)，
    scope len 表示scope type变量占用2个字节。
    
Option Length = 8 
    每个scope下有若干个option，这里只有1个scope，这个scope有两个option(包数和流数)
    每个option又包含一个type和len，type占用2个字节，len占用2个字节。所以一个option
    占用4个字节，两个option占用8个字节。
  
Scope 1 Field Type 3         
    scope指的是SFT_SYS等类型，这里指SFT_LC，即要报告接口相关的东西
    
Scope 1 Field Length = 2    
    用一个变量表示scipe类型，这个变量占用2个字节

Option 1 Field Type      TOTAL_EXP_PKTS_SENT = 41      
    这个scope下要报告信息的类型，这里是41，表示要报告包的个数(TOTAL_PKTS_EXP)

Option 1 Field Length  2  
    用一个变量表示包的个数，这个变量占用2个字节

Option 2 Field Type      TOTAL_FLOWS_EXP = 42      
    这个scope下要报告的第二个信息的类型，这里是42，表示要报告流的个数(TOTAL_FLOWS_EXP)

Option 2 Field Length  2  
    用一个变量表示流的个数，这个变量占用2个字节

*******************************************************************************/

/* Options Template FlowSet -- System */
struct ot_sys
{
	u16   flowid;		    /* 1 */
	u16   total_len;	    /* sizeof(struct ot_sys) */
	
    u16   templateid;       /* 是多少还不太清楚(自己定的吧) */
    u16   option_scope_len; /* Option Template中包含的所有scope域的字节长度*/
    u16   option_len;       /* Option Template中包含的所有Option域的字节长度*/
    u16   scope_field_type; /* 0x0001 System，0x0002 Interface */
    u16   scope_field_len;  /* 该域给出了Scope域的长度(字节)，取0，即不输出该域值*/
    
    u16   total_flow_exp_type; /*输出流的总个数*/
    u16   total_flow_exp_len; 
    u16   total_exp_pkts_send_type; /*路由器输出报文的个数*/
    u16   total_exp_pkts_send_len;
    u16   as_type;                    /* peer or origin ，0为peer，1为origin*/
    u16   as_len;
    u16   pad_type;                          /*四字节对齐*/
    u16   pad_len;
    u16   pad;                       /*四字节对齐*/
};

