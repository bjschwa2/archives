class Solution(object):
    
    def reverseVowels(self, s):
        """
        :type s: str
        :rtype: str
        """
        vowels = ("a","e","i","o","u","A","E","I","O","U")
        vowel = []
        word = []
        
        if s == ".":
            return s
        
        for x in s:
            if x in vowels:
                vowel.append(x)
                word.append("@@@@")
            else:
                word.append(x)
        
        count = 0
        for x in word:
            
            if x == "@@@@":
                word[count] = vowel.pop()
                
            count +=1
            
            
        return ''.join(word)