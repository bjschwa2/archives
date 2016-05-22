import sys

class Fibonacci:

	global n 
	n = sys.argv[1]

	def findNth(self,n):
		count = 0
		i = 0
		j = 1
		num = 0
		while count < n-1:
			if(count%2==0):
				i = i + j
				num = i
			else:
				j = i + j
				num = j
			count += 1
		return num

fib= Fibonacci()
print(fib.findNth(int(n)))