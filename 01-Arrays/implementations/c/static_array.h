#ifndef STATIC_ARRAY_H
#define STATIC_ARRAY_H

#define MAX_SIZE 10

typedef struct
{
    int data[MAX_SIZE];
    int size;
} StaticArray;

void initArray(StaticArray *arr);

int isEmpty(StaticArray *arr);

int isFull(StaticArray *arr);

void insertEnd(StaticArray *arr, int value);

void insertAt(StaticArray *arr, int index, int value);

void deleteAt(StaticArray *arr, int index);

int search(StaticArray *arr, int value);

void update(StaticArray *arr, int index, int value);

void printArray(StaticArray *arr);

#endif
