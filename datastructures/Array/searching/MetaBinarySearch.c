//
// Created by Theon on 2023/7/28.
//
#include <stdio.h>
#include <math.h>

int bsearch(int arr[], int n, int key_to_search);

int main() {
    int arr[] = {-2, 10, 100, 250, 32315};
    int size = sizeof(arr) / sizeof(arr[0]);
    printf("The index of found element is %d", bsearch(arr, size, -2));
}

int bsearch(int arr[], int n, int key_to_search) {
    int lg = log2(n - 1) + 1;
    int pos = 0;

    for (int i = lg; i >=0; i--) {
        if (arr[pos] == key_to_search) {
            return pos;
        }
        int new_pos = pos | (1 << i);
        if ((new_pos < n) && (arr[new_pos] <= key_to_search)) {
            pos = new_pos;
        }
    }

    return (arr[pos] == key_to_search) ? pos : -1;
}
