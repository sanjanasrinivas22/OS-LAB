#include <stdio.h>
#include <stdlib.h>

#define MAX 10

typedef struct {
    int id, arrival, burst, priority, remaining, completion, waiting, turnaround, started;
} Process;

void sortByArrival(Process p[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (p[j].arrival > p[j + 1].arrival) {
                Process temp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = temp;
            }
        }
    }
}

// **Non-Preemptive Priority Scheduling**
void nonPreemptivePriority(Process p[], int n) {
    sortByArrival(p, n);
    int time = 0, completed = 0;
    
    while (completed < n) {
        int index = -1, highestPriority = 9999;
        
        for (int i = 0; i < n; i++) {
            if (p[i].arrival <= time && p[i].completion == 0) {
                if (p[i].priority < highestPriority) {
                    highestPriority = p[i].priority;
                    index = i;
                }
            }
        }
        
        if (index != -1) {
            time += p[index].burst;
            p[index].completion = time;
            p[index].turnaround = p[index].completion - p[index].arrival;
            p[index].waiting = p[index].turnaround - p[index].burst;
            completed++;
        } else {
            time++;
        }
    }
}

// **Preemptive Priority Scheduling**
void preemptivePriority(Process p[], int n) {
    sortByArrival(p, n);
    int time = 0, completed = 0, lastExec = -1;
    
    while (completed < n) {
        int index = -1, highestPriority = 9999;
        
        for (int i = 0; i < n; i++) {
            if (p[i].arrival <= time && p[i].remaining > 0) {
                if (p[i].priority < highestPriority) {
                    highestPriority = p[i].priority;
                    index = i;
                }
            }
        }
        
        if (index != -1) {
            if (lastExec != index) {
                lastExec = index;
            }
            p[index].remaining--;
            time++;

            if (p[index].remaining == 0) {
                p[index].completion = time;
                p[index].turnaround = p[index].completion - p[index].arrival;
                p[index].waiting = p[index].turnaround - p[index].burst;
                completed++;
            }
        } else {
            time++;
        }
    }
}

// **Print Results**
void printResults(Process p[], int n) {
    printf("\nProcess\tArrival\tBurst\tPriority\tCompletion\tTurnaround\tWaiting\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t\t%d\t\t%d\t\t%d\n", p[i].id, p[i].arrival, p[i].burst, p[i].priority, 
               p[i].completion, p[i].turnaround, p[i].waiting);
    }
}

int main() {
    int n, choice;
    Process p[MAX];

    printf("Enter number of processes: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        p[i].id = i + 1;
        printf("Enter arrival time, burst time, and priority for process P%d: ", i + 1);
        scanf("%d %d %d", &p[i].arrival, &p[i].burst, &p[i].priority);
        p[i].remaining = p[i].burst;
        p[i].completion = 0;
        p[i].waiting = 0;
        p[i].turnaround = 0;
    }

    printf("\nChoose Scheduling Type:\n1. Non-Preemptive Priority\n2. Preemptive Priority\nEnter choice: ");
    scanf("%d", &choice);

    if (choice == 1) {
        nonPreemptivePriority(p, n);
    } else if (choice == 2) {
        preemptivePriority(p, n);
    } else {
        printf("Invalid choice! Exiting.\n");
        return 0;
    }

    printResults(p, n);
    return 0;
}
