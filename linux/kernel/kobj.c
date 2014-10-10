kobject
kset
	
/*设定kobject中name成员*/
int kobject_set_name(struct kobject *kobj, const char *fmt, ...)

/*初始化一个内核对象的kobject结构*/
void kobject_init(struct kobject *kobj, struct kobj_type *ktype)

/*
  1 建立kobject对象间的层次关系
  2 在sysfs文件系统中建立一个目录*/
int kobject_add(struct kobject *kobj, struct kobject *parent,const char *fmt, ...)

int kobject_init_and_add(struct kobject *kobj, struct kobj_type *ktype,struct kobject *parent, const char *fmt, ...)

/*分配并初始化一个kobject*/
struct kobject *kobject_create(void)

struct kobject *kobject_create_and_add(const char *name, struct kobject *parent)

/*在sysfs文件树中把kobj对应的目录删除,如果kobj属于某一kset的话,将其从kset的链表中删除*/
void kobject_del(struct kobject *kobj)


/*为一个kobject对象创建一个属性文件(kobj->sd对应的目录下生成一个属性文件)
  用户空间使用这个属性文件时,通过open打开，最终会调用sysfs_open_file*/
sysfs_create_file
sysfs_remove_file






kset_init
kset_register
kset_create_and_add



kobject_uevent


bus_type  /*总线*/
bus_attribute  /*总线属性*/


buses_init
bus_register
bus_create_file



struct device /*设备*/
struct kset *devices_kset;/*所有device类型内核对象的容器*/

devices_init
device_initialize
device_register



struct device_driver /*驱动*/


struct class   /*设备类*/


