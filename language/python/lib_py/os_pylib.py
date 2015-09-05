# os.

'''
@top
    需要遍历的目录树的路径。
@topdown                                                                             |
    默认值是"True", 表示首先返回目录树下的文件, 然后在遍历目录树的子目录. Topdown的值|
	为"False"时, 则表示先遍历目录树的子目录, 返回子目录下的文件, 最后返回根目录下的文|
	件.                                                                              |
@onerror                                                                             |
    默认值是"None", 表示忽略文件遍历时产生的错误. 如果不为空, 则提供一个自定义函数提 |
	示错误信息后继续遍历或抛出异常中止遍历.
@followlinks
    默认值是False, 默认情况下是不会遍历快捷方式的, 如果系统支持需要特殊指定.
@return
    os.walk方法返回三元组：
    dirpath：  目录的路径。
    dirnames： dirpath目录下所有子目录列表（不包含"."和".."）。
    filenames：dirpath目录下所有非目录文件列表。
'''
def walk(top, topdown=True, onerror=None, followlinks=False):
    pass

''' os.system(command)
Execute the command (a string) in a subshell. 
'''
def system(command):
    pass

	
#                      os.path

'''

'''
def join(path, *paths):
    pass