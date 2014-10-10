/*
---->slab分配器
kmem_cache   缓存管理结构

kmem_cache_init   创建系统中的第一个slab缓存
kmem_cache_create 创建slab缓存


内部接口
calculate_slab_order  计算slab的对象数，分配给slab的页框阶数并返回slab的剩余空间，即碎片大小。

