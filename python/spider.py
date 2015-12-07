import urllib, urllib2
import cookielib
#

filename = 'cookie.txt'
#
cookie = cookielib.MozillaCookieJar(filename)
# load from file
#cookie.load('cookie.txt', ignore_discard=True, ignore_expires=True)

#cookie = cookielib.CookieJar()
handler = urllib2.HTTPCookieProcessor(cookie)

opener = urllib2.build_opener(handler)
#response = opener.open('http://soj.sysu.edu.cn')
postdata = urllib.urlencode({
			'username':'smiedsa',
			'password':'07563668787',
			'lsession':'1'
		})
loginUrl = 'http://soj.sysu.edu.cn/action.php?act=Login'

response = opener.open(loginUrl, postdata)

print response.read()

cookie.save(ignore_discard=True, ignore_expires=True)

url = 'http://soj.sysu.edu.cn/index.php'
print opener.open(url).read()
# for item in cookie:
# 		print 'Name = '+ item.name
# 		print 'Value = '+item.value

standingurl = 'http://soj.sysu.edu.cn/standing.php?cid=1995'

res = opener.open(standingurl)
#print res.read()d's

#request = 


