import sys


num_tests = int(sys.stdin.readline())
tests = 0

for line in sys.stdin:
    n, c, d = map(int, line.strip().split())

    input_matrix = list(map(int, sys.stdin.readline().strip().split()))
    a11 = min(input_matrix)
    generated_matrix = [a11 + c*i + d*j for i in range(n) for j in range(n)]

    print("YES" if sorted(input_matrix) == sorted(generated_matrix) else "NO")

    tests += 1

    if tests == num_tests:
        break
