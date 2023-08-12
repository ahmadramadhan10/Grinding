import sys

lines = sys.stdin.readlines()
N = int(lines[0].strip('\n'))
alice = [int(x) for x in lines[1].strip('\n').split(' ')]
bob = [int(x) for x in lines[2].strip('\n').split(' ')]

# Sort stacks from high to low
alice.sort(reverse=True)
bob.sort(reverse=True)
points = 0
# Two pointer solution
i = 0
j = 0
while i < len(alice):
    while j < len(bob) and bob[j] > alice[i]:
        j += 1
    if j == len(bob):
        break
    points += 1
    i += 1
    j += 1

print(points)