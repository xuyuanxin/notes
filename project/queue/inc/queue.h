
typedef struct queue_node_tag
{
    int qn_key;
	void *qn_data;
}queue_node;


typedef struct queue_ctrl_tag
{
    char         q_name[32];
    unsigned int q_w_idx;
	unsigned int q_r_idx;
	unsigned int q_size;  /*队列大小*/
	unsigned int q_count; /*队列中的数据个数，初始为0写加读减*/
	queue_node   q_node[0];/*零长数组，qnode变量不占空间*/
}queue_s;


/*创建一个大小为@size的队列,成功返回队列控制头,失败返回NULL*/
queue_s *queue_create(char *name,int size);
 
