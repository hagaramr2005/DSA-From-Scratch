#include <iostream>
using namespace std;

int main() {

    int capacity = 1;
    int size = 0;

    int* arr = new int[capacity];

    for(int value = 1; value <= 20; value++) {

        if(size == capacity) {

            cout << "\nResize "
                 << capacity
                 << " -> "
                 << capacity * 2
                 << endl;

            int* temp = new int[capacity * 2];

            for(int i = 0; i < size; i++)
                temp[i] = arr[i];

            delete[] arr;

            arr = temp;

            capacity *= 2;
        }

        arr[size++] = value;

        cout << "Insert "
             << value
             << " | Size = "
             << size
             << " | Capacity = "
             << capacity
             << endl;
    }

    delete[] arr;
}
