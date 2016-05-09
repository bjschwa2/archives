
import sys

def readFile(arg1):

	with open(arg1) as f:
	    lines = f.readlines()


	return lines

args = sys.argv
lists = readFile(args[0])
print(lists)