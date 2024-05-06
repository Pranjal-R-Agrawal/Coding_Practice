import sys

num_tests = int(sys.stdin.readline())

while num_tests:
    n, x = map(int, sys.stdin.readline().strip().split())
    a = list(map(int, sys.stdin.readline().strip().split()))

    max_dist = 0
    for i in range(n - 1):
        max_dist = max(a[i+1] - a[i], max_dist)

    max_dist = max(max_dist, a[0], 2 * (x - a[-1]))
    print(max_dist)

    num_tests -= 1
