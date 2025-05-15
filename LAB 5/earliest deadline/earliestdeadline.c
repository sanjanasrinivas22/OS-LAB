#include <stdio.h>
#include <stdlib.h>

// Define the Task structure
struct Task {
    int task_id;
    int arrival_time;
    int execution_time;
    int deadline;
    int remaining_time;
};

// Function to compare two tasks by their deadline
int compareDeadline(const void *a, const void *b) {
    struct Task *taskA = (struct Task *)a;
    struct Task *taskB = (struct Task *)b;
    return taskA->deadline - taskB->deadline;
}

// EDF scheduler function
void edfScheduler(struct Task tasks[], int num_tasks) {
    int current_time = 0;
    int completed_tasks = 0;

    while (completed_tasks < num_tasks) {
        // Sort tasks by deadline (Earliest Deadline First) each time
        qsort(tasks, num_tasks, sizeof(struct Task), compareDeadline);

        // Find the task with the earliest deadline that is ready to execute
        struct Task *current_task = NULL;
        for (int i = 0; i < num_tasks; i++) {
            if (tasks[i].arrival_time <= current_time && tasks[i].remaining_time > 0) {
                current_task = &tasks[i];
                break;
            }
        }

        if (current_task != NULL) {
            // Execute the task
            printf("Executing Task %d at time %d\n", current_task->task_id, current_time);
            current_time += current_task->execution_time;
            current_task->remaining_time = 0;  // Task is completed
            completed_tasks++;
            printf("Task %d completed at time %d\n", current_task->task_id, current_time);
        } else {
            // No tasks to execute, increment the time
            current_time++;
        }
    }
}

// Main function
int main() {
    int num_tasks;
    printf("Enter the number of tasks: ");
    scanf("%d", &num_tasks);

    struct Task tasks[num_tasks];

    // Input task details
    for (int i = 0; i < num_tasks; i++) {
        printf("Enter details for Task %d:\n", i + 1);
        tasks[i].task_id = i + 1;
        printf("Arrival time: ");
        scanf("%d", &tasks[i].arrival_time);
        printf("Execution time: ");
        scanf("%d", &tasks[i].execution_time);
        printf("Deadline: ");
        scanf("%d", &tasks[i].deadline);
        tasks[i].remaining_time = tasks[i].execution_time; // Initialize remaining time
    }

    printf("\nStarting EDF Scheduling...\n");
    edfScheduler(tasks, num_tasks);

    return 0;
}
