
'''
Note 
 The ConfigParser module has been renamed to configparser in Python 3. The 2to3  tool 
 will automatically adapt imports when converting your sources to Python 3.
 
This module defines the class ConfigParser. The ConfigParser class implements a basic 
configuration file parser language which provides a structure similar to what you wo-
uld find on Microsoft Windows INI files.

'''


class RawConfigParser([defaults[, dict_type[, allow_no_value]]]): # ConfigParser.RawConfigParser
  '''
  The basic configuration object. When @defaults is given, it is initialized into the 
  dictionary of intrinsic defaults. When @dict_type is given, it will be used to cre-
  ate the dictionary objects for the list of sections, for the options within a sect-
  ion, and for the default values. When @allow_no_value is true (default: False), op-
  tions without values are accepted; the value presented for these is None.

  This class does not support the magical interpolation behavior.

  All option names are passed through the optionxform() method. Its default implemen-
  tation converts option names to lower case.
  '''

  def read(filenames):
    '''
    Attempt to read and parse a list of filenames, returning a list of filenames whi-
	ch were successfully parsed. If filenames is a string or Unicode string, it is t-
	reated as a single filename. If a file named in filenames cannot be opened,  that 
	file will be ignored. This is designed so that you can specify a list of potenti-
	al configuration file locations (for example, the current directory, the user’s -
	home directory, and some system-wide directory), and all existing configuration -
	files in the list will be read. If none of the named files exist,the ConfigParser 
	instance will contain an empty dataset. An application which requires initial va-
	lues to be loaded from a file should load the required file or files using      -
	readfp() before calling read() for any optional files:

    import ConfigParser, os

    config = ConfigParser.ConfigParser()
    config.readfp(open('defaults.cfg'))
    config.read(['site.cfg', os.path.expanduser('~/.myapp.cfg')])  
    '''
    pass
	
  def get(section, option):
    #Get an option value for the named section.
    pass
	
  def getint(section, option):
    # A convenience method which coerces the option in the specified section to an integer.
    pass

  def getfloat(section, option):
    # A convenience method which coerces the option in the specified section to a floating point number.
    pass
	
  def getboolean(section, option):
    '''
    A convenience method which coerces the option in the specified section to a     -
	Boolean value. Note that the accepted values for the option are "1", "yes",     -
	"true", and "on", which cause this method to return True, and "0", "no", "false", 
	and "off", which cause it to return False. These string values are checked in a -
	case-insensitive manner. Any other value will cause it to raise ValueError.	
    '''
    pass
	
  def items(section):
    # Return a list of (name, value) pairs for each option in the given section.
    pass


class ConfigParser([defaults[, dict_type[, allow_no_value]]]): # ConfigParser.ConfigParser
  '''
  Derived class of RawConfigParser that implements the magical interpolation  feature 
  and adds optional arguments to the get() and items() methods.
  '''
  
  def get(section, option[, raw[, vars]]):
    '''
    Get an option value for the named section. If vars is provided, it must be a dic-
	tionary. The option is looked up in vars (if provided), section, and in  defaults 
	in that order.

    All the '%' interpolations are expanded in the return values, unless the raw arg-
	ument is true. Values for interpolation keys are looked up in the same manner  as 
	the option.
    '''
    pass
	
  def items(section[, raw[, vars]]):
    '''
    Return a list of (name, value) pairs for each option in the given section. Optio-
	nal arguments have the same meaning as for the get() method.
    '''
    pass


class SafeConfigParser([defaults[, dict_type[, allow_no_value]]]): # ConfigParser.SafeConfigParser
  '''
  Derived class of ConfigParser that implements a more-sane variant of the magical i-
  nterpolation feature. This implementation is more predictable as well. New applica-
  tions should prefer this version if they don’t need to be compatible with older ve-
  rsions of Python.
  '''
  
  def set(section, option, value):
    '''
    If the given section exists, set the given option to the specified value; otherw-
	ise raise NoSectionError. value must be a string (str or unicode); if not,      -]
	TypeError is raised.
    '''
    pass

  
  
  
  
  
  
  
  
  
  
  
  
  
  

Python(2.7.6) ConfigParser - 读写配置文件
http://www.cnblogs.com/huey/p/4334152.html?utm_source=tuicool&utm_medium=referral


Python 标准库的 ConfigParser 模块提供一套 API 来读取和操作配置文件。

 

配置文件的格式

a) 配置文件中包含一个或多个 section， 每个 section 有自己的 option；

b) section 用 [sect_name] 表示，每个option是一个键值对，使用分隔符 = 或 : 隔开；

