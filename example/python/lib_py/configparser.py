import ConfigParser 

rawcf = ConfigParser.RawConfigParser() 

print rawcf.read("test.conf") 
print type(rawcf.read("test.conf") )
print rawcf.items('sec_a')

exit(0)


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
#cf.write(open("test.conf", "w"))

