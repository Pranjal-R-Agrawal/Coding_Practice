import sys

num_tests = int(sys.stdin.readline())

while num_tests:
    n, m, k = map(int, sys.stdin.readline().strip().split())
    b = list(map(int, sys.stdin.readline().strip().split()))
    c = list(map(int, sys.stdin.readline().strip().split()))

    num = 0

    for i in range(n):
        for j in range(m):
            if b[i] + c[j] <= k:
                num += 1

    print(num)

    num_tests -= 1
