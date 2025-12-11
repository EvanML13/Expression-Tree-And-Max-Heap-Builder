#ifndef HEAP_H
#define HEAP_H

#include <stdio.h>
#include <stdlib.h>

#define ROWS 20
#define COLS 10

// Function To Compute The Key
int key(int row[]);
// Function To Swap Two Rows In The Array
void swapRows(int array[ROWS][COLS], int value1, int value2);
// Function To Percolate Down The Array
void percolateDown(int array[ROWS][COLS], int totalRows, int parentIndex);
// Function To Create The Max Heao
void createMaxHeap(int array[ROWS][COLS], int totalRows);

#endif HEAP_H
