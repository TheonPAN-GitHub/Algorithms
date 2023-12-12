//
// Created by Theon on 2023/7/24.
//
#include <stdio.h>
#include <stdlib.h>

void printArray(int arr[], int n);
void mergeSort(int arr[], int l, int r);
void merge(int arr[], int l, int m, int r);
int level = 1;
int main() {
    int arr[] = {12, 11, 13, 5, 6, 7};
    int arr_size = sizeof(arr) /sizeof(arr[0]);

    printf("Given array is \n");
    printArray(arr, arr_size);

    printf("Begin merge sorting......\n");
    mergeSort(arr, 0, arr_size - 1);
    printf("End......\n");

    printf("\nSorted array is \n");
    printArray(arr, arr_size);

    return 0;
}

void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

void printArrayWithin(int arr[], int begin, int end) {
    printf("[");
    int i = begin;
    while (i < end + 1) {
        printf("%d ", arr[i]);
        i++;
    }
    printf("]\n");
}

void mergeSort(int arr[], int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
        printf("Level %d :\n", level);
        printf("l: %d, m: %d, r:%d\n", l, m, r);
        printf("left array:");
        printArrayWithin(arr, l, m);
        printf("\n");
        printf("right array:");
        printArrayWithin(arr, m + 1, r);
        printf("\n");
        level++;
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);

        merge(arr, l, m, r);
    }
    else {
        printf("Level %d end:\n", level);
        printf("l: %d, r:%d\n", l, r);
    }
}

void merge(int arr[], int l, int m, int r) {
    int i, j, k;
    int n_left = m - l + 1;
    int n_right = r - m;
    int L[n_left], R[n_right];

    for (i = 0; i < n_left; i++) {
        L[i] = arr[l + i];
    }

    for (j = 0; j < n_right; j++) {
        R[j] = arr[m + 1 + j];
    }

    i = 0;
    j = 0;
    k = l;
    while (i < n_left && j < n_right) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        }
        else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
    while (i < n_left) {
        arr[k] = L[i];
        i++;
        k++;
    }
    while (j < n_right) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

