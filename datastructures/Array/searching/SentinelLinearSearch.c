//
// Created by Theon on 2023/7/26.
//
#include <stdio.h>

void sentinelLinearSearch(int arr[], int n, int key);

int main() {
    int arr[] = {10, 20, 180, 30, 60, 50, 110, 100, 70};
    int size = sizeof(arr) / sizeof(arr[0]);
    int key = 180;

    sentinelLinearSearch(arr, size, key);

    return 0;
}

void sentinelLinearSearch(int arr[], int n, int key) {
    int lastItem = arr[n - 1];
    arr[n - 1] = key;

    int i = 0;
    while (arr[i] != key) {
        i++;
    }
    arr[n - 1] = lastItem;
    if (i < n - 1 || arr[n - 1] == key) {
        printf("%d is presented at index %d", key, i);
    } else {
        printf("Element not found");
    }
}
