class StaticArray:

    def __init__(self, capacity):
        self.array = [0] * capacity

    def set(self, index, value):
        self.array[index] = value

    def get(self, index):
        return self.array[index]

    def size(self):
        return len(self.array)

    def print(self):
        print(self.array)


# Demo
if __name__ == "__main__":

    arr = StaticArray(5)

    arr.set(0, 10)
    arr.set(1, 20)
    arr.set(2, 30)

    arr.print()

    print("Size:", arr.size())
    print("Element at index 1:", arr.get(1))
