import sys


class Array:
    def __init__(self, arr):
        self.head = 0
        self.array = arr

    def peek(self):
        return -1 if self.head == len(self.array) else self.array[self.head]

    def commit(self):
        self.head += 1


class DataSet:
    def __init__(self):
        self.len = 0
        self.arrays = []

    def __len__(self):
        return self.len

    def append(self, arr):
        self.len += len(arr)
        self.arrays.append(Array(arr))

    def next(self):
        min = -1
        obj = None
        for arr in self.arrays:
            if (min == -1 or arr.peek() <= min):
                min = arr.peek()
                obj = arr
        assert obj is not None
        obj.commit()

        return min

    def median(self):
        duplicates = 0
        current_value = 0
        for i in range(int(self.len / 2)):
            next_value = self.next()
            duplicates += (current_value == next_value)
            current_value = next_value

        return ((current_value + self.next()) / 2 if self.len % 2 == 0
                else self.next()), duplicates


def read_files(argv):
    data_set = DataSet()

    for arg in argv:
        arr = []
        f = open(arg, "r")
        f.readline()  # Skip N
        for line in f.readlines():
            arr.append(int(line))
        f.close()
        data_set.append(arr)

    return data_set


if __name__ == "__main__":
    data_set = read_files(sys.argv[1:])
    print("Median, n duplicates = {}, size = {}".format(data_set.median(),
                                                        len(data_set)))
