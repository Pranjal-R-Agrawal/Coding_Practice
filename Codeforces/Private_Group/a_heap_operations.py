import sys, math


class BinaryHeap:
    def __init__(self):
        self.arr = list()
        self.len = 0

    def insert(self, x):
        self.arr.insert(self.len, x)
        self.len += 1
        i = self.len - 1
        while i > 0:
            if self.arr[i] < self.arr[(i - 1) // 2]:
                self.arr[i], self.arr[(i - 1) // 2] = self.arr[(i - 1) // 2], self.arr[i]
                i = (i - 1) // 2
            else:
                break

    def getMin(self):
        return math.inf if self.is_empty() else self.arr[0]

    def removeMin(self):
        self.arr[0] = self.arr[self.len - 1]
        self.arr.pop()
        self.len -= 1

        i = 0
        while 2 * i + 1 < self.len:
            li, ri = 2 * i + 1, 2 * i + 2
            if self.arr[li] < self.arr[i] and (ri >= self.len or self.arr[li] <= self.arr[ri]):
                self.arr[li], self.arr[i] = self.arr[i], self.arr[li]
                i = li
            elif ri < self.len and self.arr[ri] < self.arr[i]:
                self.arr[ri], self.arr[i] = self.arr[i], self.arr[ri]
                i = ri
            else:
                break

    def is_empty(self):
        return self.len == 0

    def __contains__(self, item):
        return item in self.arr


num_ops = int(sys.stdin.readline())
operations = list()
num_operations = 0
heap = BinaryHeap()

while num_ops:
    op = list(sys.stdin.readline().strip().split())
    if op[0] == "insert":
        heap.insert(int(op[1]))
        num_operations += 1
        operations.append(" ".join(op))

    elif op[0] == "getMin":
        while int(op[1]) > heap.getMin():
            heap.removeMin()
            operations.append("removeMin")
            num_operations += 1

        if int(op[1]) < heap.getMin():
            heap.insert(int(op[1]))
            operations.append(f"insert {int(op[1])}")
            num_operations += 1

        operations.append(" ".join(op))
        num_operations += 1

    else:
        if heap.is_empty():
            heap.insert(1)
            operations.append(f"insert 1")
            num_operations += 1

        heap.removeMin()
        operations.append(" ".join(op))
        num_operations += 1

    num_ops -= 1


print(num_operations)
for op in operations:
    print(op)
