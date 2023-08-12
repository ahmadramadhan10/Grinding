import sys

lines = sys.stdin.readlines()
N = int(lines[0].strip('\n'))
array = [int(x) for x in lines[1].strip('\n').split(' ')]

even_count = 0
odd_count = 0
for i in range(len(array)):
    if i % 2 == 0:
        if array[i] % 2 == 1:
            even_count += 1
        else:
            odd_count += 1
    elif i % 2 == 1:
        if array[i] % 2 == 0:
            even_count += 1
        else:
            odd_count += 1
optimal = min(even_count, odd_count)
print(optimal)