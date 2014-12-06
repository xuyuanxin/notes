
unsigned int nf_pkt_seq;

/* 只发送一个as聚合时的NetFlow报文头 */
void nfv9_send_template_as( )
{  
	t_as tas;
    struct nfv9_hdr v9head;

    /* NetFlow Head */
	v9head.ver          = 9;
	v9head.count        = 1; /*报文里只有1个as聚合模板*/
    v9head.sys_uptime   = get_boot_mseconds();
	v9head.unix_seconds = get_seconds_since_1970();
	v9head.pkt_seq      = nf_pkt_seq++;
	v9head.sid          = 1;

    /* NetFlow Data  as template */
    tas.flowid         = 0; 
    tas.total_len      = sizeof(struct t_as);

    tas.templateid     = NFT_AS;	/* as aggre template id */
    tas.filedcnt	   = 11;	/* nfa_as中变量的个数 */

    tas.flows_type     = FLOWS;   /* 指示 nfa_as 中 as_flows 的意思(流的个数) */
    tas.flows_len	   = 4;	   /* 指示 nfa_as 中 as_flows 的大小(四个字节) 下面类似*/
    tas.pkts_type      = IN_PKTS;	
    tas.pkts_len       = 4; 	  
    tas.octets_type    = IN_BYTES;   
    tas.octets_len     = 4;	
    tas.first_type     = FIRST_SWITCHED;	
    tas.first_len	   = 4;  
    tas.last_type      = LAST_SWITCHED;   
    tas.last_len       = 4; 
    tas.input_type     = INPUT_SNMP;	
    tas.input_len	   = 2; /*default is 2, but higher values can be used*/
    tas.output_type    = OUTPUT_SNMP;   
    tas.output_len     = 2; /*default is 2, but higher values can be used*/
    tas.srcas_type     = SRC_AS;	
    tas.srcas_len	   = 2; /*be 2 or 4. By default N is  2 */
    tas.dstas_type     = DST_AS;	
    tas.dstas_len	   = 2; /*be 2 or 4. By default N is  2 */  
    tas.direction_type = DIRECTION;   
    tas.direction_len  = 1; /**/			 
    tas.pad_type       = 210;  /* ?? */	 
    tas.pad_len        = 3;	  /**/
	
	/* ip + udp + NetFlowHead + NetFlowData */

    return;
}


/* 发送一个as数据时的NetFlow报文 */
void nfv9_send_data_as()
{
	struct d_as aggre_as;
    struct nfv9_hdr v9head;

    /* NetFlow Head */
	v9head.ver          = 9;
	v9head.count        = 1; /*报文里只有1个as聚合数据*/
    v9head.sys_uptime   = get_boot_mseconds();
	v9head.unix_seconds = get_seconds_since_1970();
	v9head.pkt_seq      = nf_pkt_seq++;
	v9head.sid          = 1;

    /* NetFlow Data as data */
    aggre_as.flowid    = NFT_AS; 
    aggre_as.total_len = sizeof(struct d_as);

    /* 下面的数据根据实际情况填写 */
    aggre_as.as_flows = 1;



	/* ip + udp + NetFlowHead + NetFlowData */

}

int nfv9_send_option_template()
{
    struct ot_sys otsys;
    struct nfv9_hdr v9head;

    /* NetFlow Head */
	v9head.ver          = 9;
	v9head.count        = 1; /*报文里只有1个 option template */
    v9head.sys_uptime   = get_boot_mseconds();
	v9head.unix_seconds = get_seconds_since_1970();
	v9head.pkt_seq      = nf_pkt_seq++;
	v9head.sid          = 1;

    /* NetFlow Data -- option template */
	otsys.flowid = 1;
	otsys.total_len = sizeof(struct ot_sys);
	
	otsys.templateid = NFT_OT_SYS;
	
	otsys.option_scope_len = 4;/* why */ 
	otsys.option_len       = 16;/* why */ 
	
	otsys.scope_field_type    = 1;
	otsys.scope_field_len     = 0;   /* why */ 
	
	otsys.total_flow_exp_type =   TOTAL_FLOWS_EXP;	
	otsys.total_flow_exp_len  =   4;

    otsys.total_exp_pkts_send_type = TOTAL_PKTS_EXP;
    otsys.total_exp_pkts_send_len = 4;

    otsys.as_type = 43;
    otsys.as_len = 2;

    otsys.pad_type = 210;
    otsys.pad_len = 2;

    otsys.pad = 0;
}

