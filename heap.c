#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

/*
   Heap is used mainly for sorting and priority queue implementation.

   Property:
    1. parent node value should be greater than it's child nodes
    2. it should be complete binary tree.
   
   1. Heap indexing always starts from 1 to n.
   2. Normal arr[0] can't consider here. 
   3. It's a pure array based implementation.
   4. Deletion of any element is possible,
      but deleteing of root element makes sense
*/

void printpeek(int *arr, int hsize)
{
    if(hsize == 0) {
        puts("heapQ empty, Nothing to do");
        return;
    }
    printf("peek element : %4d \n", arr[1]);
}

void display(int *arr, int size)
{
    int i = 0;
    if(size == 0) {
        puts("heapQ empty, nothing to print");
        return;
    }
    for(i=1; i<=size; i++)
        printf("%4d", arr[i]);
    puts("");
}

void restoreUP(int *arr, int size)
{
    int key, par;
    key = arr[size];
    par = size / 2;

    while(par>=1 && arr[par]<key) { // to perorm max heap
    //while(par>=1 && arr[par]>key) { // to perfrom min heap
        arr[size] = arr[par];
        size = par;
        par = size / 2;
    }
    arr[size] = key;
}

void insert(int *arr, int number, int *hsize)
{
    if(*hsize == 99) {
        puts("Heap Q size if full");
        return;
    }
    (*hsize)++;
    arr[*hsize] = number;

    // to perform max heap operation
    restoreUP(arr, *hsize);

    // display after each restoring operation
    display(arr, *hsize);
}

void restoreDOWN(int *arr, int i, int size)
{
    int num, lchild, rchild;

    num = arr[size];
    lchild = 2 * i; 
    rchild = (2 * i) + 1; 

    while(rchild <= size) {
        if(num >= arr[lchild] && num >= arr[rchild]) {
            arr[i] = num;
            return;
        }
        else if(arr[lchild] < arr[rchild]) {
            arr[i] = arr[rchild];
            i = rchild;
        }
        else {
            arr[i] = arr[lchild];
            i = lchild;
        }
        lchild = (2 * i);
        rchild = (2 * i) + 1;
    }

    arr[i] = num;
}

void deleteroot(int *arr, int *hsize)
{
    int max;
    
    if(*hsize == 0) {
        puts("Deletion is not possible");
        return;
    }

    printf("Deleted item is : %d \n", arr[1]);
    arr[1] = arr[*hsize];
    (*hsize)--;

    // build the heap property (1) again
    restoreDOWN(arr, 1, *hsize);

    // display after performing delete operation
    display(arr, *hsize);
}

int main(int argc, char **argv)
{
    int heapq[100], hsize=0, number, choice;

    while(1) {
        puts("0. exit");
        puts("1. insert");
        puts("2. display");
        puts("3. find min/max based on min/max heapq");
        puts("4. delete root");

        printf("Enter your choice : ");
        scanf("%d", &choice);
        system("clear");
        switch(choice){
            case 0: 
                    puts("Exiting from program");
                    exit(1);
            case 1: 
                    printf("Enter a number to insert in heapQ : ");
                    scanf("%d", &number);
                    insert(heapq, number, &hsize);
                    break;
            case 2:
                    display(heapq, hsize);
                    break;
            case 3:
                    printpeek(heapq, hsize);
                    break;
            case 4:
                    deleteroot(heapq, &hsize);
                    break;
        }
    }
    return 0;
}
