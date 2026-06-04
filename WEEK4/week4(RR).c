#include <stdio.h>

struct Process {
    int pid;
    int bt;
    int rt;
    int wt;
    int tat;
    int at;
};

int main() {
    int n, quantum;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    struct Process p[n];

    for (int i = 0; i < n; i++) {
        p[i].pid = i + 1;

        printf("Enter Arrival Time and Burst Time for P%d: ", p[i].pid);
        scanf("%d%d", &p[i].at, &p[i].bt);

        p[i].rt = p[i].bt;
    }

    printf("Enter Time Quantum: ");
    scanf("%d", &quantum);

    int time = 0, done;

    do {
        done = 1;

        for (int i = 0; i < n; i++) {

            if (p[i].rt > 0 && p[i].at <= time) {
                done = 0;

                if (p[i].rt > quantum) {
                    time += quantum;
                    p[i].rt -= quantum;
                } else {
                    time += p[i].rt;
                    p[i].wt = time - p[i].bt - p[i].at;
                    p[i].tat = p[i].wt + p[i].bt;
                    p[i].rt = 0;
                }
            }
        }

        if (!done)
            time++;

    } while (!done);

    int total_wt = 0, total_tat = 0;

    printf("\nP\tAT\tBT\tWT\tTAT\n");

    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\n",
               p[i].pid, p[i].at, p[i].bt,
               p[i].wt, p[i].tat);

        total_wt += p[i].wt;
        total_tat += p[i].tat;
    }

    printf("\nAverage Waiting Time = %.2f",
           (float)total_wt / n);

    printf("\nAverage Turnaround Time = %.2f",
           (float)total_tat / n);

    return 0;
}
