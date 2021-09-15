import inspect


def int_to_bin(c):
    c, sign = (abs(c), "-") if (c < 0) else (c, "")

    if (c == 0):
        return "0" if (len(inspect.stack(0)) == 2) else ""

    return sign + int_to_bin(c >> 1) + ['0', '1'][c & 1]


print(int_to_bin(0))  # 0
print(int_to_bin(1))  # 1
print(int_to_bin(2))  # 10
print(int_to_bin(13))  # 1101
print(int_to_bin(27))  # 11011
print(int_to_bin(-27))  # -11011
print(int_to_bin(255))  # 11111111
