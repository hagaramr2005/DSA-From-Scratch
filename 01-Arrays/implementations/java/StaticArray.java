public class StaticArray {

    private int[] array;

    public StaticArray(int capacity) {
        array = new int[capacity];
    }

    public void set(int index, int value) {
        array[index] = value;
    }

    public int get(int index) {
        return array[index];
    }

    public int size() {
        return array.length;
    }

    public void print() {
        System.out.print("[ ");

        for (int value : array) {
            System.out.print(value + " ");
        }

        System.out.println("]");
    }
}
