#include "../src/heap.h"

int main(void){

    // Opens The f.dat File In Read Mode 
    FILE *fptr = fopen("f.dat", "r");
    if(fptr == NULL){
        fprintf(stderr, "Error: failed to open the file\n");
        return 1;    
    }

    int array[ROWS][COLS];
    int numbersRead = 0;

    // Itterates Through All 200 Integers In The File
    for(int i = 0; i < ROWS; i++){
        for(int j = 0; j < COLS; j++){

            // Reads The Given Integer In The File And Prints An Error If It Could Not Be Read
            if(fscanf(fptr, "%d", &array[i][j]) != 1){
                fprintf(stderr, "Error: syntax error.\n");
                fclose(fptr);
                return 1; 
            }
            numbersRead++;
        }
    }

    fclose(fptr);

    // Builds The Max Heap
    createMaxHeap(array, ROWS);

    // Print The Heapified Array To The Terminal
    for(int i = 0; i < ROWS; i++){
        for(int j = 0; j < COLS; j++){
            printf("%02d ", array[i][j]);
        }
        printf("\n");
    }

    return 0;
}

int key(int row[]){
    // Returns The Sum Of The First Three Integers
    return row[0] + row[1] + row[2];
}

void swapRows(int array[ROWS][COLS], int rowA, int rowB){

    // Swaps Two Rows In The Array
    for(int col=0; col < COLS; col++){
        int temp = array[rowA][col];
        array[rowA][col] = array[rowB][col];
        array[rowB][col] = temp;
    }
}

void percolateDown(int array[ROWS][COLS], int totalRows, int parentIndex){

    int largestIndex = parentIndex;

    // Formula To Find The Left Childs Index 
    int leftChildIndex = 2 * parentIndex + 1;
    // Formula To Find The Right Childs Index
    int rightChildIndex = 2 * parentIndex + 2;

    // Gets The Key For The Parent 
    int parentKey = key(array[largestIndex]);

    // Ensures The Left Child Exists
    if(leftChildIndex < totalRows){

        // Gets The Left Key
        int leftKey = key(array[leftChildIndex]); 

        // Moves The Left Key Up If It Is Larger Than The Parent Key
        if(leftKey > parentKey){
            largestIndex = leftChildIndex;
            parentKey = leftKey;
        }
    }

    // Ensures The Right Child Exists
    if(rightChildIndex < totalRows){
        
        // Gets The Right Key
        int rightKey = key(array[rightChildIndex]);

        // Moves The Right Key Up If It Is Larger Than The Parent Key
        if(rightKey > parentKey){
            largestIndex = rightChildIndex;
        }
    }

    // If The Parent Is Not The Largest Swap And Continue Down The Heap
    if(largestIndex != parentIndex){
        swapRows(array, parentIndex, largestIndex);
        percolateDown(array, totalRows, largestIndex);
    }
}

void createMaxHeap(int array[ROWS][COLS], int totalRows){

    // Starts From The Last Internal Node And Moves Upwards Towards The Root
    for(int i = (totalRows / 2) -1 ; i >= 0; i--){
        // Percolates Down Each Node
        percolateDown(array, totalRows, i);
    }
}
