#include <stdio.h>

#define MAX_FRAMES 10
#define MAX_PAGES 20

// Function to implement FIFO page replacement
void fifoPageReplacement(int pages[], int n, int frames) {
    int pageFrames[MAX_FRAMES];
    int pageFaults = 0;
    int index = 0;

    // Initialize frames with -1 (empty)
    for (int i = 0; i < frames; i++) {
        pageFrames[i] = -1;
    }

    // Iterate through the page reference string
    for (int i = 0; i < n; i++) {
        int page = pages[i];
        int found = 0;

        // Check if the page is already in any of the frames
        for (int j = 0; j < frames; j++) {
            if (pageFrames[j] == page) {
                found = 1;
                break;
            }
        }

        // If the page is not found in frames, it causes a page fault
        if (!found) {
            pageFaults++;

            // If there's space in the frame, insert the page
            if (index < frames) {
                pageFrames[index] = page;
                index++;
            } else {
                // If the frame is full, replace the oldest page (FIFO)
                for (int j = 0; j < frames - 1; j++) {
                    pageFrames[j] = pageFrames[j + 1];
                }
                pageFrames[frames - 1] = page;
            }
        }

        // Print the current page frames
        printf("After referencing page %d: ", page);
        for (int j = 0; j < frames; j++) {
            if (pageFrames[j] == -1) {
                printf(" - ");
            } else {
                printf("%d ", pageFrames[j]);
            }
        }
        printf("\n");
    }

    // Print the total number of page faults
    printf("Total page faults: %d\n", pageFaults);
}

int main() {
    int pages[MAX_PAGES];
    int n, frames;

    // Input number of pages and the reference string
    printf("Enter the number of pages: ");
    scanf("%d", &n);
    printf("Enter the page reference string:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &pages[i]);
    }

    // Input number of frames
    printf("Enter the number of frames: ");
    scanf("%d", &frames);

    // Call the FIFO page replacement function
    fifoPageReplacement(pages, n, frames);

    return 0;
}