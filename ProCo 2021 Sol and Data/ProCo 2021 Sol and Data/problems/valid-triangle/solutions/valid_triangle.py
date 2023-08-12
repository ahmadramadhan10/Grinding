n = input()
for i in range(int(n)):
    a, b, c = [int(x) for x in input().split()]
    if (a + b <= c or a + c <= b or b + c <= a):
        print('No')
    else:
        print('Yes')
