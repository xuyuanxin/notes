
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
	al configuration file locations (for example, the current directory, the user��s -
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
  tions should prefer this version if they don��t need to be compatible with older ve-
  rsions of Python.
  '''
  
  def set(section, option, value):
    '''
    If the given section exists, set the given option to the specified value; otherw-
	ise raise NoSectionError. value must be a string (str or unicode); if not,      -]
	TypeError is raised.
    '''
    pass

  
  
  
  
  
  
  
  
  
  
  
  
  
  

Python(2.7.6) ConfigParser - ��д�����ļ�
http://www.cnblogs.com/huey/p/4334152.html?utm_source=tuicool&utm_medium=referral


Python ��׼��� ConfigParser ģ���ṩһ�� API ����ȡ�Ͳ��������ļ���

 

�����ļ��ĸ�ʽ

a) �����ļ��а���һ������ section�� ÿ�� section ���Լ��� option��

b) section �� [sect_name] ��ʾ��ÿ��option��һ����ֵ�ԣ�ʹ�÷ָ��� = �� : ������

c) �� option �ָ������˵Ŀո�ᱻ���Ե�

d) �����ļ�ʹ�� # �� ; ע��

һ���򵥵������ļ����� myapp.conf

���ƴ���
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

���ƴ���
 

ConfigParser �Ļ�������

a) ʵ���� ConfigParser �����������ļ�

cp = ConfigParser.SafeConfigParser()
cp.read('myapp.conf')
b) ��ȡ section �б�option ���б�� option ��ֵԪ���б� 

print 'all sections:', cp.sections()        # sections: ['db', 'ssh']
print 'options of [db]:', cp.options('db')  # options of [db]: ['host', 'port', 'user', 'pass']
print 'items of [ssh]:', cp.items('ssh')    # items of [ssh]: [('host', '192.168.1.101'), ('user', 'huey'), ('pass', 'huey')]
c) ��ȡָ����������Ϣ

print 'host of db:', cp.get('db', 'host')     # host of db: 127.0.0.1
print 'host of ssh:', cp.get('ssh', 'host')   # host of ssh: 192.168.1.101
d) �����Ͷ�ȡ������Ϣ��getint�� getfloat �� getboolean

print type(cp.getint('db', 'port'))        # <type 'int'>
e) �ж� option �Ƿ����

print cp.has_option('db', 'host')    # True
f) ���� option

cp.set('db', 'host','192.168.1.102')
g) ɾ�� option

cp.remove_option('db', 'host')
h) �ж� section �Ƿ����

print cp.has_section('db')    # True
i) ��� section

cp.add_section('new_sect')
j) ɾ�� section

cp.remove_section('db')
k) �������ã�set�� remove_option�� add_section �� remove_section �Ȳ����������޸������ļ���write �������Խ� ConfigParser ���������д���ļ���

cp.write(open('myapp.conf', 'w'))
cp.write(sys.stdout)
 

Unicode ���������

�����ļ�������� Unicode ��������ݣ���Ҫʹ�� codecs ģ���Ժ��ʵı���������ļ���

myapp.conf

[msg]
hello = ���
config_parser_unicode.py

���ƴ���
import ConfigParser
import codecs

cp = ConfigParser.SafeConfigParser()
with codecs.open('myapp.conf', 'r', encoding='utf-8') as f:
    cp.readfp(f)

print cp.get('msg', 'hello')
���ƴ���
 

allow_no_value

ͨ������£� option ��һ����ֵ�ԡ����ǣ��� SafeConfigParser �Ĳ��� allow_no_value ���ó� True ʱ�������� option ������ֵ��ֻ����Ϊһ����ʶ��

allow_no_value.conf

# option as Flag
[flag]
flag_opt

allow_no_value.py

import ConfigParser

cp = ConfigParser.SafeConfigParser(allow_no_value = True)
cp.read('myapp.conf')
print cp.get('flag', 'flag_opt');    # None
allow_no_value Ĭ�����ó� False����ʱ��������ļ��д���û������ֵ�� option���ڶ�ȡ�����ļ�ʱ���׳��쳣 ConfigParser.ParsingError���� allow_no_value ���ó� True ʱ�����һ�� option û������ֵ��has_option �����᷵�� True��get �����᷵�� None��

 

DEFAULT section

��������ļ��д���һ����Ϊ DEFAULT �� section����ô���� section ����չ���� option ���ҿ��Ը������� option��

db.conf

���ƴ���
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
���ƴ���
default_section.py

print cp.get('db_root', 'host')    # 127.0.0.1
print cp.get('db_huey', 'host')    # 192.168.1.101
 

��ֵ Interpolation

SafeConfigParser �ṩ�˲�ֵ��������������ݡ�

url.conf

���ƴ���
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
���ƴ���
interpolation_demo.py

���ƴ���
import ConfigParser

cp = ConfigParser.SafeConfigParser()
cp.read('url.conf')

print cp.get('http', 'url')    # http://localhost:8080/
print cp.get('ftp', 'url')     # ftp://192.168.1.102/
���ƴ���



Python ��������ģ��֮ConfigParser���
 http://www.pythontab.com/html/2014/pythonhexinbiancheng_1120/919.html

 1.�����Ķ�ȡ�����ļ�
  -read(filename) ֱ�Ӷ�ȡini�ļ�����
  -sections() �õ����е�section�������б����ʽ����
  -options(section) �õ���section������option
  -items(section) �õ���section�����м�ֵ��
  -get(section,option) �õ�section��option��ֵ������Ϊstring����
  -getint(section,option) �õ�section��option��ֵ������Ϊint���ͣ�������Ӧ��getboolean()��getfloat() ������

 2.������д�������ļ�
  -add_section(section) ���һ���µ�section
  -set( section, option, value) ��section�е�option�������ã���Ҫ����write������д�������ļ���
 
 3.��������
  
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

 ���º��test.conf
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

 4. Python��ConfigParser Module�ж�����3�����INI�ļ����в������ֱ���
    RawConfigParser��ConfigParser��SafeConfigParser��
	RawCnfigParser���������INI�ļ���ȡ�࣬
	ConfigParser��SafeConfigParser֧�ֶ�%(value)s�����Ľ����� 
 
 �趨�����ļ�test2.conf
  [portal] 
  url = http://%(host)s:%(port)s/Portal 
  host = localhost 
  port = 8080

 ʹ��RawConfigParser��
  import ConfigParser 
  
  cf = ConfigParser.RawConfigParser() 
  
  print "use RawConfigParser() read" 
  cf.read("test2.conf") 
  print cf.get("portal", "url") 
  
  print "use RawConfigParser() write" 
  cf.set("portal", "url2", "%(host)s:%(port)s") 
  print cf.get("portal", "url2")

 �õ��ն������
  use RawConfigParser() read 
  http://%(host)s:%(port)s/Portal 
  use RawConfigParser() write 
  %(host)s:%(port)s

 ����ConfigParser��
  import ConfigParser 
  
  cf = ConfigParser.ConfigParser() 
  
  print "use ConfigParser() read" 
  cf.read("test2.conf") 
  print cf.get("portal", "url") 
  
  print "use ConfigParser() write" 
  cf.set("portal", "url2", "%(host)s:%(port)s") 
  print cf.get("portal", "url2")

 �õ��ն������
  use ConfigParser() read 
  http://localhost:8080/Portal 
  use ConfigParser() write 
  localhost:8080

 ����SafeConfigParser��
  import ConfigParser 
  
  cf = ConfigParser.SafeConfigParser() 
  
  print "use SafeConfigParser() read" 
  cf.read("test2.conf") 
  print cf.get("portal", "url") 
  
  print "use SateConfigParser() write" 
  cf.set("portal", "url2", "%(host)s:%(port)s") 
  print cf.get("portal", "url2")

 �õ��ն����(Ч��ͬConfigParser)��
  use SafeConfigParser() read 
  http://localhost:8080/Portal 
  use SateConfigParser() write 
  localhost:8080


  
  
  
  
  
  
  
  