c) 在 option 分隔符两端的空格会被忽略掉

d) 配置文件使用 # 和 ; 注释

一个简单的配置文件样例 myapp.conf

复制代码
# database source
[db]
host = 127.0.0.1
port = 3306
user = root
pass = root

# ssh
[ssh]
host = 192.168.1.101
user = huey
pass = huey

复制代码
 

ConfigParser 的基本操作

a) 实例化 ConfigParser 并加载配置文件

cp = ConfigParser.SafeConfigParser()
cp.read('myapp.conf')
b) 获取 section 列表、option 键列表和 option 键值元组列表 

print 'all sections:', cp.sections()        # sections: ['db', 'ssh']
print 'options of [db]:', cp.options('db')  # options of [db]: ['host', 'port', 'user', 'pass']
print 'items of [ssh]:', cp.items('ssh')    # items of [ssh]: [('host', '192.168.1.101'), ('user', 'huey'), ('pass', 'huey')]
c) 读取指定的配置信息

print 'host of db:', cp.get('db', 'host')     # host of db: 127.0.0.1
print 'host of ssh:', cp.get('ssh', 'host')   # host of ssh: 192.168.1.101
d) 按类型读取配置信息：getint、 getfloat 和 getboolean

print type(cp.getint('db', 'port'))        # <type 'int'>
e) 判断 option 是否存在

print cp.has_option('db', 'host')    # True
f) 设置 option

cp.set('db', 'host','192.168.1.102')
g) 删除 option

cp.remove_option('db', 'host')
h) 判断 section 是否存在

print cp.has_section('db')    # True
i) 添加 section

cp.add_section('new_sect')
j) 删除 section

cp.remove_section('db')
k) 保存配置，set、 remove_option、 add_section 和 remove_section 等操作并不会修改配置文件，write 方法可以将 ConfigParser 对象的配置写到文件中

cp.write(open('myapp.conf', 'w'))
cp.write(sys.stdout)
 

Unicode 编码的配置

配置文件如果包含 Unicode 编码的数据，需要使用 codecs 模块以合适的编码打开配置文件。

myapp.conf

[msg]
hello = 你好
config_parser_unicode.py

复制代码
import ConfigParser
import codecs

cp = ConfigParser.SafeConfigParser()
with codecs.open('myapp.conf', 'r', encoding='utf-8') as f:
    cp.readfp(f)

print cp.get('msg', 'hello')
复制代码
 

allow_no_value

通常情况下， option 是一个键值对。但是，当 SafeConfigParser 的参数 allow_no_value 设置成 True 时，它允许 option 不设置值而只是作为一个标识。

allow_no_value.conf

# option as Flag
[flag]
flag_opt

allow_no_value.py

import ConfigParser

cp = ConfigParser.SafeConfigParser(allow_no_value = True)
cp.read('myapp.conf')
print cp.get('flag', 'flag_opt');    # None
allow_no_value 默认设置成 False，此时如果配置文件中存在没有设置值的 option，在读取配置文件时将抛出异常 ConfigParser.ParsingError。当 allow_no_value 设置成 True 时，如果一个 option 没有设置值，has_option 方法会返回 True，get 方法会返回 None。

 

DEFAULT section

如果配置文件中存在一个名为 DEFAULT 的 section，那么其他 section 会扩展它的 option 并且可以覆盖它的 option。

db.conf

复制代码
[DEFAULT]
host = 127.0.0.1
port = 3306

[db_root]
user = root
pass = root

[db_huey]
host = 192.168.1.101
user = huey
pass = huey
复制代码
default_section.py

print cp.get('db_root', 'host')    # 127.0.0.1
print cp.get('db_huey', 'host')    # 192.168.1.101
 

插值 Interpolation

SafeConfigParser 提供了插值的特性来结合数据。

url.conf

复制代码
[DEFAULT]
url = %(protocol)s://%(server)s:%(port)s/

[http]
protocol = http
server = localhost
port = 8080

[ftp]
url = %(protocol)s://%(server)s/
protocol = ftp
server = 192.168.1.102
复制代码
interpolation_demo.py

复制代码
import ConfigParser

cp = ConfigParser.SafeConfigParser()
cp.read('url.conf')

print cp.get('http', 'url')    # http://localhost:8080/
print cp.get('ftp', 'url')     # ftp://192.168.1.102/
复制代码



