from DynamicArray import DynamicArray

arr = DynamicArray()

for i in range(1, 21):

    arr.add(i)

    print(
        f"Insert {i:2d} | "
        f"Size = {arr.size:2d} | "
        f"Capacity = {arr.capacity:2d}"
    )
