import sys

lines = sys.stdin.readlines()
N, K = [int(x) for x in lines[0].strip('\n').split(' ')]
marbles = lines[1].strip('\n')

# start from left
left = 0
sofar = 0
contigleft = []
for k in range(N):
    if left <= K:
        if marbles[k] == 'B':
            left += 1
            contigleft.append(sofar)
            sofar = 0
        else:
            sofar += 1
    else:
        break

right = 0
sofar = 0
contigright = []
for k in range(N-1, -1, -1):
    if right <= K:
        if marbles[k] == 'B':
            right += 1
            contigright.append(sofar)
            sofar = 0
        else:
            sofar += 1
    else:
        break

maxwhite = sum(contigleft) + contigright[0]
white = sum(contigleft) + contigright[0]
for i in range(1, K+1):
    white = white - contigleft[-i] + contigright[i]
    maxwhite = max(maxwhite, white)
print(maxwhite)