Python 解析配置模块之ConfigParser详解
 http://www.pythontab.com/html/2014/pythonhexinbiancheng_1120/919.html

 1.基本的读取配置文件
  -read(filename) 直接读取ini文件内容
  -sections() 得到所有的section，并以列表的形式返回
  -options(section) 得到该section的所有option
  -items(section) 得到该section的所有键值对
  -get(section,option) 得到section中option的值，返回为string类型
  -getint(section,option) 得到section中option的值，返回为int类型，还有相应的getboolean()和getfloat() 函数。

 2.基本的写入配置文件
  -add_section(section) 添加一个新的section
  -set( section, option, value) 对section中的option进行设置，需要调用write将内容写入配置文件。
 
 3.基本例子
  
 test.conf
  [sec_a] 
  a_key1 = 20 
  a_key2 = 10 
   
  [sec_b] 
  b_key1 = 121 
  b_key2 = b_value2 
  b_key3 = $r 
  b_key4 = 127.0.0.1

 parse_test_conf.py
  import ConfigParser 
  cf = ConfigParser.ConfigParser() 
  #read config 
  cf.read("test.conf") 
  # return all section 
  secs = cf.sections() 
  print 'sections:', secs  # sections: ['sec_b', 'sec_a']
   
  opts = cf.options("sec_a") 
  print 'options:', opts  # options: ['a_key1', 'a_key2']
      
  kvs = cf.items("sec_a") 
  print 'sec_a:', kvs     # sec_a: [('a_key1', "i'm value"), ('a_key2', '22')] 
   
  #read by type 
  str_val = cf.get("sec_a", "a_key1") 
  int_val = cf.getint("sec_a", "a_key2") 
   
  print "value for sec_a's a_key1:", str_val # value for sec_a's a_key1: i'm value
  print "value for sec_a's a_key2:", int_val # value for sec_a's a_key2: 22
   
  #write config 
  #update value 
  cf.set("sec_b", "b_key3", "new-$r") 
  #set a new value 
  cf.set("sec_b", "b_newkey", "new-value") 
  #create a new section 
  cf.add_section('a_new_section') 
  cf.set('a_new_section', 'new_key', 'new_value') 
   
  #write back to configure file 
  cf.write(open("test.conf", "w"))

 更新后的test.conf
   [sec_b] 
   b_newkey = new-value 
   b_key4 = 127.0.0.1 
   b_key1 = 121 
   b_key2 = b_value2 
   b_key3 = new-$r 
   
   [sec_a] 
   a_key1 = i'm value 
   a_key2 = 22 
   
   [a_new_section] 
   new_key = new_value

 4. Python的ConfigParser Module中定义了3个类对INI文件进行操作。分别是
    RawConfigParser、ConfigParser、SafeConfigParser。
	RawCnfigParser是最基础的INI文件读取类，
	ConfigParser、SafeConfigParser支持对%(value)s变量的解析。 
 
 设定配置文件test2.conf
  [portal] 
  url = http://%(host)s:%(port)s/Portal 
  host = localhost 
  port = 8080

 使用RawConfigParser：
  import ConfigParser 
  
  cf = ConfigParser.RawConfigParser() 
  
  print "use RawConfigParser() read" 
  cf.read("test2.conf") 
  print cf.get("portal", "url") 
  
  print "use RawConfigParser() write" 
  cf.set("portal", "url2", "%(host)s:%(port)s") 
  print cf.get("portal", "url2")

 得到终端输出：
  use RawConfigParser() read 
  http://%(host)s:%(port)s/Portal 
  use RawConfigParser() write 
  %(host)s:%(port)s

 改用ConfigParser：
  import ConfigParser 
  
  cf = ConfigParser.ConfigParser() 
  
  print "use ConfigParser() read" 
  cf.read("test2.conf") 
  print cf.get("portal", "url") 
  
  print "use ConfigParser() write" 
  cf.set("portal", "url2", "%(host)s:%(port)s") 
  print cf.get("portal", "url2")

 得到终端输出：
  use ConfigParser() read 
  http://localhost:8080/Portal 
  use ConfigParser() write 
  localhost:8080

 改用SafeConfigParser：
  import ConfigParser 
  
  cf = ConfigParser.SafeConfigParser() 
  
  print "use SafeConfigParser() read" 
  cf.read("test2.conf") 
  print cf.get("portal", "url") 
  
  print "use SateConfigParser() write" 
  cf.set("portal", "url2", "%(host)s:%(port)s") 
  print cf.get("portal", "url2")

 得到终端输出(效果同ConfigParser)：
  use SafeConfigParser() read 
  http://localhost:8080/Portal 
  use SateConfigParser() write 
  localhost:8080


  
  
  
  
  
  
  
  
