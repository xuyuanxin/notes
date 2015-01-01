/*
整个内存划分为若干"节点",节点内部又划分为若干个内存域。

pg_data_t   内存节点管理结构
node_states 节点状态
node_set_state

zone        内存区域管理结构
zone_type   内存域的类型
zone_set_flag

page        页管理结构

---->内存管理初始化
NODE_DATA 通过节点ID获得该节点的管理结构 

init_per_zone_pages_min

start_kernel
  setup_arch
    machine_specific_memory_setup 创建一个列表,包括系统占据的内存区和空闲内存区
    parse_early_param
    setup_memory  确定每个节点可用的物理内存页的数目 初始化bootmem分配器
    paging_init   建立只能用于内核的页表,用户空间无法访问
      pagetable_init
    zone_sizes_init  初始化系统中的所有节点管理结构
      add_active_range
      free_area_init_nodes
  build_all_zonelists 建立管理节点及其内存域的数据结构
    __build_all_zonelists
      build_zonelists
        build_zonelists_node

paging_init
  是否启用了PAE
    set_nx
  pagetable_init
    在可能的情况下,使用PSE PGE扩展
    kernel_physical_mapping_init
    初始化固定映射
    permanent_kmaps_init
  load_cr3
  __flsh_all_tlb
  kmap_init



---->内核1G空间
       high_memory   VMALLOC_START     VMALLOC_END                         4G
            |          |                   |                                |
           \|/        \|/                 \|/                              \|/
 +--------------------------------------------------------------------------+
 | 直接映射 | 保留(8M) |      VMALLOC      | 保留 |   持久映射   | 固定映射 |
 +--------------------------------------------------------------------------+
/|\                                              /|\            /|\
 |                                                |              |
__PAGE_OFFSET                                PKMAP_BASE        FIXADDR_START

max_low_pfn      物理内存数量小于896M的系统上内存页的数目,即被内核直接映射的最后一个页框的页框号 find_max_low_pfn中设置
                 
high_memory      setup_memory中设定

VMALLOC_OFFSET   
VMALLOC_RESERVE  vmalloc区域的长度
MAXMEM           内核可以直接寻址的物理内存的最大可能数量
VMALLOC_END

fixed_addresses  枚举类型
fix_to_virt      此函数用来计算固定映射常数的虚拟地址
set_fixmap       建立固定映射虚拟地址和物理地址间的关系



---->伙伴系统
struct zone {
	struct free_area	free_area[MAX_ORDER];
}

MAX_ORDER


free_area_init_nodes   入参是系统中各个内存域的页帧边界
  free_area_init_node
  check_for_regular_memory
                                                                                                                    


























