#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "bubble_sorts.h"

typedef void (*sort_func)(int*, int);

double get_time() {
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return ts.tv_sec + ts.tv_nsec / 1e9;
}

int is_sorted(int* arr, int n) {
    for (int i = 1; i < n; i++) {
        if (arr[i] < arr[i-1]) {
            return 0;
        }
    }
    return 1;
}

int* generate_random(int n) {
    int* arr = malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % n;
    }
    return arr;
}

int* generate_sorted(int n) {
    int* arr = malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        arr[i] = i;
    }
    return arr;
}

int* generate_nearly_sorted(int n) {
    int* arr = generate_sorted(n);
    int swaps = n / 20;  
    for (int i = 0; i < swaps; i++) {
        int idx1 = rand() % n;
        int idx2 = rand() % n;
        int temp = arr[idx1];
        arr[idx1] = arr[idx2];
        arr[idx2] = temp;
    }
    return arr;
}

int* generate_reverse(int n) {
    int* arr = malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        arr[i] = n - i;
    }
    return arr;
}

void run_test(sort_func func, const char* func_name, 
              int* data, int n, const char* data_type) {
    int* copy = malloc(n * sizeof(int));
    memcpy(copy, data, n * sizeof(int));
    
    double times[10];
    for (int i = 0; i < 10; i++) {
        memcpy(copy, data, n * sizeof(int));
        
        double start = get_time();
        func(copy, n);
        double end = get_time();
        
        times[i] = end - start;
    }
    
    if (!is_sorted(copy, n)) {
        fprintf(stderr, "ERROR: %s failed to sort %s data correctly!\n", 
                func_name, data_type);
    }
    
    for (int i = 0; i < 9; i++) {
        for (int j = i + 1; j < 10; j++) {
            if (times[i] > times[j]) {
                double tmp = times[i];
                times[i] = times[j];
                times[j] = tmp;
            }
        }
    }
    double median = times[5];
    
    printf("%-15s %-15s: %8.4f ms\n", 
           func_name, data_type, median * 1000);
    
    free(copy);
}

int main(int argc, char* argv[]) {
    int size = (argc > 1) ? atoi(argv[1]) : 5000;
    int which = (argc > 2) ? atoi(argv[2]) : -1;
    
    srand(42);
    
    printf("=== Bubble Sort Analysis (n=%d) ===\n", size);
    if (which >= 0) {
        printf("=== Testing single implementation ===\n");
    }
    printf("\n");
    
    sort_func sorts[] = {
        bubble_basic,
        bubble_early_stop,
        bubble_branchless,
        bubble_cocktail,
        standard_qsort
    };
    
    const char* names[] = {
        "Basic",
        "Early Stop",
        "Branchless",
        "Cocktail",
        "qsort (ref)"
    };
    
    struct {
        int* data;
        const char* name;
    } datasets[] = {
        { generate_random(size), "Random" },
        { generate_sorted(size), "Sorted" },
        { generate_nearly_sorted(size), "Nearly Sorted" },
        { generate_reverse(size), "Reverse" }
    };
    
    if (which == -1) {
        for (int i = 0; i < 5; i++) {
            printf("--- %s ---\n", names[i]);
            for (int j = 0; j < 4; j++) {
                run_test(sorts[i], names[i], 
                        datasets[j].data, size, datasets[j].name);
            }
            printf("\n");
        }
    } else {
        if (which < 0 || which >= 5) {
            fprintf(stderr, "Invalid implementation index (0-4)\n");
            return 1;
        }
        printf("--- %s ---\n", names[which]);
        for (int j = 0; j < 4; j++) {
            run_test(sorts[which], names[which],
                    datasets[j].data, size, datasets[j].name);
        }
        printf("\n");
    }
    
    for (int i = 0; i < 4; i++) {
        free(datasets[i].data);
    }
    
    return 0;
}