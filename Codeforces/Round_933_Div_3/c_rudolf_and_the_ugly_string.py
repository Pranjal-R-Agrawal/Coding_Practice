import sys

num_tests = int(sys.stdin.readline())

while num_tests:
    len = int(sys.stdin.readline())
    str = sys.stdin.readline().strip()
    count = 0
    index = 0

    while index <= len - 3:
        if str[index] == 'm' and str[index + 1] == 'a' and str[index + 2] == 'p':
            count += 1
            index += 3
        elif str[index] == 'p' and str[index + 1] == 'i' and str[index + 2] == 'e':
            count += 1
            index += 3
        else:
            index += 1

    print(count)

    num_tests -= 1
