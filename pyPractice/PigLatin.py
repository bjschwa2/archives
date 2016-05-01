import sys
import re

class PigLatin:
	
	
	global vowels, ay, punct
	vowels = ("a","e","o","i","u","y","A","E","O","I","U","Y")
	ay = "ay"
	punct = ['.',',','!','?',';']

	inputed = input("Please enter a word or phrase: ")
	split = re.findall(r"[\w']+|[.,!?;]", inputed)
	print (split)

	def getPrefix(inputed):
		prefix = ''
		for i in inputed:
			if i in vowels:
				return prefix
			else:
				prefix += i
		return prefix

	def capitalize(word):
		word = word.lower()
		word = word.title()
		return word

	sentence = ''
	for x in split:
		if x in punct:
			word = x + " "
		else:
			prefix = getPrefix(x)
			count = len(prefix)
			stem = x[count:]
			word = (stem + prefix + ay + " ")
			if prefix[0].isupper():
				word = capitalize(word)
		sentence += word

	print (sentence)
