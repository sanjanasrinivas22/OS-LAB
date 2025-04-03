#include <stdio.h>

void findWaitingTime(int processes[], int n, int bt[], int wt[], int quantum) {
    int rem_bt[n]; // Remaining burst times
    for (int i = 0; i < n; i++)
        rem_bt[i] = bt[i];

    int t = 0; // Current time

    while (1) {
        int done = 1;
        for (int i = 0; i < n; i++) {
            if (rem_bt[i] > 0) {
                done = 0; // There is still some process left

                if (rem_bt[i] > quantum) {
                    t += quantum;
                    rem_bt[i] -= quantum;
                } else {
                    t += rem_bt[i];
                    wt[i] = t - bt[i];
                    rem_bt[i] = 0;
                }
            }
        }
        if (done == 1)
            break;
    }
}

void findTurnAroundTime(int processes[], int n, int bt[], int wt[], int tat[]) {
    for (int i = 0; i < n; i++)
        tat[i] = bt[i] + wt[i];
}

void findAvgTime(int processes[], int n, int bt[], int quantum) {
    int wt[n], tat[n];

    findWaitingTime(processes, n, bt, wt, quantum);
    findTurnAroundTime(processes, n, bt, wt, tat);

    printf("\nTime Quantum = %d", quantum);
    printf("\nProcess\tBurst Time\tWaiting Time\tTurnaround Time\n");
    float total_wt = 0, total_tat = 0;
    for (int i = 0; i < n; i++) {
        total_wt += wt[i];
        total_tat += tat[i];
        printf("%d\t%d\t\t%d\t\t%d\n", i + 1, bt[i], wt[i], tat[i]);
    }

    printf("\nAverage Waiting Time = %.2f", total_wt / n);
    printf("\nAverage Turnaround Time = %.2f\n", total_tat / n);
}

int main() {
    int n;
    
    printf("Enter number of processes: ");
    scanf("%d", &n);
    
    int processes[n], burst_time[n];
    
    for (int i = 0; i < n; i++) {
        processes[i] = i + 1;
        printf("Enter burst time for process %d: ", i + 1);
        scanf("%d", &burst_time[i]);
    }

    int quantum_sizes[] = {1, 2, 4, 6}; // Different quantum values to experiment with
    int num_quantum = sizeof(quantum_sizes) / sizeof(quantum_sizes[0]);

    for (int i = 0; i < num_quantum; i++) {
        findAvgTime(processes, n, burst_time, quantum_sizes[i]);
    }

    return 0;
}