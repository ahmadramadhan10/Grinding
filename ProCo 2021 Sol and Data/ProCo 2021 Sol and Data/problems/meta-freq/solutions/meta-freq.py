import sys

lines = sys.stdin.readlines()
s, n = [int(x) for x in lines[0].strip('\n').split(' ')]
arr = [int(x) for x in lines[1].strip('\n').split(' ')]
q = int(lines[2].strip('\n'))
arr.sort()

for line in lines[3:]:
    num = int(line.strip('\n'))
    if num >= len(arr):
        print(s)
    else:
        print(arr[num] - 1)