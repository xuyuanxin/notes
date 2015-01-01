/*
struct cdev 一个这种结构表示一个字符设备

chrdevs   设备号管理
cdev_map  字符设备管理

先搞到设备号       alloc_chrdev_region 
已经有了就直接注册 register_chrdev_region
有了设备号再初始化 cdev_init
最后加入           cdev_add


init_special_inode 注册 def_chr_fops chrdev_open
do_dentry_open -> fops_get

chrdev_open  打开字符设备的通用函数



