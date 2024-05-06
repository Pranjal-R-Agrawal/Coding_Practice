import sys

num_tests = int(sys.stdin.readline())

while num_tests:
    n = int(sys.stdin.readline().strip())
    c = list(map(int, sys.stdin.readline().strip().split()))

    num_moves = c[0] - 1
    for i in range(1, n):
        num_moves += max(c[i] - c[i-1], 0)

    print(num_moves)

    num_tests -= 1
