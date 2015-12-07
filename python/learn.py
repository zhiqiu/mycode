#-*-coding:utf-8-*-
import urllib, urllib2
url = "http://mstc.love-sysu.com/task/chuangguan10"


for i in range(0, 10000):
	if i <= 9:
		num = "000"+str(i)
	elif i <= 99 :
		num = "00"+str(i)
	elif i <= 999:
		num = "0"+str(i)
	else:
		num =str(i)
	data = {
    "code":num
	}
	print num
	#para = urllib.urlencode(data)
	#req = urllib2.Request(url, para)
	#res = urllib2.urlopen(req)
	#print res.read()