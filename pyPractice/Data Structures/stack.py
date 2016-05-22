# from pythonds.basic.stack import Stack

# s=Stack()

# print(s.isEmpty())
# s.push(4)
# s.push('dog')
# print(s.peek())
# s.push(True)
# print(s.size())
# print(s.isEmpty())
# s.push(8.4)


class Stack:
    def __init__(self):
        self.items = []
    
    def isEmpty(self):
        return self.items == []
    
    def push(self, item):
        self.items.append(item)
    
    def pop(self):
        return self.items.pop(-1)
    
    def peek(self):
         return self.items[len(self.items)-1]

    def size(self):
         return len(self.items)
        
        
newStack = Stack()

newStack.push("george")
newStack.push("Bob")
print (newStack.peek())
print (newStack.size())
last=newStack.pop()
print (newStack.peek())
print (last)



