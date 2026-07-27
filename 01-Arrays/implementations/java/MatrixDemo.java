public class AmortizedAnalysisDemo {

    public static void main(String[] args) {

        DynamicArray arr = new DynamicArray();

        for (int i = 1; i <= 20; i++) {

            arr.add(i);

            System.out.printf(
                    "Insert %-2d | Size = %-2d | Capacity = %-2d%n",
                    i,
                    arr.size(),
                    arr.capacity()
            );
        }
    }
}
