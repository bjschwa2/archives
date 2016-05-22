import re

'''
Identifiers:

    \d = any number
    \D = anything but a number
    \s = space
    \S = anything but a space
    \w = any letter
    \W = anything but a letter
    . = any character, except for a new line
    \b = space around whole words
    \. = period. must use backslash, because . normally means any character.

Modifiers:

    {1,3} = for digits, u expect 1-3 counts of digits, or "places"
    + = match 1 or more
    ? = match 0 or 1 repetitions.
    * = match 0 or MORE repetitions
    $ = matches at the end of string
    ^ = matches start of a string
    | = matches either/or. Example x|y = will match either x or y
    [] = range, or "variance"
    {x} = expect to see this amount of the preceding code.
    {x,y} = expect to see this x-y amounts of the precedng code

White Space Charts:

    \n = new line
    \s = space
    \t = tab
    \e = escape
    \f = form feed
    \r = carriage return

Characters to REMEMBER TO ESCAPE IF USED!

    . + * ? [ ] $ ^ ( ) { } | \

    .*? = Find everything 

Brackets:

    [] = quant[ia]tative = will find either quantitative, or quantatative.
    [a-z] = return any lowercase letter a-z
    [1-5a-qA-Z] = return all numbers 1-5, lowercase letters a-q and uppercase A-Z
'''

exampleString = '''
Jessica is 15 years old, and Daniel is 27 years old.
Edward is 97 years old, and his grandfather, Oscar, is 102. 
'''

ages = re.findall(r'\d{1,3}',exampleString)
names = re.findall(r'[A-Z][a-z]*',exampleString)

print(ages)
print(names)

namedic = {}
for i, name in enumerate(names):
    namedic[name] = ages[i]

print (namedic)

# examples
# .  Normally matches any character except a newline. Within square brackets the dot is literal.
string1 = "Hello, world."
if re.search(r".....", string1):
    print (string1 + " has length >= 5")

# () Groups a series of pattern elements to a single element. When you match a pattern within parentheses, you can use any of $1, $2, ... later to refer to the previously matched pattern.

m_obj = re.search(r"(H..).(o..)", string1)
if m_obj:
    print ("We matched '" + m_obj.group(1) +\
          "' and '" + m_obj.group(2) + "'")

# + Matches the preceding pattern element one or more times.
if re.search(r"l+", string1):
    print ('There are one or more consecutive letter "l"' +\
          "'s in " + string1)


# ? Matches the preceding pattern element zero or one times.
if re.search(r"H.?e", string1):
    print ("There is an 'H' and a 'e' separated by " +\
          "0-1 characters (Ex: He Hoe)\n")

# Modifies the *, +, or {M,N}'d regexp that comes before to match as few times as possible.
if re.search(r"l.+?o", string1):
    print ("The non-greedy match with 'l' followed by\n" +\
          "one or more characters is 'llo' rather than\n" +\
          "'llo wo'.")

# * Matches the preceding pattern element zero or more times.
if re.search(r"el*o", string1):
    print ("There is an 'e' followed by zero to many\n" +\
          "'l' followed by 'o' (eo, elo, ello, elllo)")
 
# {M,N} Denotes the minimum M and the maximum N match count.
if re.search(r"l{1,2}", string1):
    print ("There exists a substring with at least 1\n" +\
          "and at most 2 l's in " + string1)


# []  Denotes a set of possible character matches.
if re.search(r"[aeiou]+", string1):
    print (string1 + " contains one or more vowels.")

# | Separates alternate possibilities.
if re.search(r"(Hello|Hi|Pogo)", string1):
    print ("At least one of Hello, Hi, or Pogo is " +\
          "contained in " + string1)

# \b Matches a word boundary.

if re.search(r"llo\b", string1):
    print ("There is a word that ends with 'llo'")
else:
    print ("There are no words that end with 'llo'")

# \w Matches an alphanumeric character, including "_".

m_obj = re.search(r"(\w\w)", string1)
if m_obj:
    print ("The first two adjacent alphanumeric characters")
    print ("(A-Z, a-z, 0-9, _) in", string1, "were",)
    print (m_obj.group(1))

# \W Matches a non-alphanumeric character, excluding "_".
if re.search(r"\W", string1):
    print ("The space between Hello and " +\
          "World is not alphanumeric")

# \s Matches a whitespace character (space, tab, newline, form feed)
if re.search(r"\s.*\s", string1):
    print ("There are TWO whitespace characters, which may")
    print ("be separated by other characters, in", string1)

# \S Matches anything BUT a whitespace.
m_obj = re.search(r"(\S*)\s*(\S*)", string1)
if m_obj:
    print ("The first two groups of NON-whitespace characters")
    print ("are '%s' and '%s'." % m_obj.groups())

# \d Matches a digit, same as [0-9].
m_obj = re.search(r"(\d+)", string1)
if m_obj:
    print (m_obj.group(1), "is the first number in '" +\
                          string1 + "'")

# \D Matches a non-digit.
string1 = "Hello World"
if re.search(r"\D", string1):
    print ("There is at least one character in", string1,)
    print ("that is not a digit.")

#  ^ Matches the beginning of a line or string.
if re.search(r"^He", string1):
    print (string1, "starts with the characters 'He'")

# $ Matches the end of a line or string.
if re.search(r"rld$", string1):
    print (string1, "is a line or string " +\
          "that ends with 'rld'")

# \A Matches the beginning of a string (but not an internal line).
if re.search(r"\AH", string1):
    print (string1, "is a string",)
    print ("that starts with 'H'")

# \Z Matches the end of a string (but not an internal line).
if re.search(r"d\n\Z", string1):
    print (string1, "is a string",)
    print ("that ends with 'd\\n'")

# [^...] Matches every character except the ones inside brackets.
if re.search(r"[^abc]", string1):
    print (string1 + " contains a character other than " +\
          "a, b, and c")