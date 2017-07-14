#!/usr/bin/python3
#-*- coding:utf-8 -*-

import pymysql

#connect to db
conn = pymysql.connect(host = '127.0.0.1', user = 'beijing', passwd = 'beijing2022', db = 'image')
cursor = conn.cursor()


#execute mysql
#sql = 'select * from table';
#cursor.execute(sql)

cursor.execute("drop table if exists test")

sql ="""create table test (
        id int auto_increment primary key,
        href varchar(10000) not null,
        path varchar(1000) not null,  
        word varchar(100)
        )"""

cursor.execute(sql)
table = 'test'
sql2 = 'insert into %s '%table + '(href,path,word) values(%s, %s, %s)' 
print(sql2)
param=('a','b','c')
cursor.execute(sql2, param)
conn.commit()
conn.close()




