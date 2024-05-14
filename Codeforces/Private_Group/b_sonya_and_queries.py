import sys
from collections import defaultdict

def calc_pattern(num):
    pattern, i = 0, 0
    while num > 0:
        pattern += (num % 2) * (10 ** i)
        num //= 10
        i += 1

    return pattern


n = int(sys.stdin.readline())
multiset = defaultdict(int)

while n > 0:
    op, num = sys.stdin.readline().strip().split()
    num = int(num)
    if op == "+":
        multiset[calc_pattern(num)] += 1
    elif op == "-":
        multiset[calc_pattern(num)] -= 1
    else:
        print(multiset[num])

    n -= 1
