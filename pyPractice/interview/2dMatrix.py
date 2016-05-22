def column(matrix, i):
    return [row[i] for row in matrix]

def row(matrix, i):
    return matrix[i-1] 

def point(matrix, x, y):
    rows = row(matrix,x)
    return rows[y-1]

def search(matrix,value):
    for i, row in enumerate(matrix):
        for k, v in enumerate(row):
            if v == value:
                return[k+1,i+1]

A = [[1,2,3,4],
     [5,6,7,8],
     [9,16,97,8]]

print(column(A,1))
print(row(A,3))
print(point(A,2,2))
print(search(A,7))