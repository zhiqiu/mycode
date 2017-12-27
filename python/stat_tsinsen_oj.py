# -*- coding: utf-8 -*-

"""
合并清橙oj上的成绩统计结果
使用pandas处理excel

Author: chenql
"""

import sys
import os
import xlwt, xlrd
import pandas as pd
import numpy as np
from selenium import webdriver
from selenium.webdriver.common.action_chains import *
import time


def download_excel():

    driver = webdriver.Chrome()
    search_url = 'http://oj.tsinsen.com/'
    driver.get(search_url)

    # 登录
    driver.find_element_by_css_selector('#username').send_keys('chenql')
    driver.find_element_by_css_selector('#password').send_keys('chenqiuliang')
    driver.find_element_by_css_selector('#cuinfo > input:nth-child(3)').click()

    # 切换课程
    chain = ActionChains(driver)
    menu = driver.find_element_by_xpath('//*[@id="mainm"]/ul')
    chain.move_to_element(menu).perform()
    submenu = menu.find_element_by_xpath('./li[4]')
    chain.move_to_element(submenu).perform()


    time.sleep(10)
    lessons = driver.find_elements_by_xpath('//*[@id="domainList"]/div/table/tbody/tr')
    for lesson in lessons:
        lesson.find_element_by_xpath('./td[2]/div/a')
        lesson.click()


    time.sleep(5)

    # 元素不可点击
    # Element is not clickable at point
    # button = driver.find_element_by_css_selector("#holdings-cnt > ul > li.trade-history ")
    # button.click()

    # 用js实现点击
    #driver.execute_script('var q=document.getElementsByClassName("trade-history");q[0].click();')

    print(driver.page_source)
    # driver.quit()


def stat_score(score_path, same_path):
    files = os.listdir(score_path)
    res_score = pd.DataFrame()
    # 处理成绩文件
    for idx, file in enumerate(files):
        filepath = score_path + '/' + file
        if os.path.isfile(filepath):
            # 读入excel表格
            # 用户名	姓名	总分	题目1 题目2 ...
            # xxx   xxx  xx xx    xx
            data = pd.read_excel(filepath, sheet_name=0, skiprows=range(4))  # header=None,
            # 平均分 = 总分(第3列)/ 题目数(列数-3)
            data[str(idx + 1)] = data.iloc[:, 2] / (data.shape[1] - 3)
            # print(data)

            if res_score.empty:
                res_score = data.iloc[:, [0, 1, -1]]
            else:
                res_score = pd.merge(res_score, data.iloc[:, [0, -1]], on='用户名')
            #print(res_score)

            # 使用xlrd读取excel
            # wb = xlrd.open_workbook(filepath)
            # table = wb.sheets()[0]
            # for row in range(5, table.nrows):
            #     print(table.row_values(row))
            # with open(file) as f:


    # 处理查重文件
    files = os.listdir(same_path)
    res_same = pd.DataFrame()
    for idx, file in enumerate(files):
        filepath = same_path + '/' + file
        if os.path.isfile(filepath):
            # 读入查重excel表格
            # 用户名	姓名	 雷同数	题目1 题目2 ...
            # xxx   xxx  xx     xx    xx
            data = pd.read_excel(filepath, sheet_name=0, skiprows=range(5))  # header=None,
            # 平均分 = 总分(第3列)/ 题目数(列数-3)
            data[str(idx+1)] = data.iloc[:, 2]
            # print(data)

            if res_same.empty:
                res_same = data.iloc[:, [0, 1, -1]]
            else:
                res_same = pd.merge(res_same, data.iloc[:, [0, -1]], on='用户名')
        #print(res_same)
    # 总雷同次数从第三次开始统计
    res_same['总雷同次数'] = res_same.iloc[:, 3:].apply(lambda x: x.sum(), axis=1)
    #print(res_same)
    res = pd.merge(res_score, res_same.iloc[:, [0, -1]], on='用户名')

    res['平均分'] = res.iloc[:, 2:-1].apply(lambda x: x.sum(), axis=1) / res.iloc[:, 2:-1].shape[1]
    #print(res)
    writer = pd.ExcelWriter(score_path + '/res.xlsx')
    res.to_excel(writer, 'Sheet1', index=False)
    writer.save()


def main():
    # 分数文件路径
    score_path = 'C:/Users/chenql/Desktop/math'
    # 查重文件路径
    same_path = 'C:/Users/chenql/Desktop/math/same'
    stat_score(score_path, same_path)

if __name__ == '__main__':
    main()
