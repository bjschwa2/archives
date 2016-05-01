import re, urllib.request

def scrapSite(criteria, site):
	info = []
	for s in site:
		print ('looking for: '+ s)
		text = urllib.request.urlopen('http://' + s + '.com').read()
		info.append(re.findall(criteria, str(text)))
	return info


criteria = re.compile(r'<title>+.*</title>+',re.I | re.M)
site = 'movies google yahoo wikipedia'.split()
title = scrapSite(criteria, site)
print (title)