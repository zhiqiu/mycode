from selenium import webdriver
import time
import json
from data_parser import *
import sys
import pymysql

def search_keyword(keyword):
    search_url = 'https://www.google.com/search?biw=1920&bih=974&tbm=isch&sa=1&q=' + keyword.replace(' ', '+')

    driver = webdriver.Firefox()
    #driver = webdriver.PhantomJS()
    driver.get(search_url)
    time.sleep(1)
    for i in range(100):
        try:
            driver.execute_script('window.scrollTo(0,document.body.scrollHeight)')
            button = driver.find_element_by_css_selector("input#smb.ksb._kvc[value$='Show more results']");
            button.click()
            time.sleep(1)
        except:
           continue
        
    #print(2)
    #with open('phantomjs.src', 'w', encoding='UTF-8') as f:
    #    f.write(driver.page_source)
    #driver.save_screenshot("aa.png")
    #return 1
    boxes = driver.find_elements_by_css_selector('a.rg_l[rel$="noopener"]')
    print(len(boxes))
    res = []
    for idx, box in enumerate(boxes):
        if idx%100==0:
            print(keyword, idx)
        dict = {}
        href = box.get_attribute('href')
        image = box.find_element_by_tag_name('img').get_attribute('src')
        dict['href'] = href
        dict['url'] = image
        res.append(dict)
        
    with open( keyword + '.json', 'w', encoding='UTF-8') as f:
        f.write(json.dumps(res))
        
    driver.quit()


def create_table(conn, table):
    #connect to db
    #conn = pymysql.connect(host = '127.0.0.1', user = 'beijing', passwd = 'beijing2022', db = 'image')
    cursor = conn.cursor()

    cursor.execute("drop table if exists %s" %table)

    sql ="""create table %s (
        id int auto_increment primary key,
        href varchar(10000) not null,
        path varchar(1000) not null,  
        word varchar(100),
        time varchar(100)
        )""" %table
    cursor.execute(sql)
    conn.commit()

def main(argv):
    conn = pymysql.connect(host = '127.0.0.1', user = 'beijing', passwd = 'beijing2022', db = 'image')
    table='test'
    create_table(conn, table)


    filename = argv[1]
    keywords = [ line.strip() for line in open(filename, 'r')]
    print(keywords)
    for keyword in keywords:
        print(keyword)
        search_keyword(keyword)
        data_parser(keyword, conn, table)
    
    conn.close()


if __name__=='__main__':
    if(len(sys.argv)==1):
        print('usage: python3 scrapy_google keyword.txt')
        sys.exit(0)
    main(sys.argv)
