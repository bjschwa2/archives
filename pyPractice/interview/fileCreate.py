import time as t
from os import path

def createFile(destination,types,num):
	''' 
	Creates a file in the location specified, of the type specified, 
	it will be named date+number
	'''

	date = t.localtime(t.time())


	for n in range(0,num):

		name = '%d_%d_%d_(%d).%s'%(date[1],date[2],date[0],n,types)

		if not(path.isfile(destination + name)):
			file = open(destination + name, 'w')
			file.write('print("%d")'%(n))
			file.close()

if __name__=='__main__':

	destination = '/home/bradley/Documents/pyPractice/'
	createFile(destination,'py',3)
	print('created files!')