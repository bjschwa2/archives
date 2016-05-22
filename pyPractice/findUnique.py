
# find top three most occuring

def findUnique(phrase):
    words = phrase.split()
    uniqueWords = {}
    for word in words:
        if word in uniqueWords:
            uniqueWords[word] +=1    
        else:
            uniqueWords[word] = 1
            
    return uniqueWords



A = findUnique("please print this out please please print out print please")
newA = sorted(A, key=A.get, reverse=True)[:3]

print (newA)