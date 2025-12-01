#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bubble_sorts.h"


void bubble_basic(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}
void bubble_early_stop(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int swapped = 0;
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                swapped = 1;
            }
        }
        if (!swapped) {
            break;
        }
    }
}


void bubble_branchless(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            int a = arr[j];
            int b = arr[j + 1];
            int should_swap = (a > b);
            arr[j] = should_swap ? b : a;
            arr[j + 1] = should_swap ? a : b;
        }
    }
}

void bubble_cocktail(int arr[], int n) {
    int left = 0;
    int right = n - 1;
    int swapped = 1;
    
    while (swapped && left < right) {
        swapped = 0;
        
        for (int i = left; i < right; i++) {
            if (arr[i] > arr[i + 1]) {
                int temp = arr[i];
                arr[i] = arr[i + 1];
                arr[i + 1] = temp;
                swapped = 1;
            }
        }
        right--;
        
        if (!swapped) break;
        
        swapped = 0;
        for (int i = right; i > left; i--) {
            if (arr[i] < arr[i - 1]) {
                int temp = arr[i];
                arr[i] = arr[i - 1];
                arr[i - 1] = temp;
                swapped = 1;
            }
        }
        left++;
    }
}

int compare_int(const void* a, const void* b) {
    return (*(int*)a - *(int*)b);
}

void standard_qsort(int arr[], int n) {
    qsort(arr, n, sizeof(int), compare_int);
}