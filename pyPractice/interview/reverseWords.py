

# // Reverse the words. Given a String that contains words separated by single space, reverse the words in the String. You can assume that no leading or trailing spaces are there.
# // For example: "Man bites dog" => "dog bites Man”


def reverseWords(s):
    new = ""
    sList=s.split()
    reverseSlist = sList[::-1]
    for i in reverseSlist:
        new += " " + (i)
    return new

print(reverseWords("Hello my name is john"))