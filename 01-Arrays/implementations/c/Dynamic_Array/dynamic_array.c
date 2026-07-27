#include <stdio.h>
#include <stdlib.h>
#include "dynamic_array.h"

static void grow(DynamicArray *arr)
{
    arr->capacity *= 2;

    int *newData = (int *)malloc(arr->capacity * sizeof(int));

    for (int i = 0; i < arr->size; i++)
        newData[i] = arr->data[i];

    free(arr->data);

    arr->data = newData;
}

void initArray(DynamicArray *arr, int capacity)
{
    arr->size = 0;
    arr->capacity = capacity;
    arr->data = (int *)malloc(capacity * sizeof(int));
}

void freeArray(DynamicArray *arr)
{
    free(arr->data);
}

int isEmpty(DynamicArray *arr)
{
    return arr->size == 0;
}

void append(DynamicArray *arr, int value)
{
    if (arr->size == arr->capacity)
        grow(arr);

    arr->data[arr->size++] = value;
}

void insertAt(DynamicArray *arr, int index, int value)
{
    if (index < 0 || index > arr->size)
        return;

    if (arr->size == arr->capacity)
        grow(arr);

    for (int i = arr->size; i > index; i--)
        arr->data[i] = arr->data[i - 1];

    arr->data[index] = value;
    arr->size++;
}

void deleteAt(DynamicArray *arr, int index)
{
    if (index < 0 || index >= arr->size)
        return;

    for (int i = index; i < arr->size - 1; i++)
        arr->data[i] = arr->data[i + 1];

    arr->size--;
}

int search(DynamicArray *arr, int value)
{
    for (int i = 0; i < arr->size; i++)
    {
        if (arr->data[i] == value)
            return i;
    }

    return -1;
}

void update(DynamicArray *arr, int index, int value)
{
    if (index < 0 || index >= arr->size)
        return;

    arr->data[index] = value;
}

void printArray(DynamicArray *arr)
{
    printf("Size     : %d\n", arr->size);
    printf("Capacity : %d\n", arr->capacity);

    printf("[ ");

    for (int i = 0; i < arr->size; i++)
        printf("%d ", arr->data[i]);

    printf("]\n\n");
}
