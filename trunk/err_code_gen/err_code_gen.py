#!/usr/bin/env python
# -*- coding: gbk -*-
#Ϊ���㣬 ֱ����gbk���롣 ���ʹ��utf-8���룬 �����ַ���Ҫת��
import os
import sys
import csv

strCsvPath = "./err_Code.csv"
if len(sys.argv) > 1:
    strCsvPath = sys.argv[1]
    
if not os.path.isfile(strCsvPath):
    print "src file does not exist: %s" % strCsvPath
    sys.exit()

print "src file: %s" % strCsvPath


strDstDir = "./"
if len(sys.argv) > 2:
    strDstDir  = sys.argv[2]
    
if not os.path.exists(strDstDir):
    os.mkdir(strDstDir)
    
print "dst dir: %s" % strDstDir

#ͷ�ļ�ģ��
strHeadFile = '''
#ifndef _ERR_CODE_H
#define _ERR_CODE_H

typedef enum
{
//TODO
}ERet;

typedef struct
{
    int Code;
    const char* ChMemo;
    const char* EnMemo;
}TErrDesc;

int GetErrDesc(int Code, TErrDesc* pErrDesc);

#endif //end _ERR_CODE_H'''

#Դ�ļ�ģ��
strSrcFile = '''
#include "ErrCode.h" 

TErrDesc g_ErrDesc[] =
{
//TODO
};

int GetErrDesc(int Code, TErrDesc* pErrDesc)
{
    int cnt = sizeof(g_ErrDesc)/sizeof(g_ErrDesc[0]);
    for(int i = 0; i < cnt; i++)
    {
        if(g_ErrDesc[i].Code == Code)
        {
            pErrDesc->Code = g_ErrDesc[i].Code;
            pErrDesc->ChMemo = g_ErrDesc[i].ChMemo;
            pErrDesc->EnMemo = g_ErrDesc[i].EnMemo;
            return 0;
        }
    }
    return -1;
}'''

strModule = ""
nValue = 0

strEnumItems = ""
strDescItems = ""

dictList = csv.DictReader(open(strCsvPath))
#����ÿһ��
for dict in dictList:
    str = dict["ģ����д"]
    if str: 
        strModule = str
    else:
        strError = dict["������"]
        ChMemo = dict["����˵��"]
        EnMemo = dict["Ӣ��˵��"]
        strEnumItems += ("    ERet_%s_%s = %d,//%s, %s\n" % (strModule, strError, nValue, ChMemo, EnMemo))
        strDescItems += ("    {%d, \"%s\", \"%s\"},\n" % (nValue, ChMemo, EnMemo))
        nValue -= 1

strHeadFile = strHeadFile.replace("//TODO", strEnumItems)
headFile = open(strDstDir + "/ErrCode.h", "w")
headFile.write(strHeadFile)
headFile.close()

print strHeadFile

strSrcFile = strSrcFile.replace("//TODO", strDescItems)
srcFile = open(strDstDir + "/ErrCode.cpp", "w")
srcFile.write(strSrcFile)
srcFile.close()    

print strSrcFile

print "generate finished!"