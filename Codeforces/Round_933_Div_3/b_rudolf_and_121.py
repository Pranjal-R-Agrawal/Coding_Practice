import sys

num_tests = int(sys.stdin.readline())

while num_tests:
    n = int(sys.stdin.readline())
    a = list(map(int, sys.stdin.readline().strip().split()))
    possible = True

    for i in range(1, n-1):
        a[i-1], a[i], a[i+1] = 0, a[i] - 2 * a[i-1], a[i+1] - a[i-1]

        if a[i] < 0 or a[i+1] < 0:
            possible = False
            break

    print("YES" if possible and a[-2] == 0 and a[-1] == 0 else "NO")

    num_tests -= 1
