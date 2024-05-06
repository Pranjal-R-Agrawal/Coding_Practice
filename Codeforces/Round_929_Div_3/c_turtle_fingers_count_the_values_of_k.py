import sys
import math

num_tests = int(sys.stdin.readline())

while num_tests:
    a, b, l = map(int, sys.stdin.readline().strip().split())

    k = set()

    for x in range(math.ceil(math.log(l, a)) + 1):
        for y in range(math.ceil(math.log(l / (a ** x), b)) + 1):
            if l % ((a ** x) * (b ** y)) == 0:
                k.add(l / ((a ** x) * (b ** y)))

    print(len(k))

    num_tests -= 1
