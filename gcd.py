# Patrik Tennberg, 2015

import sys


def gcd(a, b):
    if (b == 0):
        return a
    return gcd(b, a % b)


print gcd(int(sys.argv[1]), int(sys.argv[2]))
