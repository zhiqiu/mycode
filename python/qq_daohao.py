import cookielib, urllib2, urllib, re, random
def get_name(_input):
    temp = _input.split()
    data = {}
    for i in temp:
        temp2 = i.split('=')
        if len(temp2) == 2:
            data[temp2[0]] = temp2[1]
    return data

def get_action(_form):
    temp = _form.split()
    for i in temp:
        temp2 = i.split('=')
        if temp2[0] == 'action':
            return temp2[1][1:-1]

def generate_code(length):
    code = ''
    for i in range(length):
        r = random.randint(0,9)
        code += str(r)
    return code



if __name__ == '__main__':
    while True:
        burl = 'http://www.zprgj.sh.cn/YrZ7q'
        cj = cookielib.CookieJar()
        opener = urllib2.build_opener(urllib2.HTTPCookieProcessor(cj))
        urllib2.install_opener(opener)
        resp = urllib2.urlopen(burl)
        text = resp.read()
        re_input = re.compile('<input(.*?)/>')
        re_form = re.compile('<form(.*?)>')
        all_input = re_input.findall(text)
        form = re_form.findall(text)
        
        
        usr_id = get_name(all_input[1])
        pwd_id = get_name(all_input[2])
        hidden_id = get_name(all_input[-1])
        action = get_action(form[0])
        
        i = 1
        while True:
            try:
                para = {
                    'domain':'@qq.com',
                    usr_id['name'][1:-1]:generate_code(9),
                    pwd_id['name'][1:-1]:generate_code(12),
                    'verifycode':'',
                    'ajax':'1',
                    hidden_id['name'][1:-1]:hidden_id['value'][1:-1]
                }
                print para
                url = 'http://www.zprgj.sh.cn' + action 
                postdata = urllib.urlencode(para)
                req = urllib2.Request(url, postdata)
                resp = urllib2.urlopen(req)
                text = resp.read()
                if text == '':
                    print 'Case #%d: success'%i
                else:
                    print 'Case #%d: '%i + text
                i += 1
            except:
                break