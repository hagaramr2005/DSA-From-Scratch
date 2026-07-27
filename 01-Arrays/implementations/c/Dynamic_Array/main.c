#include <stdio.h>
#include "dynamic_array.h"

int main()
{
    DynamicArray arr;

    initArray(&arr, 2);

    append(&arr, 10);
    append(&arr, 20);

    printArray(&arr);

    append(&arr, 30);

    printArray(&arr);

    append(&arr, 40);
    append(&arr, 50);

    printArray(&arr);

    insertAt(&arr, 2, 99);

    printArray(&arr);

    deleteAt(&arr, 1);

    printArray(&arr);

    update(&arr, 0, 500);

    printArray(&arr);

    printf("Index of 99 = %d\n", search(&arr, 99));

    freeArray(&arr);

    return 0;
}
