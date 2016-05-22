class Range:
    def __init__(self, _min, _max):
        self.min = _min
        self.max = _max

    def __str__(self):
        return str(self.min) + "-" + str(self.max)

    def __repr__(self):
        return str(self)

    def get_max(self):
        return self.max

    def get_min(self):
        return self.min

    def overlapping(self, other):
        if (self.get_min() < other.get_min() < self.get_max()) \
                or (self.get_min() < other.get_max() < self.get_max()) or \
                (other.get_min() < self.get_min() < other.get_max()) \
                or (other.get_min() < self.get_max() < other.get_max()):
            return True
        return False

    def merge(self, other):
        mmin = min(self.get_min(), other.get_min())
        mmax = max(self.get_max(), other.get_max())
        res = Range(mmin, mmax)
        return res

    def compare(self, other):
        return cmp(self.min, other.min)

    @staticmethod
    def fix_array(index, array, retry=False):
        if index > len(array):
            return False
        try:
            left = array[index]
            right = array[index + 1]
        except Exception, e:
            raise IndexError("fart")
        if left.overlapping(right):
            array.remove(left)
            array.remove(right)
            array.insert(index, left.merge(right))
            if retry:
                return Range.fix_array(index, array, retry=True)
            return True


def merge(array1, array2):
    result = []
    result.extend(array1)
    result.extend(array2)
    result = sorted(result, cmp=Range.compare)
    index = 0
    while True:
        try:
            Range.fix_array(index, result, True)
            index += 1
        except IndexError, e:
            return result


if __name__ == '__main__':
    arr1 = [Range(3, 11), Range(17, 25), Range(58, 73)]
    arr2 = [Range(6, 18), Range(40, 47)]
    print (merge(arr1, arr2))

    arr1 = [Range(8, 13), Range(21, 32), Range(45, 60)]
    arr2 = [Range(2, 9), Range(25, 46)]
    print (merge(arr1, arr2))

    arr1 = [Range(1, 12), Range(26, 32), Range(51, 82)]
    arr2 = [Range(9, 24), Range(49, 60), Range(75, 98)]
    print (merge(arr1, arr2))