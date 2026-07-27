public class DynamicArrayDemo {

    public static void main(String[] args) {

        DynamicArray arr = new DynamicArray();

        for (int i = 1; i <= 10; i++) {

            arr.add(i);

            System.out.println("----------------");
            System.out.println("Added: " + i);

            arr.print();

            System.out.println("Size = " + arr.size());
            System.out.println("Capacity = " + arr.capacity());
        }

        System.out.println("\nInsert 100 at index 2");

        arr.insert(2, 100);

        arr.print();

        System.out.println("\nRemove index 0");

        arr.remove(0);

        arr.print();
    }
}
