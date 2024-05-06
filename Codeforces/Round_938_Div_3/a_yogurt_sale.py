import sys


def calculate(n: int, a: int, b: int) -> int:
    """
    Equations - n_a + 2*n_b = n; Cost = a*n_a + b*n_b;
    Cost = a*n_a + b*(n - n_a)/2 = a*n_a + b*n/2 - b*n_a/2 = a*n_a + b*(n-n_a)/2 = (a-b/2)*n_a + n*b/2;
    if a >= b/2, then minimum cost = n*b/2.
    if a < b/2, then minmum cost = n*a.
    We need to account for odd n by adding 'a'.
    """
    return (b * (n // 2) + a * (n % 2)) if a >= b / 2 else (n * a)


num = int(sys.stdin.readline())
count = 0

for line in sys.stdin:
    n, a, b = line.strip().split()
    print(f"n: {n} c: {a} d: {b}")
    print(calculate(int(n), int(a), int(b)))
    count += 1
    if count == num:
        break
