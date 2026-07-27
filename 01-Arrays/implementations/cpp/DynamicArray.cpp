#include <iostream>
using namespace std;

int main() {

    int n;

    cout<<"Enter Size: ";
    cin>>n;

    int* arr = new int[n];

    for(int i=0;i<n;i++)
        arr[i]=i+1;

    cout<<"\nElements:\n";

    for(int i=0;i<n;i++)
        cout<<arr[i]<<" ";

    delete[] arr;

    arr = nullptr;

}
