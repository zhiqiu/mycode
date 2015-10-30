import urllib, urllib2
import cookielib
#
cookie = cookielib.CookieJar()
handler = urllib2.HTTPCookieProcessor(cookie)

opener = urllib2.build_opener(handler)
#response = opener.open('http://soj.sysu.edu.cn')
response = opener.open('http://www.baidu.com')

for item in cookie:
		print 'Name = '+ item.name
		print 'Value = '+item.value

#request = 
