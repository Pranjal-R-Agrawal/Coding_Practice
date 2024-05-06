import sys


n, k = map(int, sys.stdin.readline().strip().split())
entrances = sys.stdin.readline().strip()
last_entrance = dict()
open = dict()
num_open = 0

for i, entrance in enumerate(entrances):
    last_entrance[entrance] = i

for i, entrance in enumerate(entrances):
    if entrance not in open or not open[entrance]:
        open[entrance] = True
        num_open += 1
        if num_open > k:
            print("YES")
            break

    if i == last_entrance[entrance]:
        open[entrance] = False
        num_open -= 1

if num_open <= k:
    print("NO")
