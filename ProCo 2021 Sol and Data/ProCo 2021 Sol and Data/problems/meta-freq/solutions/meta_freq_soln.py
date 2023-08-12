asd=input().split()
s=int(asd[0])
n=int(asd[1])
L=list(map(int,input().split()))
L.sort()
q=int(input())
for i in range(q):
    x=int(input())
    if x >= n:
        print(s)
    else:
        print(L[x]-1)
