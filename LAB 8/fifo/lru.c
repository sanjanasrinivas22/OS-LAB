#include <stdio.h>

int main() {
    int n, capacity;
    printf("Enter number of pages: ");
    scanf("%d", &n);

    int pages[n];
    printf("Enter the page reference string:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &pages[i]);
    }

    printf("Enter number of frames: ");
    scanf("%d", &capacity);

    int frames[capacity];
    int counter = 0;           // To track the current time (for LRU)
    int time[capacity];        // To track last used time of pages in frames
    int page_faults = 0;

    // Initialize frames and time arrays
    for (int i = 0; i < capacity; i++) {
        frames[i] = -1;
        time[i] = 0;
    }

    printf("\nPage Reference\tFrames\n");
    for (int i = 0; i < n; i++) {
        int page = pages[i];
        int found = 0;

        // Check if page is already in frames
        for (int j = 0; j < capacity; j++) {
            if (frames[j] == page) {
                found = 1;
                time[j] = ++counter;  // Update last used time
                break;
            }
        }

        if (!found) {
            // Page fault occurs
            page_faults++;

            // Find least recently used frame to replace
            int lru_index = 0;
            int min_time = time[0];
            for (int j = 1; j < capacity; j++) {
                if (time[j] < min_time) {
                    min_time = time[j];
                    lru_index = j;
                }
            }

            frames[lru_index] = page;
            time[lru_index] = ++counter;
        }

        // Print current frames
        printf("%d\t\t", page);
        for (int j = 0; j < capacity; j++) {
            if (frames[j] != -1) {
                printf("%d ", frames[j]);
            }
        }
        printf("\n");
    }

    printf("\nTotal Page Faults: %d\n", page_faults);

    return 0;
}

