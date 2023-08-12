import sys

lines = sys.stdin.readlines()
N, K = [int(x) for x in lines[0].strip('\n').split(' ')]
dequeue_forward = lines[1].strip('\n')
dequeue_backward = dequeue_forward[::-1]

current_W_removed, current_B_removed_front, current_B_removed_back = 0, 0, 0
i, j = 0, 0

# Remove only from left side at first
while current_B_removed_front <= K:
    if dequeue_forward[i] == 'W':
        current_W_removed += 1
    elif dequeue_forward[i] == 'B':
        current_B_removed_front += 1
    i += 1
i -= 1
while current_B_removed_back <= 0:
    if dequeue_backward[j] == 'W':
        current_W_removed += 1
    elif dequeue_backward[j] == 'B':
        current_B_removed_back += 1
    j += 1
max_removed = current_W_removed

# Move one black ball to the right side iteratively
for ctr in range(K):
    # Move pointer to left until we remove 1 black ball
    while current_B_removed_front >= K - ctr:
        if dequeue_forward[i] == 'W':
            current_W_removed -= 1
        elif dequeue_forward[i] == 'B':
            current_B_removed_front -= 1
        i -= 1
    # Move pointer as far right as possible until we encounter an extra black ball
    while current_B_removed_back <= ctr+1:
        if dequeue_backward[j] == 'W':
            current_W_removed += 1
        elif dequeue_backward[j] == 'B':
            current_B_removed_back += 1
        j += 1
    max_removed = max(max_removed, current_W_removed)

print(max_removed)
    