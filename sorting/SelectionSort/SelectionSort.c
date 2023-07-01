//
// Created by Theon on 2023/7/1.
//

#include <stdio.h>

void selectionSort(int arr[], int n);

void printArray(int arr[], int n);

int main() {
    int array[] = {64, 25, 12, 22, 11};

    int n = sizeof(array) / sizeof(array[0]);

    selectionSort(array, n);

    printf("Sorted array: \n");
    printArray(array, n);
    return 0;

}

void printArray(int arr[], int n){
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

void swap(int *a, int *b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

void selectionSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int min_idx = i;
        for (int j = i + 1; j < n; j++){
            if (arr[min_idx] > arr[j]) {
                min_idx = j;
            }
        }
        if (min_idx != i) {
            swap(&arr[min_idx], &arr[i]);
        }
    }
}
