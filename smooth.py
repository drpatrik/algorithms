from typing import List


def average(x: List) -> float:
    return sum(x) / len(x)


def smooth_a(x: List, n: int) -> List:
    x = ([x[0] for i in range(n)]) + x
    x = x + ([x[-1] for i in range(n)])
    return ([average(x[i:2 * n + 1 + i]) for i in range(len(x) - (2 * n))])


def smooth_b(x: List, n: int) -> List:
    left_edge_case = ([average(x[0:n + 1 + i])
                       for i in range(n)]) if len(x) > 1 else x
    return left_edge_case + ([average(x[i:2 * n + 1 + i])
                              for i in range(len(x) - n)])


x = [1, 2, 6, 4, 5, 0, 1, 2]
print("smooth_a(x, 1): ", smooth_a(x, 1))
print("smooth_a(x, 2): ", smooth_a(x, 2))
print("smooth_b(x, 1): ", smooth_b(x, 1))
print("smooth_b(x, 2): ", smooth_b(x, 2))
