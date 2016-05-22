#  Given a positive integer n, break it into the sum of at least two positive integers and maximize the product of those integers. Return the maximum product you can get.

# For example, given n = 2, return 1 (2 = 1 + 1); given n = 10, return 36 (10 = 3 + 3 + 4). 

'''
for each question:
1. brainstorm possible data structures
2. write qseudocode
3. try a solution
4. think out the O(n) notation
5. think about adding exceptions for edge cases

'''

# break up into all divisors
# find all numbers less than 10
# add all combinations of them together
#     if it equals 10 and its > last one 
# make a list of different divisors
#     ex. 10
#         0,10
#         1,9
#         2,8
#         7,3
#         6,4
#         5,5
        
# multiply each together until largest product


def createList(n):
    l = []
    for i in range(1,n+1):
        l.append(i)
    return l

def integerBreak(n):
    if n==2:
        return 1
    if n==3:
        return 2
    if n==4:
        return 4
    
    result = 1
    if n%3==0:
        m=n/3
        result = pow(3,m)
    elif n%3==2:
        m=n/3
        result = pow(3,m) *2
    elif n%3==1:
        m=n/3
        result = pow(3,m) *4
    
    return result
    

print(integerBreak(15))