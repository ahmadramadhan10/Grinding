import sys

lines = sys.stdin.readlines()
N = int(lines[0].strip('\n'))
for i in range(N):
    a, b, c = [int(x) for x in lines[i+1].strip('\n').split(' ')]
    if a + b > c and a + c > b and b + c > a:
        print("Yes")
    else:
        print("No")