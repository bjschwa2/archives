# Words beginning with a vowel, remove the vowel letter and append the letter to the end.
# All words append the letters 'ni' to the end.
# All words incrementally append the letter 'j'. i.e. 'j','jj','jjj', etc...  

def vowelToEnd(worda):
    vowels = ["a",'e','i','o','u','A','E','I','O','U']
    words = worda.split()
    new = []
    for word in words:
        if word[0] in vowels:
            if len(word) == 1:
                new.append(word)
            else:
                new.append(word[1:] + word[0])
        else:
            new.append(word)
            
    return new
    
def niToEnd(lists):
    new = []
    for word in lists:
        new.append(word + 'ni')
    return new

def appendj(lists, n):
    new = []
#     make j string
    js = ''
    for j in range(0, n):
        js += 'j'
    
    for i in lists:
        new.append(i + js)

    return new
    
string = "I will append words and stuff so help me god"

voweled = vowelToEnd(string)
nied = niToEnd(voweled)
jed = appendj(nied, 4)
print(jed)