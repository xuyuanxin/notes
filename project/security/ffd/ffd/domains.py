#coding=utf-8

import os
import logging
import time

import tldextract
import csv
from urlparse import urlparse
import pandas as pd

class Domains:

    def __init__(self, datapath,t_low,t_high,w_low,w_high):
        self.dpath = datapath   # domain path
        self.alexa_t = [t_low,t_high]
        self.alexa_w = [w_low,w_high]
        self.botnet_r = set([]) # 四个botnet阻止列表
        self.botnet_e = set([]) # 加上一个恶意域名列表
        self.malware = set([])  # 恶意域名，包括botnet域名
        self.mal2bot = set([])  # 恶意域名，包括botnet域名
        self.white = set([])    # 免检域名(不包括outlier)
        self.outlier = set([])  # cdn等域名
        self.train_w = set([])
        self.train_b = set([])

    def _load_file(self,f, dset):
        '''
        @f: file name, 每行是一个域名(a.com)，没有其它信息
        @dset: domain set, 把文件@f中的域名加入@dset
        '''		
        for line in open(f):
            ext = tldextract.extract(line.strip())
            dset.add(".".join(ext[1:]))

    def _load_phishtank(self,dset):
         with open(self.dpath+os.sep+"hosts_phishtank.csv", 'rb') as csvfile:
            reader = csv.reader(csvfile)
            for row in reader:
                ext = tldextract.extract(urlparse(row[1]).netloc)
                # print ".".join(ext[1:])
                dset.add(".".join(ext[1:]))

    def _load_alexa(self,begin=0, end=10000):
        df = pd.read_csv(self.dpath+os.sep+"top-1m.csv", names=['rank', 'domain'], header=None, encoding='utf-8')
        return set(list(df[(df['rank'] <= end) & (df['rank'] >= begin)]['domain']))

    def _load_botnet_r(self):
        self._load_file(self.dpath+os.sep+"hosts_badzeus.txt", self.botnet_r)
        self._load_file(self.dpath+os.sep+"hosts_spyeye.txt", self.botnet_r)
        self._load_file(self.dpath+os.sep+"hosts_palevo.txt", self.botnet_r)
        self._load_file(self.dpath+os.sep+"hosts_feodo.txt", self.botnet_r)

    def _load_botnet_e(self):
        self._load_file(self.dpath+os.sep+"hosts_badzeus.txt", self.botnet_e)
        self._load_file(self.dpath+os.sep+"hosts_spyeye.txt", self.botnet_e)
        self._load_file(self.dpath+os.sep+"hosts_palevo.txt", self.botnet_e)
        self._load_file(self.dpath+os.sep+"hosts_feodo.txt", self.botnet_e)
        self._load_file(self.dpath+os.sep+"hosts_cybercrime.txt", self.botnet_e)
		
    def _load_malware(self):
        self._load_file(self.dpath+os.sep+"hosts_badzeus.txt", self.malware)
        self._load_file(self.dpath+os.sep+"hosts_spyeye.txt", self.malware)
        self._load_file(self.dpath+os.sep+"hosts_palevo.txt", self.malware)
        self._load_file(self.dpath+os.sep+"hosts_feodo.txt", self.malware)
        self._load_file(self.dpath+os.sep+"hosts_cybercrime.txt", self.malware)
        self._load_file(self.dpath+os.sep+"hosts_malwaredomains.txt", self.malware)
        self._load_file(self.dpath+os.sep+"hosts_malwaredomainlist.txt", self.malware)
        self._load_file(self.dpath+os.sep+"hosts_hphosts.txt", self.malware)
        self._load_phishtank(self.malware)

    def _load_outlier(self):
        self._load_file(self.dpath+os.sep+"domain_whitelist.txt", self.outlier)
        self._load_file(self.dpath+os.sep+"cdn.txt", self.outlier)
        self._load_file(self.dpath+os.sep+"cdn_new.txt", self.outlier)		

    def _load_white(self):
        w = self._load_alexa(self.alexa_w[0],self.alexa_w[1])
        self.white |= w
	
    def _load_train_w(self):
        w = self._load_alexa(self.alexa_t[0],self.alexa_t[1])
        self.train_w |= w
		
    def load_all(self):
        logger = logging.getLogger("ffd")
        ticks = time.time()
        self._load_botnet_e()
        self._load_botnet_r()
        self._load_malware()
        self._load_outlier()
        self._load_white()
        self._load_train_w()
        logger.info("load domains, eclipse: %f s"%(time.time() - ticks))
		
    def info(self):
        logger = logging.getLogger("ffd")
        logger.info('domains predefine')
        logger.info("%10s : %d"%('botnet_r',len(self.botnet_r)))
        logger.info("%10s : %d"%('botnet_e',len(self.botnet_e)))
        logger.info("%10s : %d"%('malware',len(self.malware)))
        logger.info("%10s : %d"%('mal2bot',len(self.mal2bot)))
        logger.info("%10s : %d"%('white',len(self.white)))
        logger.info("%10s : %d"%('outlier',len(self.outlier)))
        logger.info("%10s : %d"%('train_w',len(self.train_w)))
        logger.info("%10s : %d"%('train_b',len(self.train_b)))

    def stat(self,dset,info):
        botnet_r_cnt = 0
        botnet_e_cnt = 0
        malware_cnt  = 0
        mal2bot_cnt  = 0
        white_cnt    = 0
        outlier_cnt  = 0
        train_w_cnt  = 0
        train_b_cnt  = 0

        tw_botnet_r  = 0
        tw_botnet_e  = 0
        tw_malware   = 0
        w_botnet_r   = 0
        w_botnet_e   = 0
        w_malware    = 0  
		
        logger = logging.getLogger("ffd")
        ticks  = time.time()

        for domain in dset:
            if domain in self.botnet_r:
                botnet_r_cnt += 1
            if domain in self.botnet_e:
                botnet_e_cnt += 1
            if domain in self.malware:
                malware_cnt += 1
            if domain in self.mal2bot:
                mal2bot_cnt += 1
            if domain in self.white:
                white_cnt += 1
            if domain in self.outlier:
                outlier_cnt += 1
            if domain in self.train_w:
                train_w_cnt += 1
            if domain in self.train_b:
                train_b_cnt += 1

            if domain in self.train_w and domain in self.botnet_r:
                tw_botnet_r += 1
            if domain in self.train_w and domain in self.botnet_e:
                tw_botnet_e += 1
            if domain in self.train_w and domain in self.malware:
                tw_malware += 1
            if domain in self.white and domain in self.botnet_r:
                w_botnet_r += 1
            if domain in self.white and domain in self.botnet_e:
                w_botnet_e += 1
            if domain in self.white and domain in self.malware:
                w_malware += 1
				
        logger.info("%s : %d"%(info,len(dset)))
        logger.info("%15s : %d"%('botnet_r',botnet_r_cnt))
        logger.info("%15s : %d"%('botnet_e',botnet_e_cnt))
        logger.info("%15s : %d"%('malware',malware_cnt))
        logger.info("%15s : %d(%d)"%('mal2bot',mal2bot_cnt,len(self.mal2bot)))
        logger.info("%15s : %d"%('white',white_cnt))
        logger.info("%15s : %d"%('outlier',outlier_cnt))
        logger.info("%15s : %d"%('train_w',train_w_cnt))
        logger.info("%15s : %d"%('train_b',train_b_cnt))

        logger.info("%15s : %d"%('tw&botnet_r',tw_botnet_r))
        logger.info("%15s : %d"%('tw&botnet_e',tw_botnet_e))
        logger.info("%15s : %d"%('tw&malware',tw_malware))
        logger.info("%15s : %d"%('w&botnet_r',w_botnet_r))
        logger.info("%15s : %d"%('w&botnet_e',w_botnet_e))
        logger.info("%15s : %d"%('w&malware',w_malware))

        logger.info("stat %s, eclipse: %fs."%(info, time.time() - ticks))
		
	
		
