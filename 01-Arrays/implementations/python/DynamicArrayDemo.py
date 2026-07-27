from DynamicArray import DynamicArray

arr = DynamicArray()

for i in range(1, 11):

    arr.add(i)

    print("----------------")
    print("Added:", i)

    arr.display()

print("\nInsert 100 at index 2")

arr.insert(2, 100)

arr.display()

print("\nDelete index 0")

arr.remove(0)

arr.display()
