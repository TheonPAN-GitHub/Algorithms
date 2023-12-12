//
// Created by Theon on 2023/7/26.
//
#include <stdio.h>

int search(int arr[], int n, int key);

int main() {
    int arr[] = {2, 3, 10, 40};
    int key = 10;
    int size = sizeof(arr) / sizeof(arr[0]);
    int result = search(arr, size, key);
    (result == -1) ?
    printf("Element is not presented in array") :
    printf("Element is presented at index %d", result);

    return 0;
}

int search(int arr[], int n, int key) {
    int result = -1;
    for (int i = 0; i < n; i++) {
        if (arr[i] == key) {
            result = i;
            break;
        }
    }
    return result;
}
