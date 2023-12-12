//
// Created by Theon on 2023/7/27.
//
#include <stdio.h>

int binarySearch(int arr[], int l, int r, int x);

int main() {
    int arr[] = {2, 3, 4, 10, 40};
    int arr_size = sizeof(arr) / sizeof(arr[0]);
    int x = 3;
    int result = binarySearch(arr, 0, arr_size - 1, x);

    (result < 0) ? printf("Element is not present in array") : printf("Element is present at index %d", result);

    return 0;
}

int binarySearch(int arr[], int l, int r, int x) {
    if (l <= r) {
        int m = l + (r - l) / 2;
        if (arr[m] == x) {
            return m;
        }

        if (arr[m] < x) {
            return binarySearch(arr, m + 1, r, x);
        } else  {
            return binarySearch(arr, l, m - 1, x);
        }
    }
    return -1;
}
