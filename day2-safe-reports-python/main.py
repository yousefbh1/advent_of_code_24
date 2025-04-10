with open("input.txt") as f:
    input_data = f.read()

li = []

for arr in input_data.split('\n'):
    temp = []
    for val in arr.split(' '):
        temp.append(int(val))
    li.append(temp)

safe_count = 0

def checkSafe(arr):
    ascending = True
    descending = True

    for i in range(len(arr) - 1):
        if arr[i] > arr[i+1]:
            ascending = False
        if arr[i] < arr[i+1]:
            descending = False
        if abs(arr[i] - arr[i+1]) > 3 or abs(arr[i] - arr[i+1]) < 1:
            return False
    
    return ascending or descending


for arr in li:
    if checkSafe(arr):
        print(arr)
        safe_count += 1

safe_count_2 = 0

for arr in li:
    for i in range(len(arr)):
        if checkSafe(arr[:i] + arr[i+1:]):
            safe_count_2 += 1
            break

print(safe_count)
print(safe_count_2)