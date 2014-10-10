/*
struct module 模块管理结构
MODULE_ALIAS 模块别名
already_uses 模块a已经使用了模块b?
ref_module   模块a使用模块b

装载模块
init_module  kernel/module.c/SYSCALL_DEFINE3

移除模块
delete_module  kernel/module.c/SYSCALL_DEFINE2