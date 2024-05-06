import sys

num_tests = int(sys.stdin.readline())

while num_tests:
    n = int(sys.stdin.readline().strip())
    a = list(map(int, sys.stdin.readline().strip().split()))

    # The first operation can be used to collect all the negative terms together
    # The second operation can be used to negate all the collected negative terms
    total_sum = 0
    element_mod_3_eq_1_exists = False
    for i in range(n):
        total_sum += a[i]
        if a[i] % 3 == 1:
            element_mod_3_eq_1_exists = True

    r = total_sum % 3
    if r == 0:
        # Already divisible
        num_moves = 0
    elif r == 1:
        # Either add 1 to 2 elements (2 moves) or remove an element e s.t. (e % 3 == 1) if it exists (1 move)
        num_moves = 2 - element_mod_3_eq_1_exists
        pass
    else:
        # At least 1 move needs to be performed. Adding 1 to an element is guaranteed to work.
        num_moves = 1

    print(num_moves)

    num_tests -= 1
