import sys

num_tests = int(sys.stdin.readline())


while num_tests:
    n = int(sys.stdin.readline())
    p1 = set(sys.stdin.readline().strip().split())
    p2 = set(sys.stdin.readline().strip().split())
    p3 = set(sys.stdin.readline().strip().split())

    s1, s2, s3 = 0, 0, 0
    for word in p1:
        count = (word in p2) + (word in p3) + 1
        if count == 1:
            s1 += 3
        elif count == 2:
            s1 += 1

    for word in p2:
        count = (word in p1) + (word in p3) + 1
        if count == 1:
            s2 += 3
        elif count == 2:
            s2 += 1

    for word in p3:
        count = (word in p1) + (word in p2) + 1
        if count == 1:
            s3 += 3
        elif count == 2:
            s3 += 1

    print(f"{s1} {s2} {s3}")

    num_tests -= 1
