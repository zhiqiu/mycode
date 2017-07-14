import json
import os
import io, base64
import urllib.request
from PIL import Image
import datetime

def data_parser(keyword, conn, table):
    with open(keyword + '.json', 'r') as input:
        images = json.load(input)
    if not os.path.exists(keyword):
        try:
            os.mkdir(keyword)
        except:
            print('Makedir Error')
            return
        
    for idx, image in enumerate(images):
        if image['href'] and image['url']:
            #check if exist
            cursor = conn.cursor()
            sql = 'select * from %s where href=\'%s\';'%(table, image['href'])
            cursor.execute(sql)
            res = cursor.fetchall()
            
            if len(res) != 0:
                print(res)
                print('%s exists'% image['href'])
                continue

            #conn.commit()
            #
            data_url = image['url'].split(',')
            if len(data_url) > 1:
                im = Image.open(io.BytesIO(base64.b64decode(data_url[1])))
            else:
                try:
                    im = Image.open(io.BytesIO(urllib.request.urlopen(data_url[0]).read()))
                except:
                    continue
            
            path = keyword + "/image_" + str(idx) +".jpg"
            try:
                im.convert('RGB').save(path)
            except:
                print('Save Image Error')
                continue
            
            sql2 = 'insert into %s '%table + '(href,path,word,time) values(%s, %s, %s, %s)' 
            param = (image['href'], path, keyword, datetime.datetime.now())
            cursor.execute(sql2, param)
            cursor.close()
            conn.commit()
        else:
            print('%d in %s missing'%(idx, keyword))

def main(argv):
    filename = argv[1]
    keywords = [ line.strip() for line in open(filename, 'r')]
    print(keywords)
    for keyword in keywords:
        data_paser(keyword)
    
if __name__=='__main__':
    if(len(sys.argv)==1):
        print('usage: python3 data_parser keyword.txt')
        sys.exit(0)
