
global master
master = []

def printlist(list, *args, **kwargs):

	for inlist in list:
		for item in inlist:
			print (item)

def recursiveprint(*args, **kwargs):
	for outlist in list(args) + list(kwargs.values()):
		if type(outlist) == list:
			for innerlist in outlist:
				if type(innerlist)==list:
					recursiveprint(innerlist)
				else:
					print(innerlist)

def createLists(num):

	if num == 0:
		return 0

	for i in range(0,num):
		small = []
		for j in range(0,i+1):
			small.append(j)
		master.append(small)
	createLists(i)

createLists(100)
lists = [[1,[12,[1000,[14,15,[10000]]]],2,4],[1,44,53],[0,123,2]]
print(lists)
print (master)

recursiveprint(lists,master)