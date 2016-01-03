#coding=utf-8

from datetime import datetime
import pandas as pd
import csv
from urlparse import urlparse
from sys import argv
from datetime import timedelta
import re
import os
import time
from pymongo import MongoClient
#from log_to_mongo_lib import *
import tldextract

def init_set(coll, _set):
    cursor = coll.find({}, {"_id": 1})
    for item in cursor:
        _set.add(item["_id"])

def init_domain_set(f, domain_set):
    for line in open(f):
        ext = tldextract.extract(line.strip())
        domain_set.add(".".join(ext[1:]))

def init_sus_domain_set():
    sus_domain_set = set([])
    init_domain_set(domains_path + os.sep + "hosts_badzeus.txt", sus_domain_set)
    init_domain_set(domains_path + os.sep + "hosts_spyeye.txt", sus_domain_set)
    init_domain_set(domains_path + os.sep + "hosts_palevo.txt", sus_domain_set)
    init_domain_set(domains_path + os.sep + "hosts_feodo.txt", sus_domain_set)
    init_domain_set(domains_path + os.sep + "hosts_cybercrime.txt", sus_domain_set)
    init_domain_set(domains_path + os.sep + "hosts_malwaredomains.txt", sus_domain_set)
    init_domain_set(domains_path + os.sep + "hosts_malwaredomainlist.txt", sus_domain_set)
    init_from_phishtank(sus_domain_set)
    init_domain_set(domains_path + os.sep + "hosts_hphosts.txt", sus_domain_set)
    return sus_domain_set

def init_outlier_domain_set():
    outlier_domain_set = set([])
    init_domain_set(domains_path + os.sep + "domain_whitelist.txt", outlier_domain_set)
    init_domain_set(domains_path + os.sep + "cdn.txt", outlier_domain_set)
    init_domain_set(domains_path + os.sep + "cdn_new.txt", outlier_domain_set)
    return outlier_domain_set

def init_from_phishtank(domain_set):
    with open(domains_path + os.sep + 'hosts_phishtank.csv', 'rb') as csvfile:
        reader = csv.reader(csvfile)
        for row in reader:
            ext = tldextract.extract(urlparse(row[1]).netloc)
            # print ".".join(ext[1:])
            domain_set.add(".".join(ext[1:]))

def init_from_alexa(begin=1, end=10000):
    df = pd.read_csv(domains_path + os.sep + 'top-1m.csv', names=['rank', 'domain'], header=None, encoding='utf-8')
    return set(list(df[(df['rank'] <= end) & (df['rank'] >= begin)]['domain']))

def mongo_print(args):
    run_log_writer = open("run.log", "a")
    print str(args)
    run_log_writer.write(str(args) + "\n")
    run_log_writer.close()

def load_one_line(_dict, timestamp, subdomain, key, item, ttl, count):
    '''
	@_dict: domain or ip
    @item : ip or domain
    '''

    if key not in _dict:
        _dict[key]               = {}
        _dict[key]["_id"]        = key    # ip or domain
        _dict[key]["ITEMS"]      = [item]
        _dict[key]["SUBDOMAINS"] = [subdomain]
        _dict[key]["TTLS"]       = [ttl]
        _dict[key]["COUNT"]      = count
        _dict[key]["FIRST_SEEN"] = timestamp
        _dict[key]["LAST_SEEN"]  = timestamp
        return

    if item not in _dict[key]["ITEMS"]:
        _dict[key]["ITEMS"].append(item)
    if subdomain not in _dict[key]["SUBDOMAINS"]:
        _dict[key]["SUBDOMAINS"].append(subdomain)
    if ttl not in _dict[key]["TTLS"]:
        _dict[key]["TTLS"].append(ttl)
    if timestamp < _dict[key]["FIRST_SEEN"]:
        _dict[key]["FIRST_SEEN"] = timestamp
    if timestamp > _dict[key]["LAST_SEEN"]:
        _dict[key]["LAST_SEEN"] = timestamp
    _dict[key]["COUNT"] = _dict[key]["COUNT"] + count

