#-*-coding:utf-8-*-
"""
测试使用新浪微博api发送一条微博
"""
import weibo  #导入weibo的库

APP_KEY = 'XXXXXXXXXX'
APP_SECRET = 'XXXXXXXXX'
CALL_BACK = 'XXXXXXXXX'
#上面三个变量是在微博开放平台上创建应用时反馈回来的值

client = weibo.APIClient(APP_KEY, APP_SECRET, CALL_BACK)  #新建新浪微博客户端
auth_url = client.get_authorize_url()
print auth_url  
#打印授权url，这时将该url复制到浏览器，授权之后，在回调页的url中获得code值，将code值作为下面的输入

code = raw_input()
r  = client.request_access_token(code)
client.set_access_token(r.access_token, r.expires_in)
client.statuses.update.post(status="这条是测试用的微博")
#到官方文档查看api的使用方法，替换掉上面的statuses update post以及参数即可调用其他的api接口
