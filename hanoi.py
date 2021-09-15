def hanoi(f, t, h, n):
    if n == 1:
        return [f + "->" + t]
    moves = hanoi(f, h, t, n - 1) + hanoi(f, t, h, 1) + hanoi(h, t, f, n - 1)

    return moves


print(hanoi('f', 't', 'h', 2))
