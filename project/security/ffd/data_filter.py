'''
过滤passivedns数据
1 只关心IPV4的数据
2 只关心 domain ip ttl
3 去重(domain ip ttl 完全一致认为是重复数据)
'''

import os

dns_log_path = "F:\\mygit\\data\\ffd\\dnslog"
output_path  = "F:\\mygit\\data\\ffd\\dnslog_filted"
dnslog_distinct = "F:\\mygit\\data\\ffd\\dnslog_distinct"
allfiles=['2014-01-01','2014-01-02','2014-01-03','2014-01-04','2014-01-05','2014-01-06','2014-01-07','2014-01-08']

nums_all = 0
nums_filted = 0
nums_distincted = 0

all_lines = set()
for f in allfiles:
    wf1 = open(os.path.join(output_path, f),'w')
    wf2 = open(os.path.join(dnslog_distinct, f),'w')

    nums_all = 0
    nums_filted = 0
    nums_distincted = 0
    all_lines.clear()

    for line in open(os.path.join(dns_log_path, f)):
        nums_all += 1
        line_array = line.split("||")

        if len(line_array) != 9 or line_array[5] != 'A':
            continue

        ip     = line_array[6]
        ttl    = line_array[7]
        domain = line_array[4]
        
        new_data = '0||0||0||0||'+domain+'||A||'+ip+'||'+ttl+'||'+'0'

        nums_filted += 1
        if new_data not in all_lines:
            all_lines.add(new_data)
            nums_distincted += 1


        wf1.write(new_data)

    for line in all_lines:
        wf2.write(line+'\n')
    
    print("%s %d/%d/%d %f/%f %f"%(f,nums_all,nums_filted,nums_distincted,\
	     float(nums_filted)/nums_all,float(nums_distincted)/nums_filted,float(nums_distincted)/nums_all))
    
'''
#timestamp       ||dns-client ||dns-server||RR class||Query              ||Query Type  ||Answer       ||TTL          ||Count
1322849924.408856||10.1.1.1   ||8.8.8.8   ||IN      ||upload.youtube.com.||A           ||74.125.43.117||46587        ||5
0                  1            2           3         4                    5             6              7              8

2014-01-01 2668445/1957701/1249696 0.733649/0.638349 0.468324
2014-01-02 2793057/1948404/1176554 0.697588/0.603855 0.421242
2014-01-03 2591309/1804549/1083073 0.696385/0.600190 0.417964
2014-01-04 2433657/1650293/1000908 0.678112/0.606503 0.411277
2014-01-05 2405842/1684271/1026049 0.700075/0.609195 0.426482
2014-01-06 3267306/2422215/1483024 0.741349/0.612259 0.453898
2014-01-07 4038918/3193688/2184930 0.790729/0.684140 0.540969
2014-01-08 3457537/2383897/1121738 0.689478/0.470548 0.324433
'''    

