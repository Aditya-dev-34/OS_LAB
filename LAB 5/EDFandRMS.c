#include <stdio.h>
#include <math.h>

struct Process {
    int pid;
    int et, period, deadline;
    int remaining, next_release, abs_deadline;
};

int gcd(int a, int b) {
    while (b) {
        int t = b;
        b = a % b;
        a = t;
    }
    return a;
}

int lcm(int a, int b) {
    return (a * b) / gcd(a, b);
}

int findHyper(struct Process p[], int n) {
    int h = p[0].period;
    for (int i = 1; i < n; i++)
        h = lcm(h, p[i].period);
    return h;
}

int isSchedulable(struct Process p[], int n, int choice) {
    float util = 0;
    for (int i = 0; i < n; i++) {
        util += (float)p[i].et / p[i].period;
    }
    printf("\nTotal CPU Utilization = %.2f\n", util);
    if (choice == 1) { 
        printf("EDF Condition: U <= 1\n");
        if (util <= 1.0) {
            printf("Schedulable under EDF\n");
            return 1;
        } else {
            printf("Not schedulable under EDF\n");
            return 0;
        }
    } else {
        float bound = n * (pow(2, 1.0 / n) - 1);
        printf("RMS Bound = %.2f\n", bound);
        if (util <= bound) {
            printf("Schedulable under RMS\n");
            return 1;
        } else {
            printf("Not schedulable under RMS\n");
            return 0;
        }
    }
}

int main() {
    int n, choice;
    struct Process p[20];

    printf("Enter number of processes: ");
    scanf("%d", &n);

    printf("\nChoose Scheduling Algorithm:\n");
    printf("1. EDF\n2. RMS\nEnter choice: ");
    scanf("%d", &choice);

    for (int i = 0; i < n; i++) {
        p[i].pid = i + 1;
        if (choice == 1) {
            printf("\nEnter Execution Time, Period, Deadline for P%d: ", p[i].pid);
            scanf("%d%d%d", &p[i].et, &p[i].period, &p[i].deadline);
        } else {
            printf("\nEnter Execution Time and Period for P%d: ", p[i].pid);
            scanf("%d%d", &p[i].et, &p[i].period);
            p[i].deadline = p[i].period;
        }
        p[i].remaining = 0;
        p[i].next_release = 0;
    }
    if (!isSchedulable(p, n, choice)) {
        printf("\n➡ Exiting program...\n");
        return 0;
    }
    int time = 0, hyper = findHyper(p, n);
    int ganttPID[200], ganttTime[200], g = 0, lastPID = -1;

    while (time < hyper) {
        for (int i = 0; i < n; i++) {
            if (time == p[i].next_release) {
                p[i].remaining = p[i].et;
                p[i].abs_deadline = time + p[i].deadline;
                p[i].next_release += p[i].period;
            }
        }
        int idx = -1;
        if (choice == 1) {
            for (int i = 0; i < n; i++) {
                if (p[i].remaining > 0) {
                    if (idx == -1 || p[i].abs_deadline < p[idx].abs_deadline)
                        idx = i;
                }
            }
        }
        else {
            for (int i = 0; i < n; i++) {
                if (p[i].remaining > 0) {
                    if (idx == -1 || p[i].period < p[idx].period)
                        idx = i;
                }
            }
        }
        if (idx != -1) {
            if (lastPID != p[idx].pid) {
                ganttPID[g] = p[idx].pid;
                ganttTime[g++] = time;
                lastPID = p[idx].pid;
            }
            p[idx].remaining--;
        } else {
            if (lastPID != -1) {
                ganttPID[g] = -1;
                ganttTime[g++] = time;
                lastPID = -1;
            }
        }
        time++;
    }
    ganttTime[g] = time;
    if (choice == 1)
        printf("\n===== EDF Gantt Chart =====\n");
    else
        printf("\n===== RMS Gantt Chart =====\n");

    for (int i = 0; i < g; i++) printf("--------");
    printf("-\n|");

    for (int i = 0; i < g; i++) {
        if (ganttPID[i] == -1)
            printf(" Idle\t |");
        else
            printf(" P%d \t|", ganttPID[i]);
    }

    printf("\n");
    for (int i = 0; i < g; i++) printf("--------");
    printf("-\n");

    for (int i = 0; i <= g; i++)
        printf("%d\t", ganttTime[i]);

    printf("\n");
    return 0;
}
