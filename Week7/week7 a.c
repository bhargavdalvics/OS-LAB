#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int id;
    int execution_time;
    int period;
    int deadline;     //deadline of current task
    int remaining_time;
} Task;

void rate_monotonic(Task tasks[], int n, int hyperperiod) {  //hyperperiod-total simulation time
    printf("\n--- Rate Monotonic Scheduling ---\n");
    for (int t = 0; t < hyperperiod; t++) {    //t-current time unit
        int chosen = -1;       
        //chosen-Stores the index of the selected task.
        //-1 means no task selected
        
        for (int i = 0; i < n; i++) {
            //New Task Arrival
            if (t % tasks[i].period == 0) {    //Checks whether a new instance of the task arrives.
                tasks[i].remaining_time = tasks[i].execution_time; //reloads execution time
                tasks[i].deadline = t + tasks[i].period; //sets the deadline
            }
            //Priority Selection
            if (tasks[i].remaining_time > 0) {
                if (chosen == -1 || tasks[i].period < tasks[chosen].period)  //smallest period = highest priority 
                    chosen = i;
            }
        }
        //Execute Selected Task
        if (chosen != -1) {
            tasks[chosen].remaining_time--;   //execute task for 1 unit 
            printf("Time %d: Task %d running\n", t, tasks[chosen].id);
        } else {
            printf("Time %d: CPU idle\n", t);
        }
    }
}

int main() {
    Task tasks[] = {
        {1, 1, 4, 0, 0},
        {2, 2, 5, 0, 0}
    };
    int n = 2;
    int hyperperiod = 20;
    rate_monotonic(tasks, n, hyperperiod);
    return 0;
}
