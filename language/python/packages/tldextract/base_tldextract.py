'''
Accurately separate the TLD from the registered domain and subdomains of a URL, using 
the Public Suffix List.

tldextract accurately separates the gTLD or ccTLD ( generic or country code top-level 
domain) from the registered domain and subdomains of a URL.
'''

>>> import tldextract
>>> tldextract.extract('http://forums.news.cnn.com/')
ExtractResult(subdomain='forums.news', domain='cnn', suffix='com')
>>> tldextract.extract('http://forums.bbc.co.uk/') # United Kingdom
ExtractResult(subdomain='forums', domain='bbc', suffix='co.uk')
>>> tldextract.extract('http://www.worldbank.org.kg/') # Kyrgyzstan
ExtractResult(subdomain='www', domain='worldbank', suffix='org.kg')

# ExtractResult is a named tuple, so it��s simple to access the parts you want.

>>> ext = tldextract.extract('http://forums.bbc.co.uk')
>>> (ext.subdomain, ext.domain, ext.suffix)
('forums', 'bbc', 'co.uk')
>>> # rejoin subdomain and domain
>>> '.'.join(ext[:2])
'forums.bbc'
>>> # a common alias
>>> ext.registered_domain
'bbc.co.uk'

