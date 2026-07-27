#include <stdio.h>
#include "static_array.h"

void initArray(StaticArray *arr)
{
    arr->size = 0;
}

int isEmpty(StaticArray *arr)
{
    return arr->size == 0;
}

int isFull(StaticArray *arr)
{
    return arr->size == MAX_SIZE;
}

void insertEnd(StaticArray *arr, int value)
{
    if (isFull(arr))
    {
        printf("Array is Full!\n");
        return;
    }

    arr->data[arr->size] = value;
    arr->size++;
}

void insertAt(StaticArray *arr, int index, int value)
{
    if (isFull(arr))
    {
        printf("Array is Full!\n");
        return;
    }

    if (index < 0 || index > arr->size)
    {
        printf("Invalid Index!\n");
        return;
    }

    for (int i = arr->size; i > index; i--)
    {
        arr->data[i] = arr->data[i - 1];
    }

    arr->data[index] = value;
    arr->size++;
}

void deleteAt(StaticArray *arr, int index)
{
    if (isEmpty(arr))
    {
        printf("Array is Empty!\n");
        return;
    }

    if (index < 0 || index >= arr->size)
    {
        printf("Invalid Index!\n");
        return;
    }

    for (int i = index; i < arr->size - 1; i++)
    {
        arr->data[i] = arr->data[i + 1];
    }

    arr->size--;
}

int search(StaticArray *arr, int value)
{
    for (int i = 0; i < arr->size; i++)
    {
        if (arr->data[i] == value)
            return i;
    }

    return -1;
}

void update(StaticArray *arr, int index, int value)
{
    if (index < 0 || index >= arr->size)
    {
        printf("Invalid Index!\n");
        return;
    }

    arr->data[index] = value;
}

void printArray(StaticArray *arr)
{
    printf("[ ");

    for (int i = 0; i < arr->size; i++)
    {
        printf("%d ", arr->data[i]);
    }

    printf("]\n");
}
