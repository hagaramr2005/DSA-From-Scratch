#include <stdio.h>
#include "static_array.h"

int main()
{
    StaticArray arr;

    initArray(&arr);

    insertEnd(&arr, 10);
    insertEnd(&arr, 20);
    insertEnd(&arr, 30);

    printArray(&arr);

    insertAt(&arr, 1, 15);

    printArray(&arr);

    deleteAt(&arr, 2);

    printArray(&arr);

    update(&arr, 1, 100);

    printArray(&arr);

    int index = search(&arr, 30);

    printf("30 Found at Index: %d\n", index);

    return 0;
}
