#include <iostream>
using namespace std;

int main() {

    int capacity = 4;

    int size = 4;

    int* arr = new int[capacity];

    for(int i=0;i<size;i++)
        arr[i]=i+1;

    cout<<"Before Resize\n";

    cout<<"Capacity = "<<capacity<<endl;

    for(int i=0;i<size;i++)
        cout<<arr[i]<<" ";

    cout<<"\n\n";

    capacity*=2;

    int* newArr = new int[capacity];

    for(int i=0;i<size;i++)
        newArr[i]=arr[i];

    delete[] arr;

    arr=newArr;

    arr[size]=5;

    size++;

    cout<<"After Resize\n";

    cout<<"Capacity = "<<capacity<<endl;

    for(int i=0;i<size;i++)
        cout<<arr[i]<<" ";

    delete[] arr;

}
