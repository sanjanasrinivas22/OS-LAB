#include <stdio.h>
#include <stdlib.h>

void first_fit(int block_sizes[], int m, int process_sizes[], int n) {
    int allocation[n];
   
    // Initially, no process is allocated memory
    for (int i = 0; i < n; i++) {
        allocation[i] = -1;
    }
   
    // Assign memory to processes using First Fit
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (block_sizes[j] >= process_sizes[i]) {
                allocation[i] = j;
                block_sizes[j] -= process_sizes[i];  // Reduce the available block size
                break;
            }
        }
    }
   
    // Print the allocation results
    printf("\nFirst-Fit Allocation:\n");
    for (int i = 0; i < n; i++) {
        if (allocation[i] != -1) {
            printf("Process %d allocated to Block %d\n", i + 1, allocation[i] + 1);
        } else {
            printf("Process %d could not be allocated memory\n", i + 1);
        }
    }
}

void best_fit(int block_sizes[], int m, int process_sizes[], int n) {
    int allocation[n];
   
    // Initially, no process is allocated memory
    for (int i = 0; i < n; i++) {
        allocation[i] = -1;
    }
   
    // Assign memory to processes using Best Fit
    for (int i = 0; i < n; i++) {
        int best_idx = -1;
        int min_diff = 9999;  // Initialize to a large number
       
        for (int j = 0; j < m; j++) {
            // Check if the block can accommodate the process
            if (block_sizes[j] >= process_sizes[i]) {
                int diff = block_sizes[j] - process_sizes[i];
                // Check if this block is the best fit
                if (diff < min_diff) {
                    min_diff = diff;
                    best_idx = j;
                }
            }
        }
       
        if (best_idx != -1) {
            allocation[i] = best_idx;
            block_sizes[best_idx] -= process_sizes[i];  // Reduce the available block size
        }
    }
   
    // Print the allocation results
    printf("\nBest-Fit Allocation:\n");
    for (int i = 0; i < n; i++) {
        if (allocation[i] != -1) {
            printf("Process %d allocated to Block %d\n", i + 1, allocation[i] + 1);
        } else {
            printf("Process %d could not be allocated memory\n", i + 1);
        }
    }
}

int main() {
    int m, n;

    // Input the number of memory blocks and processes
    printf("Enter the number of memory blocks: ");
    scanf("%d", &m);
    int block_sizes[m];
   
    printf("Enter the sizes of the memory blocks:\n");
    for (int i = 0; i < m; i++) {
        printf("Block %d size: ", i + 1);
        scanf("%d", &block_sizes[i]);
    }
   
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    int process_sizes[n];
   
    printf("Enter the sizes of the processes:\n");
    for (int i = 0; i < n; i++) {
        printf("Process %d size: ", i + 1);
        scanf("%d", &process_sizes[i]);
    }

    // Simulate First-Fit Allocation
    first_fit(block_sizes, m, process_sizes, n);
   
    // Reset memory blocks for Best-Fit
    int block_sizes_copy[m];
    for (int i = 0; i < m; i++) {
        block_sizes_copy[i] = block_sizes[i];
    }
   
    // Simulate Best-Fit Allocation
    best_fit(block_sizes_copy, m, process_sizes, n);
   
    return 0;
}