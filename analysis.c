#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bubble_sorts.h"

static long comparisons;
static long swaps;
static long memory_accesses;

void bubble_instrumented(int arr[], int n) {
    comparisons = 0;
    swaps = 0;
    memory_accesses = 0;
    
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            comparisons++;
            memory_accesses += 2;
            
            if (arr[j] > arr[j + 1]) {
                memory_accesses += 4;
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                swaps++;
            }
        }
    }
}

void bubble_early_instrumented(int arr[], int n) {
    comparisons = 0;
    swaps = 0;
    memory_accesses = 0;
    int passes = 0;
    
    for (int i = 0; i < n - 1; i++) {
        passes++;
        int swapped = 0;
        
        for (int j = 0; j < n - i - 1; j++) {
            comparisons++;
            memory_accesses += 2;
            
            if (arr[j] > arr[j + 1]) {
                memory_accesses += 4;
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                swaps++;
                swapped = 1;
            }
        }
        
        if (!swapped) {
            printf("  Early termination at pass %d (saved %d passes)\n", 
                   passes, n - 1 - passes);
            break;
        }
    }
}

void analyze_branch_prediction() {
    printf("=== Branch Prediction Impact ===\n\n");
    
    int n = 1000;
    int* arr = malloc(n * sizeof(int));
    
    srand(42);
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % n;
    }
    
    printf("Random data (unpredictable branches):\n");
    bubble_instrumented(arr, n);
    printf("  Comparisons: %ld\n", comparisons);
    printf("  Swaps: %ld (%.1f%% of comparisons)\n", 
           swaps, (double)swaps/comparisons * 100);
    printf("  Memory accesses: %ld\n", memory_accesses);
    printf("  Avg accesses per comparison: %.2f\n",
           (double)memory_accesses / comparisons);
    printf("  Expected branch misprediction: ~50%%\n\n");
    
    for (int i = 0; i < n; i++) {
        arr[i] = i;
    }
    
    printf("Sorted data (predictable branches):\n");
    bubble_early_instrumented(arr, n);
    printf("  Comparisons: %ld\n", comparisons);
    printf("  Swaps: %ld\n", swaps);
    printf("  Memory accesses: %ld\n", memory_accesses);
    printf("  Expected branch misprediction: ~0%%\n\n");
    
    free(arr);
}

void analyze_memory_locality() {
    printf("=== Memory Access Pattern ===\n\n");
    
    printf("Bubble sort memory characteristics:\n");
    printf("- Sequential access pattern (cache-friendly)\n");
    printf("- Working set: 2 adjacent elements at a time\n");
    printf("- Spatial locality: EXCELLENT (always adjacent)\n");
    printf("- Temporal locality: MODERATE (reuse in next iteration)\n\n");
    
    int cache_line = 64;
    int ints_per_line = cache_line / sizeof(int);
    
    printf("Cache line analysis:\n");
    printf("- Cache line size: %d bytes\n", cache_line);
    printf("- Integers per cache line: %d\n", ints_per_line);
    printf("- Each comparison touches at most 1 cache line\n");
    printf("- Prefetching helps due to sequential pattern\n\n");
}

void print_key_insights() {
    printf("=== Key CMPT 295 Insights ===\n\n");
    
    printf("1. BRANCH PREDICTION:\n");
    printf("   - Critical for bubble sort performance\n");
    printf("   - Random data: ~50%% misprediction rate\n");
    printf("   - Sorted data: ~0%% misprediction rate\n\n");
    
    printf("2. MEMORY ACCESS:\n");
    printf("   - ~6 memory accesses per swap (2 reads + 4 for swap)\n");
    printf("   - Sequential pattern = cache-friendly\n");
    printf("   - Performance bottleneck is branches, not cache\n\n");
    
    printf("3. COMPILER OPTIMIZATION:\n");
    printf("   - Limited effect due to data dependencies\n");
    printf("   - Cannot vectorize (each swap depends on previous)\n");
    printf("   - Branchless version may use cmov instructions\n\n");
    
    printf("4. ALGORITHMIC INSIGHTS:\n");
    printf("   - Early termination: O(n²) → O(n) for sorted data\n");
    printf("   - Cocktail sort: better for pipe-organ patterns\n");
    printf("   - Still 1000x slower than qsort for large random data\n");
}

int main() {
    analyze_branch_prediction();
    analyze_memory_locality();
    print_key_insights();
    return 0;
}