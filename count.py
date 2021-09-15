def count(lst, c):
    i = 0
    if (len(lst) == 0):
        return i
    e = lst[0]
    if (type(e) == list):
        i = i + count(e, c)
    elif (type(e) == int and c.count(e) > 0):
        i += c.count(e)
    i = i + count(lst[1:], c)

    return i


print(count([1, 3, 3, [5, [4, 3, 7], 3], 5, 3, 3], [3, 4]))
