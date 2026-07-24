#ifndef DYNAMIC_ARRAY_H
#define DYNAMIC_ARRAY_H

typedef struct
{
    int *data;
    int size;
    int capacity;
} DynamicArray;

void initArray(DynamicArray *arr, int capacity);

void freeArray(DynamicArray *arr);

int isEmpty(DynamicArray *arr);

void append(DynamicArray *arr, int value);

void insertAt(DynamicArray *arr, int index, int value);

void deleteAt(DynamicArray *arr, int index);

int search(DynamicArray *arr, int value);

void update(DynamicArray *arr, int index, int value);

void printArray(DynamicArray *arr);

#endif