# --------------------------------------------------------------------------------------
def dump_domain_dict(coll, nor_coll, sus_coll, spe_coll,
                     nor_set, sus_set,
                     _dict,
                     cache, nor_cache, sus_cache, spe_cache,
                     nor_ip_set, sus_ip_set):
    '''
    @coll, @nor_coll, @sus_coll, @spe_coll : 四个数据库
    @nor_set, @sus_set: 域名集合
    @_dict: 域名字典，格式参考load_one_line
                                                                                     |
    @nor_set和@sus_set分别是正常和可以域名集合，初始化时创建。字典_dict中是域名的信息|
	，如果域名在可疑集合中，把域名放入@sus_coll数据库中，对应的ip放入@sus_ip_set集合 |
	中。正常域名做类似处理。不在正常域名集合也不在可疑域名集合中的域名，放入@coll。  |
	放入@coll的域名，其中域名对应的IP个数大于30时(对于IP则是对应的域名大于30个)，算作|
	特殊域名，放入@spe_coll
    '''
    for key in _dict:
        if key in sus_set:
            sus_doc = sus_coll.find_one({"_id": key})
            sus_ip_set |= set(_dict[key]["ITEMS"])
            update_nor_sus(key, _dict[key], sus_doc, sus_cache)
        elif key in nor_set:
            nor_doc = nor_coll.find_one({"_id": key})
            nor_ip_set |= set(_dict[key]["ITEMS"])
            update_nor_sus(key, _dict[key], nor_doc, nor_cache)
        else:
            doc = coll.find_one({"_id": key})
            update(_dict[key], doc, key, cache, spe_cache)

    clear_cache(coll, cache)
    clear_cache(nor_coll, nor_cache)
    clear_cache(sus_coll, sus_cache)
    clear_cache(spe_coll, spe_cache)

def dump_ip_dict(coll, nor_coll, sus_coll, spe_coll,
                 nor_set, sus_set,
                 _dict,
                 cache, nor_cache, sus_cache, spe_cache):
    for key in _dict:
        if key in sus_set:
            sus_doc = sus_coll.find_one({"_id": key})
            update_nor_sus(key, _dict[key], sus_doc, sus_cache)
        elif key in nor_set:
            nor_doc = nor_coll.find_one({"_id": key})
            update_nor_sus(key, _dict[key], nor_doc, nor_cache)
        else:
            doc = coll.find_one({"_id": key})
            update(_dict[key], doc, key, cache, spe_cache)

    clear_cache(coll, cache)
    clear_cache(nor_coll, nor_cache)
    clear_cache(sus_coll, sus_cache)
    clear_cache(spe_coll, spe_cache)

def update_nor_sus(key, _dict, doc, nor_sus_cache):
    '''
    @key: 可疑域名或正常域名
    @_dict: 域名信息，参考@load_one_line
    @_doc: 域名在数据库中的信息，可能为None
    @nor_sus_cache: 参考@init_cache
    '''
    if doc is None:
        nor_sus_cache["INSERT"][key] = _dict
        #coll.insert("_id":key, _dict)
    else:
        update_dict = {}

        new_item_list = list(set(_dict["ITEMS"]) - set(doc["ITEMS"]))
        if len(new_item_list) > 0:
            update_dict["$push"] = {}
            update_dict["$push"]["ITEMS"] = {"$each": new_item_list}

        new_subdomain_list = list(set(_dict["SUBDOMAINS"]) - set(doc["SUBDOMAINS"]))
        if len(new_subdomain_list) > 0:
            if "$push" not in update_dict:
                update_dict["$push"] = {}
            update_dict["$push"]["SUBDOMAINS"] = {"$each": new_subdomain_list}

        new_ttl_list = list(set(_dict["TTLS"]) - set(doc["TTLS"]))
        if len(new_ttl_list) > 0:
            if "$push" not in update_dict:
                update_dict["$push"] = {}
            update_dict["$push"]["TTLS"] = {"$each": new_ttl_list}

        update_dict["$set"] = {}
        if _dict["FIRST_SEEN"] < doc["FIRST_SEEN"]:
            update_dict["$set"]["FIRST_SEEN"] = _dict["FIRST_SEEN"]
        if _dict["LAST_SEEN"] > doc["LAST_SEEN"]:
            update_dict["$set"]["LAST_SEEN"] = _dict["LAST_SEEN"]
        update_dict["$set"]["COUNT"] = doc["COUNT"] + _dict["COUNT"]

        nor_sus_cache["UPDATE"][key] = update_dict
        #coll.update({"_id":key}, update_dict)

