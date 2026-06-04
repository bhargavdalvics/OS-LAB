#include <stdio.h>

struct Process {
    int at, bt, pr, rt, ct, wt, tat;
};

int main() {
    int n, ch, time = 0, completed = 0;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    struct Process p[n];

    for (int i = 0; i < n; i++) {
        printf("AT BT Priority for P%d: ", i + 1);
        scanf("%d%d%d", &p[i].at, &p[i].bt, &p[i].pr);
        p[i].rt = p[i].bt;
        p[i].ct = 0;
    }

    printf("\n1. Non-Preemptive\n2. Preemptive\nChoice: ");
    scanf("%d", &ch);

    switch (ch) {

    case 1: // Non-Preemptive
        while (completed < n) {
            int idx = -1, min = 999; //min-stores the smallest priority number.

            for (int i = 0; i < n; i++)
                if (p[i].at <= time && p[i].ct == 0 && p[i].pr < min) { 
//p[i].ct == 0 .Process is not completed.
// 
// p[i].pr < min. Has higher priority than previously selected process.
// 
                    
                    min = p[i].pr;
                    idx = i;
                }

            if (idx == -1)
                time++;
            else {
                time += p[idx].bt;
                p[idx].ct = time;
                p[idx].tat = p[idx].ct - p[idx].at;
                p[idx].wt = p[idx].tat - p[idx].bt;
                completed++;
            }
        }
        break;

    case 2: // Preemptive
        while (completed < n) {
            int idx = -1, min = 999;

            for (int i = 0; i < n; i++)
                if (p[i].at <= time && p[i].rt > 0 && p[i].pr < min) {
                    min = p[i].pr;
                    idx = i;
                }

            if (idx == -1)
                time++;
            else {
                p[idx].rt--;
                time++;

                if (p[idx].rt == 0) {
                    p[idx].ct = time;
                    p[idx].tat = p[idx].ct - p[idx].at;
                    p[idx].wt = p[idx].tat - p[idx].bt;
                    completed++;
                }
            }
        }
        break;

    default:
        printf("Invalid Choice");
        return 0;
    }

    printf("\nP\tAT\tBT\tPR\tWT\tTAT\n");
    for (int i = 0; i < n; i++)
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n",
               i + 1, p[i].at, p[i].bt, p[i].pr,
               p[i].wt, p[i].tat);

    return 0;
}
