#coding=utf-8

import collections
import math
import logging
import time

import tldextract


def entropy(s):
    p, lns = collections.Counter(s), float(len(s))
    if lns <= 1:
        return 0
    return sum(- count/lns * math.log(count/lns, 2) for count in p.values())/(math.log(lns, 2))

def net_prefix16(ip):
    tmp_array = ip.split(".")
    return tmp_array[0] + "." + tmp_array[1]

def net_div(ips):
    prefix16_list = [net_prefix16(x) for x in ips]
    return round(entropy(prefix16_list), 5)
	
def base_features(dinfo,istrain=True):
    '''
    @dinfo: 读取数据文件，建立的内存数据结构(字典)
	
    获取基本特征信息(ip ttl)，用于预处理。
    '''

    logger = logging.getLogger("ffd")
    ticks  = time.time()
    fcache = dict()

    for key in dinfo:
        fcache[key] = {}
        ips = dinfo[key]['ITEMS']
        ttls = dinfo[key]['TTLS']
        fcache[key]['ip_nums'] = round(float(len(ips)),5)
        if(istrain):
            fcache[key]['net_div'] = net_div(ips)
        else:
            prefix16 = [net_prefix16(x) for x in ips]
            fcache[key]['net_div'] = round(float(len(set(prefix16)))/len(ips),5)
        fcache[key]['min_ttl'] = round(min(ttls),5)
		
    logger.info("get base features, eclipse: %f s"%(time.time() - ticks))

    return fcache
	
def malware_to_botnet(finfo,botnet,malware,params):
    dset = set()
    for key in finfo:
        ip_nums = finfo[key]['ip_nums']
        net_div = finfo[key]['net_div']
        min_ttl = finfo[key]['min_ttl']
        
        if key not in botnet and key in malware:
            if ip_nums > params[0] and net_div > params[1] and min_ttl < params[2]:
                dset.add(key)

    return dset
	
def train_preproc(finfo,domains,params):
    dset   = set()
    logger = logging.getLogger("ffd")
    ticks  = time.time()	
    outlier_cnt   = 0
    conflict_cnt  = 0
    filter_by_f   = 0
    not_train_cnt = 0

    for key in finfo:
        if key in domains.outlier:
            outlier_cnt += 1
            continue

        if key in domains.train_w or key in domains.malware:
            if key in domains.train_w and key in domains.malware:
                conflict_cnt += 1
                continue

            if key in domains.botnet_e or key in domains.train_w:
                dset.add(key)
                continue

            ip_nums = finfo[key]['ip_nums']
            net_div = finfo[key]['net_div']
            min_ttl = finfo[key]['min_ttl']

            if key not in domains.botnet_e and key in domains.malware:
                if ip_nums > params[0] and net_div > params[1] and min_ttl < params[2]:
                    dset.add(key)
                    domains.mal2bot.add(key)
                else:
                    filter_by_f += 1
        else:
            not_train_cnt += 1

    logger.info("train filter, outerlier: %d, conflit: %d, not botnet: %d, not train: %d "%\
	           (outlier_cnt, conflict_cnt, filter_by_f,not_train_cnt))
    logger.info("train pre process, eclipse: %f s"%(time.time() - ticks))

    return dset	

def detect_preproc(finfo,domains,params):
    '''
    @finfo: feature info
    @domains: Domain class
    @params: 
    '''

    dset   = set()
    logger = logging.getLogger("ffd")
    ticks  = time.time()	
    filter_by_w = 0
    filter_by_f = 0

    for key in finfo:
        if key in domains.white:
            filter_by_w += 1
            continue
        
        ip_nums = finfo[key]['ip_nums']
        net_div = finfo[key]['net_div']
        min_ttl = finfo[key]['min_ttl']

        if ip_nums > params[0] and net_div > params[1] and min_ttl < params[2]:
            dset.add(key)
        else:
            filter_by_f += 1

    logger.info("detect, pass by white: %d, pass by f: %d"%(filter_by_w, filter_by_f))
    logger.info("detect pre process, eclipse: %f s"%(time.time() - ticks))

    return dset


