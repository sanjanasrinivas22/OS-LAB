#include <stdio.h>
#include <stdbool.h>

#define MAX_P 10  // max processes
#define MAX_R 10  // max resources

int main() {
    int n, m; // n = number of processes, m = number of resources
    int allocation[MAX_P][MAX_R], max[MAX_P][MAX_R], need[MAX_P][MAX_R], available[MAX_R];
    bool finished[MAX_P] = {false};
    int safeSeq[MAX_P], count = 0;

    printf("Enter number of processes: ");
    scanf("%d", &n);
    printf("Enter number of resources: ");
    scanf("%d", &m);

    printf("Enter allocation matrix (%d x %d):\n", n, m);
    for(int i = 0; i < n; i++)
        for(int j = 0; j < m; j++)
            scanf("%d", &allocation[i][j]);

    printf("Enter max matrix (%d x %d):\n", n, m);
    for(int i = 0; i < n; i++)
        for(int j = 0; j < m; j++)
            scanf("%d", &max[i][j]);

    printf("Enter available resources (%d values): ", m);
    for(int j = 0; j < m; j++)
        scanf("%d", &available[j]);

    // Calculate need matrix
    for(int i = 0; i < n; i++)
        for(int j = 0; j < m; j++)
            need[i][j] = max[i][j] - allocation[i][j];

    // Safety Algorithm
    while(count < n) {
        bool found = false;
        for(int i = 0; i < n; i++) {
            if(!finished[i]) {
                bool canRun = true;
                for(int j = 0; j < m; j++) {
                    if(need[i][j] > available[j]) {
                        canRun = false;
                        break;
                    }
                }
                if(canRun) {
                    for(int j = 0; j < m; j++)
                        available[j] += allocation[i][j];
                    safeSeq[count++] = i;
                    finished[i] = true;
                    found = true;
                }
            }
        }
        if(!found) {
            printf("System is not in a safe state.\n");
            return 1;
        }
    }

    printf("System is in a safe state.\nSafe sequence: ");
    for(int i = 0; i < n; i++)
        printf("P%d ", safeSeq[i]);
    printf("\n");

    return 0;
}
