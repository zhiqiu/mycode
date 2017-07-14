#!/usr/bin/python3
#-*- coding:utf-8 -*-
import json
import os
import io, base64
import urllib.request
from PIL import Image

def data_parser(keyword):
    with open(keyword + '.json', 'r') as input:
        images = json.load(input)
    if not os.path.exists(keyword):
        try:
            os.mkdir(keyword)
        except:
            print('Makedir Error')
            return
        
    for idx, image in enumerate(images):
        if image['url']:
            data_url = image['url'].split(',')
            if len(data_url) > 1:
                im = Image.open(io.BytesIO(base64.b64decode(data_url[1])))
            else:
                try:
                    im = Image.open(io.BytesIO(urllib.request.urlopen(data_url[0]).read()))
                except:
                    continue
            
            try:
                im.convert('RGB').save(keyword + "/image_" + str(idx) +  ".jpg")
            except:
                print('Save Image Error')
                continue

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
