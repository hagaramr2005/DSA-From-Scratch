#include <iostream>
using namespace std;

int main() {

    const int SIZE = 5;

    int arr[SIZE] = {10,20,30,40,50};

    cout << "Array Elements:\n";

    for(int i=0;i<SIZE;i++)
        cout << arr[i] << " ";

    cout << "\n\n";

    cout << "Address of each element\n";

    for(int i=0;i<SIZE;i++)
        cout << "&arr[" << i << "] = " << &arr[i] << endl;

}
