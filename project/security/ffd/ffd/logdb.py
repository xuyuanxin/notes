#coding=utf-8

import logging
import time

import tldextract
from pymongo import MongoClient

def updata_db(dbclient, dbname, collname, data_cache):	
    for key in data_cache: # key is domain or ip
        data = data_cache[key]	
        coll = dbclient[dbname][collname]
        doc  = coll.find_one({"KEY": key})

        if None == doc:
            coll.replace_one(data, data, upsert=True)
        else:
            doc_ips = set(doc["ITEMS"])
            doc_ips |= set(data["ITEMS"])
            data["ITEMS"] = list(doc_ips) 
			
            doc_sd = set(doc["SUBDOMAINS"])
            doc_sd |= set(data["SUBDOMAINS"])
            data["SUBDOMAINS"] = list(doc_sd) 

            doc_ttl = set(doc["TTLS"])
            doc_ttl |= set(data["TTLS"])
            data["TTLS"] = list(doc_ttl)

            if doc["FIRST_SEEN"] < data["FIRST_SEEN"]:
                data["FIRST_SEEN"] = doc["FIRST_SEEN"]

            if doc["LAST_SEEN"] > data["LAST_SEEN"]:
                data["LAST_SEEN"] = doc["LAST_SEEN"]

            data["COUNT"] = data["COUNT"] + doc["COUNT"]         
            
            coll.replace_one({'KEY': key}, data)

def dcache(f, type, condition=None, domains=None):
    '''
    @f: log file name(with full path)
    @type: domain or ip
    @condition: 域名集合
    @domains: domains类， 训练时使用
	
    list: 200s
    set : 47s, but mongodb not support
	
    从数据文件中读取信息，在内存中建立数据结构
    '''

    logger  = logging.getLogger("ffd")
    d_cache = dict()
    number  = 0
    ticks   = time.time()

    outlier_set       = set()
    conflit_set       = set()
    outlier_cnt       = 0
    train_conflit_cnt = 0

    for line in open(f):
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

        #if domain in outlier_domain_set:
        #    continue
        #if domain in nor_domain_set and domain in sus_domain_set:
        #    continue
        # if domain not in sus_domain_set and domain not in nor_domain_set:
        #     continue

        timestamp = float(line_array[0])
        ip        = line_array[6]
        ttl       = int(line_array[7])
        count     = int(line_array[8])
		
        if 'domain' == type:
            key = domain
            items = ip
        elif 'ip' == type:
            key = ip
            items = domain
        else:
            logger.error("logdb.dcache, type is not support")
            return None

        if None != domains:
            if domain in domains.outlier:
                outlier_cnt += 1
                outlier_set.add(domain)
                continue
            if domain in domains.train_w and domain in domains.malware:
                conflit_set.add(domain)
                train_conflit_cnt += 1
                continue

        if None!=condition and key not in condition:
            continue

        if key not in d_cache:
            d_cache[key]               = {}
            d_cache[key]["KEY"]        = key    # ip or domain
            d_cache[key]["ITEMS"]      = set([items])
            d_cache[key]["SUBDOMAINS"] = set([subdomain])
            d_cache[key]["TTLS"]       = set([ttl])
            #d_cache[key]["ITEMS"]      = [items]
            #d_cache[key]["SUBDOMAINS"] = [subdomain]
            #d_cache[key]["TTLS"]       = [ttl]
            d_cache[key]["COUNT"]      = count
            d_cache[key]["FIRST_SEEN"] = timestamp
            d_cache[key]["LAST_SEEN"]  = timestamp
        else:
            if items not in d_cache[key]["ITEMS"]:
                #d_cache[key]["ITEMS"].append(items)
                d_cache[key]["ITEMS"].add(items)

            if subdomain not in d_cache[key]["SUBDOMAINS"]:
                d_cache[key]["SUBDOMAINS"].add(subdomain)

            if ttl not in d_cache[key]["TTLS"]:
                d_cache[key]["TTLS"].add(ttl)

            if timestamp < d_cache[key]["FIRST_SEEN"]:
                d_cache[key]["FIRST_SEEN"] = timestamp

            if timestamp > d_cache[key]["LAST_SEEN"]:
                d_cache[key]["LAST_SEEN"] = timestamp

            d_cache[key]["COUNT"] = d_cache[key]["COUNT"] + count

    logger.info("logdb.dcache, pre filter, outlier: %d(%d), train confilt: %d(%d)."%\
	           (len(outlier_set),outlier_cnt,len(conflit_set),train_conflit_cnt))
    logger.info("logdb.dcache, data line: %d, %s: %d."%(number,type,len(d_cache)))
    logger.info("logdb.dcache, build %s cache, eclipse: %f s"%(type, time.time() - ticks))

    return d_cache
			
