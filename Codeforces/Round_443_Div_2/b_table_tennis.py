# 15 minutes

import sys

n, k = map(int, sys.stdin.readline().strip().split())
a = list(map(int, sys.stdin.readline().strip().split()))

winner = a[0]
num_defeated = 0

for i in range(1, n):
    if a[i] > winner:
        winner = a[i]
        num_defeated = 1
    elif a[i] < winner:
        num_defeated += 1
        if num_defeated >= k:
            break

print(winner)
