import sys

num_tests = int(sys.stdin.readline())

while num_tests:
    n, m = map(int, sys.stdin.readline().strip().split())
    a = list(map(int, sys.stdin.readline().strip().split()))
    b = list(map(int, sys.stdin.readline().strip().split()))

    a.sort()
    b.sort(reverse=True)

    max_diff, diff = 0, 0
    for i in range(n):
        diff += abs(a[i] - b[i])

    max_diff = diff
    for c in range(n-1, -1, -1):
        diff += abs(a[c] - b[-(n-c)]) - abs(a[c] - b[c])
        max_diff = max(max_diff, diff)

    print(max_diff)

    num_tests -= 1
