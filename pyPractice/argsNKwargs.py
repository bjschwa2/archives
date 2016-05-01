

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
	master = []
	if num == 0:
		return master

	for i in range(0,num):
		small = []
		for j in range(0,i):
			small.append(j)
		master.append(small)

	createLists(num-1)
	print (num)

list = createLists(5)
print (list)

lists = [[1,12,2,4],[1,44,53],[0,123,2]]
recursiveprint(lists)