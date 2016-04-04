#coding=utf-8

import os
import ConfigParser
import logging
import time
import argparse

import tldextract
from pymongo import MongoClient

#from .domains import Domains
import domains
import logdb
import feature

if __name__ == '__main__':
    parser = argparse.ArgumentParser()
    parser.add_argument("-d","--data", type=str, help="the start date, e.g. 2014/12/20/23")
    parser.add_argument("-f", "--force", action="store_true", help="force run")
    parser.add_argument("-v", "--verbose", action="store_true", help="verbose info")
    args = parser.parse_args()
    print(args)
	
    ticksbeg  = time.time()
    cfger = ConfigParser.SafeConfigParser()
    cfger.read('ffd.conf')

    tlow  = cfger.getint('train', 'alexa_low')
    thigh = cfger.getint('train', 'alexa_high')
    dlow  = cfger.getint('detect', 'alexa_low')
    dhigh = cfger.getint('detect', 'alexa_high')
    domain_path = cfger.get('dpath','domains_path')
    data_path = cfger.get('dpath','data_path')
    rlog  = cfger.get('dpath','run_log')
    
    logger = logging.getLogger("ffd")
    logging.basicConfig(level=logging.INFO,
                        format=' %(asctime)s %(filename)s[line:%(lineno)d] %(levelname)s %(message)s',
                        datefmt='%a, %d %b %Y %H:%M:%S',
                        filename=os.path.join(rlog, 'run.log'),
                        filemode='a')

    console = logging.StreamHandler()
    console.setLevel(logging.INFO)
    formatter = logging.Formatter(' %(name)-8s: %(levelname)-8s %(message)s')
    console.setFormatter(formatter)
    logger.addHandler(console)

    logger.info("------------------------------------------------------------")
    logger.info("main, domain path   : %s "%(domain_path))
    logger.info("main, data path     : %s "%(data_path))
    logger.info("main, run log path  : %s "%(data_path))
    logger.info("main, tlow,thigh: %d, %d; dlow,dhigh: %d, %d "%(tlow,thigh,dlow,dhigh))

    data_file = os.path.join(data_path, '2014-01-08')

    d = domains.Domains(domain_path,tlow,thigh,dlow,dhigh)
    d.load_all()

    all_domain_info  = logdb.dcache(data_file,'domain',domains=d)

    domain_all       = logdb.get_keys(all_domain_info)
    domain_train_all = logdb.get_keys(all_domain_info,d.malware|d.train_w)
    relative_ips     = logdb.get_rip(all_domain_info,domain_train_all)
    domain_train_r   = logdb.get_rd(all_domain_info,relative_ips)
	
    logger.info("main, relative ips : %d"%(len(relative_ips)))

    d.stat(domain_all,'all domains')
    d.stat(domain_train_all,'train domains before pre process')
    d.stat(domain_train_r,'relative domains of train domain(before preproc)')

    train_feature_base  = feature.base_features(all_domain_info)
    params = [cfger.getfloat('train', 'ip_nums'), cfger.getfloat('train', 'net_div'), \
	          cfger.getfloat('train', 'min_ttl')]
    train_domains = feature.train_preproc(train_feature_base, d, params)
    d.stat(train_domains,'train domains after pre process')
	
    detect_domain_info  = all_domain_info
    detect_feature_base = feature.base_features(detect_domain_info,istrain=False)
    params = [cfger.getfloat('detect', 'ip_nums'), cfger.getfloat('detect', 'net_div'), \
	          cfger.getfloat('detect', 'min_ttl')]
    detect_domains = feature.detect_preproc(detect_feature_base, d, params)	
    d.stat(detect_domains,'detect domains after pre process')
	
    logger.info("main, total eclipse: %fs"%(time.time() - ticksbeg))
    exit(0)

    mclient = MongoClient()

    logdb.coll_clean(mclient,'20140108','domains')
	
    logdb.log_db(data_file, mclient['20140108'])