def update(_dict, doc, key, cache, spe_cache):
    '''
    @key: 除了可疑域名和正常域名的域名
    @_dict: 域名信息，参考@load_one_line
    @_doc: 域名在数据库中的信息，可能为None
    @cache, spe_cache: 参考@init_cache
    '''

    spe_threshold = 30
    if doc is None:
        if len(_dict["ITEMS"]) > spe_threshold:
            spe_cache["INSERT"][key] = _dict
        else:
            cache["INSERT"][key] = _dict
    else:
        update_dict = {}
        di_set = set(_dict["ITEMS"])
        do_set = set(doc["ITEMS"])
        if len(di_set | do_set) > spe_threshold:
            update_dict["ITEMS"]      = list(set(_dict["ITEMS"]) | set(doc["ITEMS"]))
            update_dict["SUBDOMAINS"] = list(set(_dict["SUBDOMAINS"]) | set(doc["SUBDOMAINS"]))
            update_dict["TTLS"]       = list(set(_dict["TTLS"]) | set(doc["TTLS"]))
            update_dict["FIRST_SEEN"] = min(_dict["FIRST_SEEN"], doc["FIRST_SEEN"])
            update_dict["LAST_SEEN"]  = max(_dict["FIRST_SEEN"], doc["FIRST_SEEN"])
            update_dict["COUNT"]      = _dict["COUNT"] + doc["COUNT"]
            update_dict["_id"]        = key
            spe_cache["INSERT"][key]  = update_dict

            cache["DELETE"].add(key)
        else:
            new_item_list = list(di_set - do_set)
            if len(new_item_list) > 0:
                update_dict["$push"] = {}
                update_dict["$push"]["ITEMS"] = {"$each": new_item_list}

            new_subdomain_list = list(set(_dict["SUBDOMAINS"]) - set(doc["SUBDOMAINS"]))
            if len(new_subdomain_list) > 0:
                if "$push" not in update_dict: update_dict["$push"] = {}
                update_dict["$push"]["SUBDOMAINS"] = {"$each": new_subdomain_list}

            new_ttl_list = list(set(_dict["TTLS"]) - set(doc["TTLS"]))
            if len(new_ttl_list) > 0:
                if "$push" not in update_dict:
                    update_dict["$push"] = {}
                update_dict["$push"]["TTLS"] = {"$each": new_ttl_list}

            update_dict["$set"] = {}
            if _dict["FIRST_SEEN"] < doc["FIRST_SEEN"]:
                update_dict["$set"]["FIRST_SEEN"] = _dict["FIRST_SEEN"]
            if _dict["LAST_SEEN"] > doc["LAST_SEEN"]:
                update_dict["$set"]["LAST_SEEN"] = _dict["LAST_SEEN"]
            update_dict["$set"]["COUNT"] = doc["COUNT"] + _dict["COUNT"]

            cache["UPDATE"][key] = update_dict

def init_cache():
    cache = dict()
    cache["UPDATE"] = {}      # 字典中的元素还是字典
    cache["INSERT"] = {}      
    cache["DELETE"] = set([])
    return cache

def clear_cache(coll, cache):
    mongo_print(str(datetime.now()) + " begin clear")

    for item in cache["INSERT"]:
        coll.insert(cache["INSERT"][item])
    mongo_print(str(datetime.now()) + " " + str(len(cache["INSERT"])) + " inserted")
    cache["INSERT"].clear()

    for item in cache["UPDATE"]:
        coll.update({"_id": item}, cache["UPDATE"][item])
    mongo_print(str(datetime.now()) + " " + str(len(cache["UPDATE"])) + " updated")
    cache["UPDATE"].clear()

    for item in cache["DELETE"]:
        coll.remove({"_id": item})
    mongo_print(str(datetime.now()) + " " + str(len(cache["DELETE"])) + " deleted")
    cache["DELETE"].clear()


script, start_date_str, day_gap = argv
domains_path   = "F:\\mygit\\data\\ffd\\domains"
dns_log_path   = "F:\\mygit\\data\\ffd\\dnslog"
p              = re.compile("^\d{4}\-\d{2}\-\d{2}$")
start_datetime = datetime.strptime(start_date_str, "%y%m%d")
end_datetime   = start_datetime + timedelta(days=int(day_gap))
client         = MongoClient()
db             = client["p" + start_date_str] # 数据库的名字，例如 p140101

ip_dict     = {}
domain_dict = {}      # 日志信息简单汇总后，先放入这个字典再写入数据库
sus_ip_set  = set([])
nor_ip_set  = set([])

outlier_domain_set = init_outlier_domain_set()
nor_domain_set     = init_from_alexa(10000, 15000)
sus_domain_set     = init_sus_domain_set()

domain_cache     = init_cache()
ip_cache         = init_cache()
sus_domain_cache = init_cache()
sus_ip_cache     = init_cache()
nor_domain_cache = init_cache()
nor_ip_cache     = init_cache()
spe_domain_cache = init_cache()
spe_ip_cache     = init_cache()

mongo_print("\n\n\n\n\n" + str(os.path.basename(__file__)))