def log_db(f, dbname, cnt=3000000):
    '''
    @f: log file name(with full path)
    @dbname: data base name
    '''

    logger = logging.getLogger("ffd")
    domain_cache = dcache(f,'domain')
    for key in domain_cache:
        domain_cache[key]["ITEMS"]      = list(domain_cache[key]["ITEMS"])
        domain_cache[key]["SUBDOMAINS"] = list(domain_cache[key]["SUBDOMAINS"])
        domain_cache[key]["TTLS"]       = list(domain_cache[key]["TTLS"])
			
    coll = dbname['domains']

    ticks = time.time()
    result = coll.insert_many(domain_cache.values(),ordered=False)
    logger.info("logdb.log_db, insert db, eclipse: %f s"%(time.time() - ticks))

    logger.info("logdb.log_db, insert nums: %d"%(len(result.inserted_ids)))    

def coll_clean(dbclient, dbname, collname):
    dbclient[dbname][collname].drop()

#def db_clean(dbclient, dbname):
#    dbclient[dbname].drop()


def get_keys(dcache, condition=None):
    '''
    @dcache: 
    @condition: 域名或者IP集合
	
    从缓存中提取域名或IP
    '''

    dset   = set([])
    logger = logging.getLogger("ffd")
    ticks  = time.time()

    for key in dcache:
        if None == condition:
            dset.add(key)
        else:
            if key in condition:
                dset.add(key)

    #logger.info("get keys, eclipse: %fs."%(time.time() - ticks))

    return dset		
		
def get_rip(dcache, condition=None):
    '''
    @dcache: key is domains
    @condition: 域名集合
	
    从缓存中提取相关IP
    '''

    dset   = set([])
    logger = logging.getLogger("ffd")
    ticks  = time.time()

    for key in dcache:
        ips = dcache[key]["ITEMS"]
        if None == condition:
            dset.update(ips)
        else:
            if key in condition:
                dset.update(ips)

    #logger.info("get keys, eclipse: %fs."%(time.time() - ticks))

    return dset			
		
def get_rd(dcache, condition=None):
    '''
    @dcache: key is domains
    @condition: IP集合
	
    从缓存中提取IP的相关域名
    '''

    dset   = set([])
    logger = logging.getLogger("ffd")
    ticks  = time.time()
    rd_cnt = 0

    for key in dcache:
        ips = dcache[key]["ITEMS"]
        if None == condition:
            dset.add(key)
        else:
            if len(ips.intersection(condition)) > 0:
                rd_cnt += 1
                dset.add(key)

    logger.info("logdb.get_rd, get rd %d, eclipse: %fs."%(rd_cnt,time.time() - ticks))

    return dset		


	
if __name__ == '__main__':
    datafile = "F:\\mygit\\data\\ffd\\dnslog\\test\\2014-01-08"
    mclient = MongoClient()
    db = mclient.dbtest01

    coll_clean(mclient,'dbtest01','colltest01')

    coll = db.colltest01
	
    domain = 'aaa.com'
    domain_cache = {}
    domain_cache[domain]               = {}
    domain_cache[domain]["KEY"]        = domain    # ip or domain
    domain_cache[domain]["ITEMS"]      = ['1.1.1.1']
    domain_cache[domain]["SUBDOMAINS"] = ['sd1']
    domain_cache[domain]["TTLS"]       = [200]
    domain_cache[domain]["COUNT"]      = 1
    domain_cache[domain]["FIRST_SEEN"] = 100
    domain_cache[domain]["LAST_SEEN"]  = 100
	
    doc  = coll.find_one({"KEY": domain})
    if None != doc:
        print("type doc: %s, doc: %s"%(type(doc),doc))
        print("type doc[ITEMS]: %s, %s"%(type(doc["ITEMS"]),doc["ITEMS"]))
    else:
        print("doc is None")
	
    coll.replace_one(domain_cache[domain], domain_cache[domain], upsert=True)
    print(domain_cache)

    log_db(datafile, mclient, '20140101')