int nfv9_send_option_data()
{
    struct otd_sys otdsys;
    struct nfv9_hdr v9head;

    /* NetFlow Head */
	v9head.ver          = 9;
	v9head.count        = 1; /*报文里只有1个 option data system */
    v9head.sys_uptime   = get_boot_mseconds();
	v9head.unix_seconds = get_seconds_since_1970();
	v9head.pkt_seq      = nf_pkt_seq++;
	v9head.sid          = 1;

    /* NetFlow Data -- option data system */
	otdsys.flowid    = NFT_OT_SYS;
	otdsys.total_len = sizeof(struct otd_sys);

	/* 根据实际情况填写数据 */
	otdsys.total_flow_exp = 1;	
	otdsys.total_pkt_exp  = 1;	
	otdsys.as_type        = 1;
    otdsys.pad            = 0;
}


/*******************************************************************************
Let us consider the example of an Export Packet composed of a Template FlowSet, 
a Data FlowSet (which contains three Flow Data   Records), an Options Template 
FlowSet, and a Data FlowSet (which   contains two Options Data Records).


Export Packet:

   +--------+---------------------------------------------. . .
   |        | +--------------+ +-----------------------+
   | Packet | | Template     | | Data                  |
   | Header | | FlowSet      | | FlowSet               |   . . .
   |        | | (1 Template) | | (3 Flow Data Records) |
   |        | +--------------+ +-----------------------+
   +--------+---------------------------------------------. . .

       . . .+-------------------------------------------------+
            +------------------+ +--------------------------+ |
            | Options          | | Data                     | |
       . . .| Template FlowSet | | FlowSet                  | |
            | (1 Template)     | | (2 Options Data Records) | |
            +------------------+ +--------------------------+ |
       . . .--------------------------------------------------+



11.1.  Packet Header Example

   The Packet Header is composed of:

    0                   1                   2                   3
    0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
   |     Version = 9               |          Count = 7            |
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
   |                           sysUpTime                           |
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
   |                           UNIX Secs                           |
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
   |                       Sequence Number                         |
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
   |                           Source ID                           |
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

count 7
    a Template FlowSet
    a Data FlowSet (which contains three Flow Data  Records), 
    an Options Template FlowSet
    a Data FlowSet (which   contains two Options Data Records).   


11.2.  Template FlowSet Example

   We want to report the following Field Types:
   -  The source IP address (IPv4), so the length is 4
   -  The destination IP address (IPv4), so the length is 4
   -  The next-hop IP address (IPv4), so the length is 4
   -  The number of bytes of the Flow
   -  The number of packets of the Flow

   Therefore, the Template FlowSet is composed of the following:

    0                   1                   2                   3
    0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
   |       FlowSet ID = 0          |      Length = 28 bytes        |
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
   |       Template ID 256         |       Field Count = 5         |
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
   |     IP_SRC_ADDR = 8           |       Field Length = 4        |
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
   |     IP_DST_ADDR = 12          |       Field Length = 4        |
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
   |     IP_NEXT_HOP = 15          |       Field Length = 4        |
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
   |       IN_PKTS = 2             |       Field Length = 4        |
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
   |       IN_BYTES = 1            |       Field Length = 4        |
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

field count 5
    IP_SRC_ADDR  IP_DST_ADDR  IP_NEXT_HOP  IN_PKTS IN_BYTES



11.3.  Data FlowSet Example

   In this example, we report the following three Flow Records:

   Src IP addr. | Dst IP addr. | Next Hop addr. | Packet | Bytes
                |              |                | Number | Number
   ---------------------------------------------------------------
   198.168.1.12 | 10.5.12.254  | 192.168.1.1    | 5009   | 5344385
   192.168.1.27 | 10.5.12.23   | 192.168.1.1    | 748    | 388934
   192.168.1.56 | 10.5.12.65   | 192.168.1.1    | 5      | 6534


    0                   1                   2                   3
    0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
   |       FlowSet ID = 256        |          Length = 64          |
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
   |                          198.168.1.12                         |
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
   |                          10.5.12.254                          |
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
   |                          192.168.1.1                          |
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
   |                             5009                              |
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
   |                            5344385                            |
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
   |                          192.168.1.27                         |
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
   |                           10.5.12.23                          |
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
   |                          192.168.1.1                          |
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
   |                              748                              |
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
   |                             388934                            |
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
   |                          192.168.1.56                         |
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
   |                           10.5.12.65                          |
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
   |                           192.168.1.1                         |
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
   |                               5                               |
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
   |                              6534                             |
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+


   Note that padding was not necessary in this example.


11.4.  Options Template FlowSet Example

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


11.5.  Data FlowSet with Options Data Records Example

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


