import sys

num_tests = int(sys.stdin.readline())

while num_tests:
    n, k = map(int, sys.stdin.readline().strip().split())
    a = list(map(int, sys.stdin.readline().strip().split()))
    left_sums, right_sums = [0] * n, [0] * n

    for i in range(n):
        left_sums[i] = a[i] + (left_sums[i - 1] if i > 0 else 0)

    for i in range(n - 1, -1, -1):
        right_sums[i] = a[i] + (right_sums[i + 1] if i < n - 1 else 0)

    if n == 0:
        print(1)
    elif n == 1:
        print(1 if a[0] <= k else 0)
    else:
        count = 0
        checked = 0
        for i in range(n):
            checked = i
            if left_sums[i] + min(left_sums[-1] - left_sums[i], left_sums[i] - 1) <= k or right_sums[i] + min(right_sums[0] - right_sums[i], right_sums[i]) <= k:
                count += 1
            else:
                break

        for i in range(n - 1, checked, -1):
            if right_sums[i] + min(right_sums[0] - right_sums[i], right_sums[i]) <= k:
                count += 1
            else:
                break

        print(count)

    num_tests -= 1
