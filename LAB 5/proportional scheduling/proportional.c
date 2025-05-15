#include <stdio.h>

// Define the Task structure
struct Task {
    int task_id;
    int execution_time;
    int weight;
    int remaining_time;
};

// Function to calculate the total weight of all tasks
int total_weight(struct Task tasks[], int num_tasks) {
    int total = 0;
    for (int i = 0; i < num_tasks; i++) {
        total += tasks[i].weight;
    }
    return total;
}

// Proportional scheduler function
void proportional_scheduler(struct Task tasks[], int num_tasks) {
    int total = total_weight(tasks, num_tasks);
    int current_time = 0;
   
    // While all tasks are not completed
    while (1) {
        int all_done = 1; // Flag to check if all tasks are completed
       
        for (int i = 0; i < num_tasks; i++) {
            if (tasks[i].remaining_time > 0) {
                all_done = 0; // If there's any task with remaining time, set flag to false

                // Calculate the time slice for this task based on its weight
                int time_slice = (tasks[i].weight * 100) / total;

                // The task can only run for the remaining time or the calculated time slice, whichever is smaller
                int run_time = (tasks[i].remaining_time < time_slice) ? tasks[i].remaining_time : time_slice;
                tasks[i].remaining_time -= run_time; // Decrease remaining time by run time

                // Print task execution details
                printf("Task %d executing for %d units at time %d\n", tasks[i].task_id, run_time, current_time);
                current_time += run_time;
            }
        }

        // If all tasks are done, break out of the loop
        if (all_done) {
            break;
        }
    }

    printf("All tasks completed.\n");
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
        printf("Execution time: ");
        scanf("%d", &tasks[i].execution_time);
        printf("Weight: ");
        scanf("%d", &tasks[i].weight);
        tasks[i].remaining_time = tasks[i].execution_time; // Initialize remaining time
    }

    printf("\nStarting Proportional Scheduling...\n");
    proportional_scheduler(tasks, num_tasks);

    return 0;
}