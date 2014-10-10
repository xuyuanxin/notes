/*

sysfs初始化
sysfs_init






struct task_struct {
    int link_count; 
    int total_link_count;
    struct fs_struct *fs;
    struct files_struct *files;
    struct nsproxy *nsproxy;
}
struct file_system_type 描述一个文件系统
struct vfsmount         每个装载的文件系统都对应一个vfsmount结构的实例
super_block             超级块


expand_fdtable

register_filesystem   注册文件系统,file_systems链表管理

安装
namespace.c/SYSCALL_DEFINE5


