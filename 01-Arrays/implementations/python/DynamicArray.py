class DynamicArray:

    def __init__(self):
        self.capacity = 2
        self.size = 0
        self.array = [None] * self.capacity

    def add(self, value):

        if self.size == self.capacity:
            self._grow()

        self.array[self.size] = value
        self.size += 1

    def insert(self, index, value):

        if self.size == self.capacity:
            self._grow()

        for i in range(self.size, index, -1):
            self.array[i] = self.array[i - 1]

        self.array[index] = value
        self.size += 1

    def remove(self, index):

        for i in range(index, self.size - 1):
            self.array[i] = self.array[i + 1]

        self.array[self.size - 1] = None
        self.size -= 1

        if self.size <= self.capacity // 4 and self.capacity > 2:
            self._shrink()

    def get(self, index):
        return self.array[index]

    def set(self, index, value):
        self.array[index] = value

    def _grow(self):

        self.capacity *= 2

        new_array = [None] * self.capacity

        for i in range(self.size):
            new_array[i] = self.array[i]

        self.array = new_array

    def _shrink(self):

        self.capacity //= 2

        new_array = [None] * self.capacity

        for i in range(self.size):
            new_array[i] = self.array[i]

        self.array = new_array

    def display(self):

        print(self.array)
        print(f"Size = {self.size}")
        print(f"Capacity = {self.capacity}")
