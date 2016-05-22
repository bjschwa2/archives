# import time as t
# from os import path

# def createFile(destination,types,num):
#     ''' 
#     Creates a file in the location specified, of the type specified, 
#     it will be named date+number
#     '''

#     date = t.localtime(t.time())


#     for n in range(0,num):

#         name = '%d_%d_%d_(%d).%s'%(date[1],date[2],date[0],n,types)

#         if not(path.isfile(destination + name)):
#             file = open(destination + name, 'w')
#             file.write('<p> bjschwa2@ncsu.edu is my email address </p>')
#             file.close()

# if __name__=='__main__':

#     destination = ''
#     createFile(destination,'html',10)
#     print('created files!')

import os 
import sys
import re

def findFiles(types):
    fileList = []
    rootdir = "."
    for root,subFolders,files in os.walk(rootdir):
        for f in files:
            if f.endswith('.'+ types):
                fileList.append(os.path.join(root,f))
    return fileList

def findEmails(fileList):    
    for files in fileList:
        for line in open(files, 'r'):
            subbed = re.sub(r'[a-z]+[0-9]*@[a-z]{1,3}.[a-z]{1,3}' ,"****", line)
            print(subbed)
    return fileList
            
files = findFiles('html')
findEmails(files)