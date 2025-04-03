#include <stdio.h>
#include <limits.h>

struct Process {
    int pid, at, bt, rt, ct, tat, wt;
};

void sortByArrival(struct Process p[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (p[j].at > p[j + 1].at) {
                struct Process temp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = temp;
            }
        }
    }
}

void sjfNonPreemptive(struct Process p[], int n) {
    sortByArrival(p, n);
    int completed = 0, currentTime = 0;
    
    while (completed < n) {
        int shortest = -1, minBT = 9999;
        
        for (int i = 0; i < n; i++) {
            if (p[i].at <= currentTime && p[i].bt < minBT && p[i].ct == 0) {
                minBT = p[i].bt;
                shortest = i;
            }
        }
        
        if (shortest == -1) {
            currentTime++;
        } else {
            currentTime += p[shortest].bt;
            p[shortest].ct = currentTime;
            p[shortest].tat = p[shortest].ct - p[shortest].at;
            p[shortest].wt = p[shortest].tat - p[shortest].bt;
            completed++;
        }
    }
}

void sjfPreemptive(struct Process p[], int n) {
    int completed = 0, currentTime = 0, shortest = -1, minRT;
    
    for (int i = 0; i < n; i++) {
        p[i].rt = p[i].bt;
    }
    
    while (completed < n) {
        shortest = -1;
        minRT = INT_MAX;

        for (int i = 0; i < n; i++) {
            if (p[i].at <= currentTime && p[i].rt > 0 && p[i].rt < minRT) {
                minRT = p[i].rt;
                shortest = i;
            }
        }

        if (shortest == -1) {
            currentTime++;
        } else {
            p[shortest].rt--;
            currentTime++;
            
            if (p[shortest].rt == 0) {
                p[shortest].ct = currentTime;
                p[shortest].tat = p[shortest].ct - p[shortest].at;
                p[shortest].wt = p[shortest].tat - p[shortest].bt;
                completed++;
            }
        }
    }
}

void display(struct Process p[], int n) {
    printf("\nPID\tAT\tBT\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\n", p[i].pid, p[i].at, p[i].bt, p[i].ct, p[i].tat, p[i].wt);
    }
}

int main() {
    int n, choice;
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    struct Process p[n];
    
    for (int i = 0; i < n; i++) {
        p[i].pid = i + 1;
        printf("Enter AT and BT for Process %d: ", i + 1);
        scanf("%d %d", &p[i].at, &p[i].bt);
        p[i].ct = 0; 
    }
    
    printf("Choose Scheduling Algorithm:\n1. Non-Preemptive SJF\n2. Preemptive SJF\nEnter choice: ");
    scanf("%d", &choice);
    
    if (choice == 1) {
        sjfNonPreemptive(p, n);
    } else if (choice == 2) {
        sjfPreemptive(p, n);
    } else {
        printf("Invalid choice!\n");
        return 1;
    }
    
    display(p, n);
    return 0;
}
