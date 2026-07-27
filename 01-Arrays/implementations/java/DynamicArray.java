public class DynamicArray {

    private int size;
    private int capacity;
    private int[] array;

    public DynamicArray() {
        capacity = 2;
        array = new int[capacity];
    }

    public void add(int value) {

        if (size == capacity) {
            grow();
        }

        array[size++] = value;
    }

    public int get(int index) {

        if (index >= size)
            throw new IndexOutOfBoundsException();

        return array[index];
    }

    public void set(int index, int value) {

        if (index >= size)
            throw new IndexOutOfBoundsException();

        array[index] = value;
    }

    public void insert(int index, int value) {

        if (size == capacity)
            grow();

        for (int i = size; i > index; i--) {
            array[i] = array[i - 1];
        }

        array[index] = value;
        size++;
    }

    public void remove(int index) {

        if (index >= size)
            throw new IndexOutOfBoundsException();

        for (int i = index; i < size - 1; i++) {
            array[i] = array[i + 1];
        }

        size--;

        if (size <= capacity / 4 && capacity > 2) {
            shrink();
        }
    }

    private void grow() {

        capacity *= 2;

        int[] newArray = new int[capacity];

        for (int i = 0; i < size; i++) {
            newArray[i] = array[i];
        }

        array = newArray;
    }

    private void shrink() {

        capacity /= 2;

        int[] newArray = new int[capacity];

        for (int i = 0; i < size; i++) {
            newArray[i] = array[i];
        }

        array = newArray;
    }

    public int size() {
        return size;
    }

    public int capacity() {
        return capacity;
    }

    public void print() {

        System.out.print("[ ");

        for (int i = 0; i < capacity; i++) {

            if (i < size)
                System.out.print(array[i] + " ");
            else
                System.out.print("_ ");
        }

        System.out.println("]");
    }
}
