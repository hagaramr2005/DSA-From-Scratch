#include <iostream>
using namespace std;

class Vector {

private:

    int* data;

    int size;

    int capacity;

public:

    Vector() {

        size = 0;
        capacity = 1;

        data = new int[capacity];

    }

    void push_back(int value){

        if(size==capacity){

            capacity*=2;

            int* temp = new int[capacity];

            for(int i=0;i<size;i++)
                temp[i]=data[i];

            delete[] data;

            data=temp;

        }

        data[size]=value;

        size++;

    }

    void print(){

        cout<<"Size = "<<size<<endl;
        cout<<"Capacity = "<<capacity<<endl;

        for(int i=0;i<size;i++)
            cout<<data[i]<<" ";

        cout<<endl<<endl;

    }

    ~Vector(){

        delete[] data;

    }

};

int main(){

    Vector v;

    for(int i=1;i<=20;i++){

        v.push_back(i);

        v.print();

    }

}
