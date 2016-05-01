import sys

def findUnique():
	phrase = input("please input a phrase: ")
	words = phrase.split()
	uniqueWords = {}
	for i, word in enumerate(words):
		if word in uniqueWords:
			uniqueWords[word] +=1	
		else:
			uniqueWords[word] = 1
			
	print(uniqueWords)



findUnique()