'''
[global]
default.alias = dev

[dev.alias]
url = http://dev.namenode:port
user = ann

[prod.alias]
url = http://prod.namenode:port
root = /jobs/


--> all (prefilter)
 Mon, 15 Feb 2016 22:12:32 ffd_main.py[line:42] INFO ------------------------------------------------------------
 Mon, 15 Feb 2016 22:12:32 ffd_main.py[line:43] INFO main, domain path   : F:\\mygit\\data\\ffd\\domains\\2014 
 Mon, 15 Feb 2016 22:12:32 ffd_main.py[line:44] INFO main, data path     : F:\\mygit\\data\\ffd\\dnslog 
 Mon, 15 Feb 2016 22:12:32 ffd_main.py[line:45] INFO main, run log path  : F:\\mygit\\data\\ffd\\dnslog 
 Mon, 15 Feb 2016 22:12:32 ffd_main.py[line:46] INFO main, tlow,thigh: 10000, 15000; dlow,dhigh: 0, 10000 
 Mon, 15 Feb 2016 22:12:39 domains.py[line:89] INFO domains._info, domains load from data files: 
 Mon, 15 Feb 2016 22:12:39 domains.py[line:90] INFO   botnet_r : 172
 Mon, 15 Feb 2016 22:12:39 domains.py[line:91] INFO   botnet_e : 3181
 Mon, 15 Feb 2016 22:12:39 domains.py[line:92] INFO    malware : 123180
 Mon, 15 Feb 2016 22:12:39 domains.py[line:93] INFO    mal2bot : 0
 Mon, 15 Feb 2016 22:12:39 domains.py[line:94] INFO      white : 10000
 Mon, 15 Feb 2016 22:12:39 domains.py[line:95] INFO    outlier : 68
 Mon, 15 Feb 2016 22:12:39 domains.py[line:96] INFO    train_w : 5001
 Mon, 15 Feb 2016 22:12:39 domains.py[line:97] INFO    train_b : 0
 Mon, 15 Feb 2016 22:12:39 domains.py[line:109] INFO domains.load_all, load domains, eclipse: 7.188000 s
 Mon, 15 Feb 2016 22:13:29 logdb.py[line:145] INFO logdb.dcache, pre filter, outlier: 39(83972), train confilt: 153(3613).
 Mon, 15 Feb 2016 22:13:29 logdb.py[line:146] INFO logdb.dcache, data line: 3457537, domain: 256512.
 Mon, 15 Feb 2016 22:13:29 logdb.py[line:147] INFO logdb.dcache, build domain cache, eclipse: 50.193000 s
 Mon, 15 Feb 2016 22:13:30 logdb.py[line:248] INFO logdb.get_rd, get rd 18400, eclipse: 0.315000s.
 Mon, 15 Feb 2016 22:13:30 ffd_main.py[line:60] INFO main, relative ips : 74951
 Mon, 15 Feb 2016 22:13:30 domains.py[line:162] INFO domains.stat, all domains total 256512
 Mon, 15 Feb 2016 22:13:30 domains.py[line:163] INFO        botnet_r : 7
 Mon, 15 Feb 2016 22:13:30 domains.py[line:164] INFO        botnet_e : 71
 Mon, 15 Feb 2016 22:13:30 domains.py[line:165] INFO         malware : 3587
 Mon, 15 Feb 2016 22:13:30 domains.py[line:166] INFO         mal2bot : 0(0)
 Mon, 15 Feb 2016 22:13:30 domains.py[line:167] INFO           white : 5610
 Mon, 15 Feb 2016 22:13:30 domains.py[line:168] INFO         outlier : 0
 Mon, 15 Feb 2016 22:13:30 domains.py[line:169] INFO         train_w : 1794
 Mon, 15 Feb 2016 22:13:30 domains.py[line:170] INFO         train_b : 0
 Mon, 15 Feb 2016 22:13:30 domains.py[line:172] INFO     tw&botnet_r : 0
 Mon, 15 Feb 2016 22:13:30 domains.py[line:173] INFO     tw&botnet_e : 0
 Mon, 15 Feb 2016 22:13:30 domains.py[line:174] INFO      tw&malware : 0
 Mon, 15 Feb 2016 22:13:30 domains.py[line:175] INFO      w&botnet_r : 3
 Mon, 15 Feb 2016 22:13:30 domains.py[line:176] INFO      w&botnet_e : 9
 Mon, 15 Feb 2016 22:13:30 domains.py[line:177] INFO       w&malware : 885
 Mon, 15 Feb 2016 22:13:30 domains.py[line:179] INFO domains.stat, stat all domains, eclipse: 0.311000s.
 Mon, 15 Feb 2016 22:13:30 domains.py[line:162] INFO domains.stat, train domains before pre process total 5381
 Mon, 15 Feb 2016 22:13:30 domains.py[line:163] INFO        botnet_r : 7
 Mon, 15 Feb 2016 22:13:30 domains.py[line:164] INFO        botnet_e : 71
 Mon, 15 Feb 2016 22:13:30 domains.py[line:165] INFO         malware : 3587
 Mon, 15 Feb 2016 22:13:30 domains.py[line:166] INFO         mal2bot : 0(0)
 Mon, 15 Feb 2016 22:13:30 domains.py[line:167] INFO           white : 886
 Mon, 15 Feb 2016 22:13:30 domains.py[line:168] INFO         outlier : 0
 Mon, 15 Feb 2016 22:13:30 domains.py[line:169] INFO         train_w : 1794
 Mon, 15 Feb 2016 22:13:30 domains.py[line:170] INFO         train_b : 0
 Mon, 15 Feb 2016 22:13:30 domains.py[line:172] INFO     tw&botnet_r : 0
 Mon, 15 Feb 2016 22:13:30 domains.py[line:173] INFO     tw&botnet_e : 0
 Mon, 15 Feb 2016 22:13:30 domains.py[line:174] INFO      tw&malware : 0
 Mon, 15 Feb 2016 22:13:30 domains.py[line:175] INFO      w&botnet_r : 3
 Mon, 15 Feb 2016 22:13:30 domains.py[line:176] INFO      w&botnet_e : 9
 Mon, 15 Feb 2016 22:13:30 domains.py[line:177] INFO       w&malware : 885
 Mon, 15 Feb 2016 22:13:30 domains.py[line:179] INFO domains.stat, stat train domains before pre process, eclipse: 0.019000s.
 Mon, 15 Feb 2016 22:13:30 domains.py[line:162] INFO domains.stat, relative domains of train domain(before preproc) total 18400
 Mon, 15 Feb 2016 22:13:30 domains.py[line:163] INFO        botnet_r : 7
 Mon, 15 Feb 2016 22:13:30 domains.py[line:164] INFO        botnet_e : 71
 Mon, 15 Feb 2016 22:13:30 domains.py[line:165] INFO         malware : 3587
 Mon, 15 Feb 2016 22:13:30 domains.py[line:166] INFO         mal2bot : 0(0)
 Mon, 15 Feb 2016 22:13:30 domains.py[line:167] INFO           white : 1545
 Mon, 15 Feb 2016 22:13:30 domains.py[line:168] INFO         outlier : 0
 Mon, 15 Feb 2016 22:13:30 domains.py[line:169] INFO         train_w : 1794
 Mon, 15 Feb 2016 22:13:30 domains.py[line:170] INFO         train_b : 0
 Mon, 15 Feb 2016 22:13:30 domains.py[line:172] INFO     tw&botnet_r : 0
 Mon, 15 Feb 2016 22:13:30 domains.py[line:173] INFO     tw&botnet_e : 0
 Mon, 15 Feb 2016 22:13:30 domains.py[line:174] INFO      tw&malware : 0
 Mon, 15 Feb 2016 22:13:30 domains.py[line:175] INFO      w&botnet_r : 3
 Mon, 15 Feb 2016 22:13:30 domains.py[line:176] INFO      w&botnet_e : 9
 Mon, 15 Feb 2016 22:13:30 domains.py[line:177] INFO       w&malware : 885
 Mon, 15 Feb 2016 22:13:30 domains.py[line:179] INFO domains.stat, stat relative domains of train domain(before preproc), eclipse: 0.037000s.
 Mon, 15 Feb 2016 22:13:33 feature.py[line:48] INFO feature.base_features, get base features, eclipse: 2.878000 s
 Mon, 15 Feb 2016 22:13:33 feature.py[line:102] INFO feature.train_preproc, train filter, outerlier: 0, conflit: 0, not botnet: 3207, not train: 251131 
 Mon, 15 Feb 2016 22:13:33 feature.py[line:103] INFO feature.train_preproc, train pre process, eclipse: 0.131000 s
 Mon, 15 Feb 2016 22:13:33 domains.py[line:162] INFO domains.stat, train domains after pre process total 2174
 Mon, 15 Feb 2016 22:13:33 domains.py[line:163] INFO        botnet_r : 7
 Mon, 15 Feb 2016 22:13:33 domains.py[line:164] INFO        botnet_e : 71
 Mon, 15 Feb 2016 22:13:33 domains.py[line:165] INFO         malware : 380
 Mon, 15 Feb 2016 22:13:33 domains.py[line:166] INFO         mal2bot : 309(309)
 Mon, 15 Feb 2016 22:13:33 domains.py[line:167] INFO           white : 185
 Mon, 15 Feb 2016 22:13:33 domains.py[line:168] INFO         outlier : 0
 Mon, 15 Feb 2016 22:13:33 domains.py[line:169] INFO         train_w : 1794
 Mon, 15 Feb 2016 22:13:33 domains.py[line:170] INFO         train_b : 0
 Mon, 15 Feb 2016 22:13:33 domains.py[line:172] INFO     tw&botnet_r : 0
 Mon, 15 Feb 2016 22:13:33 domains.py[line:173] INFO     tw&botnet_e : 0
 Mon, 15 Feb 2016 22:13:33 domains.py[line:174] INFO      tw&malware : 0
 Mon, 15 Feb 2016 22:13:33 domains.py[line:175] INFO      w&botnet_r : 3
 Mon, 15 Feb 2016 22:13:33 domains.py[line:176] INFO      w&botnet_e : 9
 Mon, 15 Feb 2016 22:13:33 domains.py[line:177] INFO       w&malware : 184
 Mon, 15 Feb 2016 22:13:33 domains.py[line:179] INFO domains.stat, stat train domains after pre process, eclipse: 0.012000s.
 Mon, 15 Feb 2016 22:13:35 feature.py[line:48] INFO feature.base_features, get base features, eclipse: 1.532000 s
 Mon, 15 Feb 2016 22:13:35 feature.py[line:134] INFO feature.detect_preproc, detect, pass by white: 5610, pass by f: 233163
 Mon, 15 Feb 2016 22:13:35 feature.py[line:135] INFO feature.detect_preproc, detect pre process, eclipse: 0.197000 s
 Mon, 15 Feb 2016 22:13:35 domains.py[line:162] INFO domains.stat, detect domains after pre process total 17739
 Mon, 15 Feb 2016 22:13:35 domains.py[line:163] INFO        botnet_r : 3
 Mon, 15 Feb 2016 22:13:35 domains.py[line:164] INFO        botnet_e : 17
 Mon, 15 Feb 2016 22:13:35 domains.py[line:165] INFO         malware : 656
 Mon, 15 Feb 2016 22:13:35 domains.py[line:166] INFO         mal2bot : 127(309)
 Mon, 15 Feb 2016 22:13:35 domains.py[line:167] INFO           white : 0
 Mon, 15 Feb 2016 22:13:35 domains.py[line:168] INFO         outlier : 0
 Mon, 15 Feb 2016 22:13:35 domains.py[line:169] INFO         train_w : 496
 Mon, 15 Feb 2016 22:13:35 domains.py[line:170] INFO         train_b : 0
 Mon, 15 Feb 2016 22:13:35 domains.py[line:172] INFO     tw&botnet_r : 0
 Mon, 15 Feb 2016 22:13:35 domains.py[line:173] INFO     tw&botnet_e : 0
 Mon, 15 Feb 2016 22:13:35 domains.py[line:174] INFO      tw&malware : 0
 Mon, 15 Feb 2016 22:13:35 domains.py[line:175] INFO      w&botnet_r : 0
 Mon, 15 Feb 2016 22:13:35 domains.py[line:176] INFO      w&botnet_e : 0
 Mon, 15 Feb 2016 22:13:35 domains.py[line:177] INFO       w&malware : 0
 Mon, 15 Feb 2016 22:13:35 domains.py[line:179] INFO domains.stat, stat detect domains after pre process, eclipse: 0.038000s.
 Mon, 15 Feb 2016 22:13:35 ffd_main.py[line:79] INFO main, total eclipse: 63.234000s

--> all(not prefilter)
 Sat, 13 Feb 2016 22:21:55 ffd_main.py[line:42] INFO ------------------------------------------------------------
 Sat, 13 Feb 2016 22:21:55 ffd_main.py[line:43] INFO domain path   : F:\\mygit\\data\\ffd\\domains\\2014 
 Sat, 13 Feb 2016 22:21:55 ffd_main.py[line:44] INFO data path     : F:\\mygit\\data\\ffd\\dnslog 
 Sat, 13 Feb 2016 22:21:55 ffd_main.py[line:45] INFO run log path  : F:\\mygit\\data\\ffd\\dnslog 
 Sat, 13 Feb 2016 22:21:55 ffd_main.py[line:46] INFO tlow,thigh,dlow,dhigh: 10000,15000,0,10000 
 Sat, 13 Feb 2016 22:22:02 domains.py[line:94] INFO load domains, eclipse: 7.031000 s
 Sat, 13 Feb 2016 22:22:02 domains.py[line:98] INFO domains predefine
 Sat, 13 Feb 2016 22:22:02 domains.py[line:99] INFO   botnet_r : 172
 Sat, 13 Feb 2016 22:22:02 domains.py[line:100] INFO   botnet_e : 3181
 Sat, 13 Feb 2016 22:22:02 domains.py[line:101] INFO    malware : 123180
 Sat, 13 Feb 2016 22:22:02 domains.py[line:102] INFO    mal2bot : 0
 Sat, 13 Feb 2016 22:22:02 domains.py[line:103] INFO      white : 10000
 Sat, 13 Feb 2016 22:22:02 domains.py[line:104] INFO    outlier : 68
 Sat, 13 Feb 2016 22:22:02 domains.py[line:105] INFO    train_w : 5001
 Sat, 13 Feb 2016 22:22:02 domains.py[line:106] INFO    train_b : 0
 Sat, 13 Feb 2016 22:22:47 logdb.py[line:128] INFO data line: 3457537, domain: 256704.
 Sat, 13 Feb 2016 22:22:47 logdb.py[line:129] INFO build domain cache, eclipse: 44.825000 s
 Sat, 13 Feb 2016 22:22:47 logdb.py[line:230] INFO get rd 18685, eclipse: 0.285000s.
 Sat, 13 Feb 2016 22:22:47 ffd_main.py[line:61] INFO relative ips : 79670
 Sat, 13 Feb 2016 22:22:48 domains.py[line:159] INFO all domains : 256704
 Sat, 13 Feb 2016 22:22:48 domains.py[line:160] INFO        botnet_r : 8
 Sat, 13 Feb 2016 22:22:48 domains.py[line:161] INFO        botnet_e : 75
 Sat, 13 Feb 2016 22:22:48 domains.py[line:162] INFO         malware : 3748
 Sat, 13 Feb 2016 22:22:48 domains.py[line:163] INFO         mal2bot : 0(0)
 Sat, 13 Feb 2016 22:22:48 domains.py[line:164] INFO           white : 5620
 Sat, 13 Feb 2016 22:22:48 domains.py[line:165] INFO         outlier : 39
 Sat, 13 Feb 2016 22:22:48 domains.py[line:166] INFO         train_w : 1948
 Sat, 13 Feb 2016 22:22:48 domains.py[line:167] INFO         train_b : 0
 Sat, 13 Feb 2016 22:22:48 domains.py[line:169] INFO     tw&botnet_r : 1
 Sat, 13 Feb 2016 22:22:48 domains.py[line:170] INFO     tw&botnet_e : 4
 Sat, 13 Feb 2016 22:22:48 domains.py[line:171] INFO      tw&malware : 153
 Sat, 13 Feb 2016 22:22:48 domains.py[line:172] INFO      w&botnet_r : 3
 Sat, 13 Feb 2016 22:22:48 domains.py[line:173] INFO      w&botnet_e : 9
 Sat, 13 Feb 2016 22:22:48 domains.py[line:174] INFO       w&malware : 887
 Sat, 13 Feb 2016 22:22:48 domains.py[line:176] INFO stat all domains, eclipse: 0.307000s.
 Sat, 13 Feb 2016 22:22:48 domains.py[line:159] INFO train domains before pre process : 5543
 Sat, 13 Feb 2016 22:22:48 domains.py[line:160] INFO        botnet_r : 8
 Sat, 13 Feb 2016 22:22:48 domains.py[line:161] INFO        botnet_e : 75
 Sat, 13 Feb 2016 22:22:48 domains.py[line:162] INFO         malware : 3748
 Sat, 13 Feb 2016 22:22:48 domains.py[line:163] INFO         mal2bot : 0(0)
 Sat, 13 Feb 2016 22:22:48 domains.py[line:164] INFO           white : 888
 Sat, 13 Feb 2016 22:22:48 domains.py[line:165] INFO         outlier : 9
 Sat, 13 Feb 2016 22:22:48 domains.py[line:166] INFO         train_w : 1948
 Sat, 13 Feb 2016 22:22:48 domains.py[line:167] INFO         train_b : 0
 Sat, 13 Feb 2016 22:22:48 domains.py[line:169] INFO     tw&botnet_r : 1
 Sat, 13 Feb 2016 22:22:48 domains.py[line:170] INFO     tw&botnet_e : 4
 Sat, 13 Feb 2016 22:22:48 domains.py[line:171] INFO      tw&malware : 153
 Sat, 13 Feb 2016 22:22:48 domains.py[line:172] INFO      w&botnet_r : 3
 Sat, 13 Feb 2016 22:22:48 domains.py[line:173] INFO      w&botnet_e : 9
 Sat, 13 Feb 2016 22:22:48 domains.py[line:174] INFO       w&malware : 887
 Sat, 13 Feb 2016 22:22:48 domains.py[line:176] INFO stat train domains before pre process, eclipse: 0.035000s.
 Sat, 13 Feb 2016 22:22:48 domains.py[line:159] INFO relative domains of train domain(before preproc) : 18685
 Sat, 13 Feb 2016 22:22:48 domains.py[line:160] INFO        botnet_r : 8
 Sat, 13 Feb 2016 22:22:48 domains.py[line:161] INFO        botnet_e : 75
 Sat, 13 Feb 2016 22:22:48 domains.py[line:162] INFO         malware : 3748
 Sat, 13 Feb 2016 22:22:48 domains.py[line:163] INFO         mal2bot : 0(0)
 Sat, 13 Feb 2016 22:22:48 domains.py[line:164] INFO           white : 1567
 Sat, 13 Feb 2016 22:22:48 domains.py[line:165] INFO         outlier : 20
 Sat, 13 Feb 2016 22:22:48 domains.py[line:166] INFO         train_w : 1948
 Sat, 13 Feb 2016 22:22:48 domains.py[line:167] INFO         train_b : 0
 Sat, 13 Feb 2016 22:22:48 domains.py[line:169] INFO     tw&botnet_r : 1
 Sat, 13 Feb 2016 22:22:48 domains.py[line:170] INFO     tw&botnet_e : 4
 Sat, 13 Feb 2016 22:22:48 domains.py[line:171] INFO      tw&malware : 153
 Sat, 13 Feb 2016 22:22:48 domains.py[line:172] INFO      w&botnet_r : 3
 Sat, 13 Feb 2016 22:22:48 domains.py[line:173] INFO      w&botnet_e : 9
 Sat, 13 Feb 2016 22:22:48 domains.py[line:174] INFO       w&malware : 887
 Sat, 13 Feb 2016 22:22:48 domains.py[line:176] INFO stat relative domains of train domain(before preproc), eclipse: 0.049000s.
 Sat, 13 Feb 2016 22:22:51 feature.py[line:48] INFO get base features, eclipse: 2.756000 s
 Sat, 13 Feb 2016 22:22:51 feature.py[line:102] INFO train filter, outerlier: 39, conflit: 153, not botnet: 3207, not train: 251131 
 Sat, 13 Feb 2016 22:22:51 feature.py[line:103] INFO train pre process, eclipse: 0.120000 s
 Sat, 13 Feb 2016 22:22:51 domains.py[line:159] INFO train domains after pre process : 2174
 Sat, 13 Feb 2016 22:22:51 domains.py[line:160] INFO        botnet_r : 7
 Sat, 13 Feb 2016 22:22:51 domains.py[line:161] INFO        botnet_e : 71
 Sat, 13 Feb 2016 22:22:51 domains.py[line:162] INFO         malware : 380
 Sat, 13 Feb 2016 22:22:51 domains.py[line:163] INFO         mal2bot : 309(309)
 Sat, 13 Feb 2016 22:22:51 domains.py[line:164] INFO           white : 185
 Sat, 13 Feb 2016 22:22:51 domains.py[line:165] INFO         outlier : 0
 Sat, 13 Feb 2016 22:22:51 domains.py[line:166] INFO         train_w : 1794
 Sat, 13 Feb 2016 22:22:51 domains.py[line:167] INFO         train_b : 0
 Sat, 13 Feb 2016 22:22:51 domains.py[line:169] INFO     tw&botnet_r : 0
 Sat, 13 Feb 2016 22:22:51 domains.py[line:170] INFO     tw&botnet_e : 0
 Sat, 13 Feb 2016 22:22:51 domains.py[line:171] INFO      tw&malware : 0
 Sat, 13 Feb 2016 22:22:51 domains.py[line:172] INFO      w&botnet_r : 3
 Sat, 13 Feb 2016 22:22:51 domains.py[line:173] INFO      w&botnet_e : 9
 Sat, 13 Feb 2016 22:22:51 domains.py[line:174] INFO       w&malware : 184
 Sat, 13 Feb 2016 22:22:51 domains.py[line:176] INFO stat train domains after pre process, eclipse: 0.028000s.
 Sat, 13 Feb 2016 22:22:52 feature.py[line:48] INFO get base features, eclipse: 1.473000 s
 Sat, 13 Feb 2016 22:22:52 feature.py[line:134] INFO detect, pass by white: 5620, pass by f: 233272
 Sat, 13 Feb 2016 22:22:52 feature.py[line:135] INFO detect pre process, eclipse: 0.184000 s
 Sat, 13 Feb 2016 22:22:52 domains.py[line:159] INFO detect domains after pre process : 17812
 Sat, 13 Feb 2016 22:22:52 domains.py[line:160] INFO        botnet_r : 4
 Sat, 13 Feb 2016 22:22:52 domains.py[line:161] INFO        botnet_e : 20
 Sat, 13 Feb 2016 22:22:52 domains.py[line:162] INFO         malware : 715
 Sat, 13 Feb 2016 22:22:52 domains.py[line:163] INFO         mal2bot : 127(309)
 Sat, 13 Feb 2016 22:22:52 domains.py[line:164] INFO           white : 0
 Sat, 13 Feb 2016 22:22:52 domains.py[line:165] INFO         outlier : 19
 Sat, 13 Feb 2016 22:22:52 domains.py[line:166] INFO         train_w : 551
 Sat, 13 Feb 2016 22:22:52 domains.py[line:167] INFO         train_b : 0
 Sat, 13 Feb 2016 22:22:52 domains.py[line:169] INFO     tw&botnet_r : 1
 Sat, 13 Feb 2016 22:22:52 domains.py[line:170] INFO     tw&botnet_e : 3
 Sat, 13 Feb 2016 22:22:52 domains.py[line:171] INFO      tw&malware : 54
 Sat, 13 Feb 2016 22:22:52 domains.py[line:172] INFO      w&botnet_r : 0
 Sat, 13 Feb 2016 22:22:52 domains.py[line:173] INFO      w&botnet_e : 0
 Sat, 13 Feb 2016 22:22:52 domains.py[line:174] INFO       w&malware : 0
 Sat, 13 Feb 2016 22:22:52 domains.py[line:176] INFO stat detect domains after pre process, eclipse: 0.043000s.
 Sat, 13 Feb 2016 22:22:52 ffd_main.py[line:80] INFO total eclipse: 57.526000s

--> 
Sat, 13 Feb 2016 19:33:14 ffd_main.py[line:42] INFO ------------------------------------------------------------
Sat, 13 Feb 2016 19:33:14 ffd_main.py[line:43] INFO domain path   : F:\\mygit\\data\\ffd\\domains\\2014 
Sat, 13 Feb 2016 19:33:14 ffd_main.py[line:44] INFO data path     : F:\\mygit\\data\\ffd\\dnslog 
Sat, 13 Feb 2016 19:33:14 ffd_main.py[line:45] INFO run log path  : F:\\mygit\\data\\ffd\\dnslog 
Sat, 13 Feb 2016 19:33:14 ffd_main.py[line:46] INFO tlow,thigh,dlow,dhigh: 10000,15000,0,10000 
Sat, 13 Feb 2016 19:33:21 domains.py[line:94] INFO load domains, eclipse: 7.219000 s
Sat, 13 Feb 2016 19:33:21 domains.py[line:98] INFO domains predefine
Sat, 13 Feb 2016 19:33:21 domains.py[line:99] INFO   botnet_r : 172
Sat, 13 Feb 2016 19:33:21 domains.py[line:100] INFO   botnet_e : 3181
Sat, 13 Feb 2016 19:33:21 domains.py[line:101] INFO    malware : 123180
Sat, 13 Feb 2016 19:33:21 domains.py[line:102] INFO    mal2bot : 0
Sat, 13 Feb 2016 19:33:21 domains.py[line:103] INFO      white : 10000
Sat, 13 Feb 2016 19:33:21 domains.py[line:104] INFO    outlier : 68
Sat, 13 Feb 2016 19:33:21 domains.py[line:105] INFO    train_w : 5001
Sat, 13 Feb 2016 19:33:21 domains.py[line:106] INFO    train_b : 0
Sat, 13 Feb 2016 19:33:53 domains.py[line:227] INFO get domain_domain, eclipse: 31.791000s.
Sat, 13 Feb 2016 19:34:25 domains.py[line:227] INFO get domain_domain, eclipse: 31.888000s.
Sat, 13 Feb 2016 19:34:57 domains.py[line:227] INFO get domain_ip, eclipse: 31.966000s.
Sat, 13 Feb 2016 19:39:56 domains.py[line:227] INFO get ip_domain, eclipse: 299.650000s.
Sat, 13 Feb 2016 19:39:56 domains.py[line:159] INFO all domains : 256704
Sat, 13 Feb 2016 19:39:56 domains.py[line:160] INFO        botnet_r : 8
Sat, 13 Feb 2016 19:39:56 domains.py[line:161] INFO        botnet_e : 75
Sat, 13 Feb 2016 19:39:56 domains.py[line:162] INFO         malware : 3748
Sat, 13 Feb 2016 19:39:56 domains.py[line:163] INFO         mal2bot : 0(0)
Sat, 13 Feb 2016 19:39:56 domains.py[line:164] INFO           white : 5620
Sat, 13 Feb 2016 19:39:56 domains.py[line:165] INFO         outlier : 39
Sat, 13 Feb 2016 19:39:56 domains.py[line:166] INFO         train_w : 1948
Sat, 13 Feb 2016 19:39:56 domains.py[line:167] INFO         train_b : 0
Sat, 13 Feb 2016 19:39:57 domains.py[line:169] INFO     tw&botnet_r : 1
Sat, 13 Feb 2016 19:39:57 domains.py[line:170] INFO     tw&botnet_e : 4
Sat, 13 Feb 2016 19:39:57 domains.py[line:171] INFO      tw&malware : 153
Sat, 13 Feb 2016 19:39:57 domains.py[line:172] INFO      w&botnet_r : 3
Sat, 13 Feb 2016 19:39:57 domains.py[line:173] INFO      w&botnet_e : 9
Sat, 13 Feb 2016 19:39:57 domains.py[line:174] INFO       w&malware : 887
Sat, 13 Feb 2016 19:39:57 domains.py[line:176] INFO stat all domains, eclipse: 0.360000s.
Sat, 13 Feb 2016 19:39:57 domains.py[line:159] INFO train domains before pre process : 5543
Sat, 13 Feb 2016 19:39:57 domains.py[line:160] INFO        botnet_r : 8
Sat, 13 Feb 2016 19:39:57 domains.py[line:161] INFO        botnet_e : 75
Sat, 13 Feb 2016 19:39:57 domains.py[line:162] INFO         malware : 3748
Sat, 13 Feb 2016 19:39:57 domains.py[line:163] INFO         mal2bot : 0(0)
Sat, 13 Feb 2016 19:39:57 domains.py[line:164] INFO           white : 888
Sat, 13 Feb 2016 19:39:57 domains.py[line:165] INFO         outlier : 9
Sat, 13 Feb 2016 19:39:57 domains.py[line:166] INFO         train_w : 1948
Sat, 13 Feb 2016 19:39:57 domains.py[line:167] INFO         train_b : 0
Sat, 13 Feb 2016 19:39:57 domains.py[line:169] INFO     tw&botnet_r : 1
Sat, 13 Feb 2016 19:39:57 domains.py[line:170] INFO     tw&botnet_e : 4
Sat, 13 Feb 2016 19:39:57 domains.py[line:171] INFO      tw&malware : 153
Sat, 13 Feb 2016 19:39:57 domains.py[line:172] INFO      w&botnet_r : 3
Sat, 13 Feb 2016 19:39:57 domains.py[line:173] INFO      w&botnet_e : 9
Sat, 13 Feb 2016 19:39:57 domains.py[line:174] INFO       w&malware : 887
Sat, 13 Feb 2016 19:39:57 domains.py[line:176] INFO stat train domains before pre process, eclipse: 0.039000s.
Sat, 13 Feb 2016 19:39:57 domains.py[line:159] INFO relative domains of train domain(before preproc) : 18685
Sat, 13 Feb 2016 19:39:57 domains.py[line:160] INFO        botnet_r : 8
Sat, 13 Feb 2016 19:39:57 domains.py[line:161] INFO        botnet_e : 75
Sat, 13 Feb 2016 19:39:57 domains.py[line:162] INFO         malware : 3748
Sat, 13 Feb 2016 19:39:57 domains.py[line:163] INFO         mal2bot : 0(0)
Sat, 13 Feb 2016 19:39:57 domains.py[line:164] INFO           white : 1567
Sat, 13 Feb 2016 19:39:57 domains.py[line:165] INFO         outlier : 20
Sat, 13 Feb 2016 19:39:57 domains.py[line:166] INFO         train_w : 1948
Sat, 13 Feb 2016 19:39:57 domains.py[line:167] INFO         train_b : 0
Sat, 13 Feb 2016 19:39:57 domains.py[line:169] INFO     tw&botnet_r : 1
Sat, 13 Feb 2016 19:39:57 domains.py[line:170] INFO     tw&botnet_e : 4
Sat, 13 Feb 2016 19:39:57 domains.py[line:171] INFO      tw&malware : 153
Sat, 13 Feb 2016 19:39:57 domains.py[line:172] INFO      w&botnet_r : 3
Sat, 13 Feb 2016 19:39:57 domains.py[line:173] INFO      w&botnet_e : 9
Sat, 13 Feb 2016 19:39:57 domains.py[line:174] INFO       w&malware : 887
Sat, 13 Feb 2016 19:39:57 domains.py[line:176] INFO stat relative domains of train domain(before preproc), eclipse: 0.061000s.
Sat, 13 Feb 2016 19:42:50 logdb.py[line:128] INFO data line: 3457537, domain: 18685.
Sat, 13 Feb 2016 19:42:50 logdb.py[line:129] INFO build domain cache, eclipse: 173.573000 s
Sat, 13 Feb 2016 19:42:51 feature.py[line:48] INFO get base features, eclipse: 0.314000 s
Sat, 13 Feb 2016 19:42:51 feature.py[line:98] INFO train filted domains cnt, outerlier: 20, conflit: 153, not botnet: 3207
Sat, 13 Feb 2016 19:42:51 feature.py[line:99] INFO train pre process, eclipse: 0.022000 s
Sat, 13 Feb 2016 19:42:51 domains.py[line:159] INFO train domains after pre process : 2174
Sat, 13 Feb 2016 19:42:51 domains.py[line:160] INFO        botnet_r : 7
Sat, 13 Feb 2016 19:42:51 domains.py[line:161] INFO        botnet_e : 71
Sat, 13 Feb 2016 19:42:51 domains.py[line:162] INFO         malware : 380
Sat, 13 Feb 2016 19:42:51 domains.py[line:163] INFO         mal2bot : 309(309)
Sat, 13 Feb 2016 19:42:51 domains.py[line:164] INFO           white : 185
Sat, 13 Feb 2016 19:42:51 domains.py[line:165] INFO         outlier : 0
Sat, 13 Feb 2016 19:42:51 domains.py[line:166] INFO         train_w : 1794
Sat, 13 Feb 2016 19:42:51 domains.py[line:167] INFO         train_b : 0
Sat, 13 Feb 2016 19:42:51 domains.py[line:169] INFO     tw&botnet_r : 0
Sat, 13 Feb 2016 19:42:51 domains.py[line:170] INFO     tw&botnet_e : 0
Sat, 13 Feb 2016 19:42:51 domains.py[line:171] INFO      tw&malware : 0
Sat, 13 Feb 2016 19:42:51 domains.py[line:172] INFO      w&botnet_r : 3
Sat, 13 Feb 2016 19:42:51 domains.py[line:173] INFO      w&botnet_e : 9
Sat, 13 Feb 2016 19:42:51 domains.py[line:174] INFO       w&malware : 184
Sat, 13 Feb 2016 19:42:51 domains.py[line:176] INFO stat train domains after pre process, eclipse: 0.021000s.
Sat, 13 Feb 2016 19:46:32 logdb.py[line:128] INFO data line: 3457537, domain: 256704.
Sat, 13 Feb 2016 19:46:32 logdb.py[line:129] INFO build domain cache, eclipse: 221.665000 s
Sat, 13 Feb 2016 19:46:34 feature.py[line:48] INFO get base features, eclipse: 1.421000 s
Sat, 13 Feb 2016 19:46:34 feature.py[line:130] INFO detect, pass by white: 5620, pass by f: 233272
Sat, 13 Feb 2016 19:46:34 feature.py[line:131] INFO detect pre process, eclipse: 0.185000 s
Sat, 13 Feb 2016 19:46:34 domains.py[line:159] INFO detect domains after pre process : 17812
Sat, 13 Feb 2016 19:46:34 domains.py[line:160] INFO        botnet_r : 4
Sat, 13 Feb 2016 19:46:34 domains.py[line:161] INFO        botnet_e : 20
Sat, 13 Feb 2016 19:46:34 domains.py[line:162] INFO         malware : 715
Sat, 13 Feb 2016 19:46:34 domains.py[line:163] INFO         mal2bot : 127(309)
Sat, 13 Feb 2016 19:46:34 domains.py[line:164] INFO           white : 0
Sat, 13 Feb 2016 19:46:34 domains.py[line:165] INFO         outlier : 19
Sat, 13 Feb 2016 19:46:34 domains.py[line:166] INFO         train_w : 551
Sat, 13 Feb 2016 19:46:34 domains.py[line:167] INFO         train_b : 0
Sat, 13 Feb 2016 19:46:34 domains.py[line:169] INFO     tw&botnet_r : 1
Sat, 13 Feb 2016 19:46:34 domains.py[line:170] INFO     tw&botnet_e : 3
Sat, 13 Feb 2016 19:46:34 domains.py[line:171] INFO      tw&malware : 54
Sat, 13 Feb 2016 19:46:34 domains.py[line:172] INFO      w&botnet_r : 0
Sat, 13 Feb 2016 19:46:34 domains.py[line:173] INFO      w&botnet_e : 0
Sat, 13 Feb 2016 19:46:34 domains.py[line:174] INFO       w&malware : 0
Sat, 13 Feb 2016 19:46:34 domains.py[line:176] INFO stat detect domains after pre process, eclipse: 0.040000s.
Sat, 13 Feb 2016 19:46:34 ffd_main.py[line:77] INFO total eclipse: 800.287000s
'''