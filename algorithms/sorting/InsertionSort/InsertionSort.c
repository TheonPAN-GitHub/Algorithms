//
// Created by Theon on 2023/6/3.
//
#include <math.h>
#include <stdio.h>

void insertionSort(int arr[], int n);

void printArray(int arr[], int n);


int main() {
    int arr[] = {12, 11, 13, 5, 6};
    int n = sizeof(arr) / sizeof(arr[0]);

    insertionSort(arr, n);
    printArray(arr, n);
}

void insertionSort(int arr[], int n){
    int i, j, key;
    for (i = 1; i < n; i++) {
        j = i - 1;
        key = arr[i];
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

void printArray(int arr[], int n){
    for (int i = 0; i < n; i ++){
        printf("%d ", arr[i]);
    }

    printf("\n");
}