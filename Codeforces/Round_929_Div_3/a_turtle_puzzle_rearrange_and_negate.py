import sys

num_tests = int(sys.stdin.readline())

while num_tests:
    n = int(sys.stdin.readline().strip())
    a = list(map(int, sys.stdin.readline().strip().split()))

    # The first operation can be used to collect all the negative terms together
    # The second operation can be used to negate all the collected negative terms
    max_sum = 0
    for i in range(n):
        max_sum += abs(a[i])

    print(max_sum)

    num_tests -= 1