file_list = []
for root, dirs, files in os.walk(dns_log_path):
    files.sort()
    for f in files:
        if not p.match(f):
            continue
        this_date = datetime.strptime(f, "%Y-%m-%d").date()
        if start_datetime.date() <= this_date < end_datetime.date():
            file_list.append(f)

print file_list # 要处理的文件，如 [2014-01-01,2014-01-02]

for f in file_list:
    mongo_print(f)
    mongo_print(datetime.now())

    bar1 = time.clock()
    number = 0

    for line in open(os.path.join(dns_log_path, f)):
        number += 1
        line_array = line.split("||")

        if len(line_array) != 9 or line_array[5] != 'A':
            continue

        domain = (line_array[4][:len(line_array[4]) - 1]).lower()
        ext = tldextract.extract(domain)
        subdomain = ext.subdomain
        if ext.domain == "":
            domain = ext.suffix
        else:
            domain = ".".join(ext[1:])

        if domain in outlier_domain_set:
            continue
        if domain in nor_domain_set and domain in sus_domain_set:
            continue
        # if domain not in sus_domain_set and domain not in nor_domain_set:
        #     continue

        timestamp = float(line_array[0])
        ip        = line_array[6]
        ttl       = int(line_array[7])
        count     = int(line_array[8])

        load_one_line(domain_dict, timestamp, subdomain, domain, ip, ttl, count)
        load_one_line(ip_dict, timestamp, subdomain, ip, domain, ttl, count)

    mongo_print([len(domain_dict), len(ip_dict), number])
    mongo_print((time.clock() - bar1) / number)
    mongo_print(datetime.now())

    bar2 = time.clock()
    dump_domain_dict(db.domain, db.nor_domain, db.sus_domain, db.spe_domain,
                     nor_domain_set, sus_domain_set,
                     domain_dict,
                     domain_cache, nor_domain_cache, sus_domain_cache, spe_domain_cache,
                     nor_ip_set, sus_ip_set)
    mongo_print((time.clock() - bar2) / len(domain_dict))
    mongo_print(datetime.now())
    domain_dict.clear()

    print len(nor_ip_set)
    print len(sus_ip_set)

    bar3 = time.clock()
    dump_ip_dict(db.ip, db.nor_ip, db.sus_ip, db.spe_ip,
                 nor_ip_set, sus_ip_set,
                 ip_dict,
                 ip_cache, nor_ip_cache, sus_ip_cache, spe_ip_cache)
    mongo_print((time.clock() - bar3) / len(ip_dict))
    mongo_print(str(datetime.now()) + "\n")
    ip_dict.clear()


'''
使用方法
 python log_to_mongo.py 140101 1
 140101: 处理文件2014-01-01
 1     ：处理1天的数据，也就是2014-01-01

 python log_to_mongo.py 140108 2
 140108: 处理文件2014-01-08
 2     ：处理2天的数据，也就是2014-01-08、2014-01-07

 crteat file: xxx/resources/cdn_new.txt

日志入库
  1 outlier不入库
  2 同时是正常和可疑的域名不入库

数据库
 coll_name_list = ['domain', 'nor_domain', 'sus_domain', 'spe_domain', 'ip', 'nor_ip', 'sus_ip', 'spe_ip']
 nor_domain: 正常域名alexa排名在10000到15000之间的域名
 sus_domain: 恶意域名
 spe_domain: 特殊域名，相关IP个数大于30，且不是正常域名，不是恶意域名
 domain    : 上述三种域名之外的域名
 




2015-11-29 17:36:50.220000 begin clear
Traceback (most recent call last):
  File "log_to_mongo.py", line 98, in <module>
    nor_ip_set, sus_ip_set)
  File "G:\xdata_osrc\FluxEnder\src\log_to_mongo_lib.py", line 113, in dump_domain_dict
    clear_cache(spe_coll, spe_cache)
  File "G:\xdata_osrc\FluxEnder\src\log_to_mongo_lib.py", line 232, in clear_cache
    coll.insert(cache["INSERT"][item])
  File "C:\Python27\lib\site-packages\pymongo\collection.py", line 1926, in insert
    check_keys, manipulate, write_concern)
  File "C:\Python27\lib\site-packages\pymongo\collection.py", line 431, in _insert
    _check_write_command_response(results)
  File "C:\Python27\lib\site-packages\pymongo\helpers.py", line 260, in _check_write_command_response
    raise DuplicateKeyError(error.get("errmsg"), 11000, error)
pymongo.errors.DuplicateKeyError: E11000 duplicate key error index: p140101.spe_domain.$_id_ dup key: { : "jhu.edu" }

G:\xdata_osrc\FluxEnder\src>
'''