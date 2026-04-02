#include <stdio.h>

struct Process {
    int pid, at, bt, ct, tat, wt, rt, queue;
};

int main() {
    int n;
    struct Process p[20];

    printf("Enter number of processes: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        p[i].pid = i + 1;
        printf("\nEnter AT and BT for P%d: ", p[i].pid);
        scanf("%d%d", &p[i].at, &p[i].bt);
        printf("Enter queue (0 = System, 1 = User): ");
        scanf("%d", &p[i].queue);
        p[i].rt = -1;
    }

    struct Process systemP[20], userP[20];
    int sysCount = 0, userCount = 0;

    for (int i = 0; i < n; i++) {
        if (p[i].queue == 0)
            systemP[sysCount++] = p[i];
        else
            userP[userCount++] = p[i];
    }

    int sysRem[20], userRem[20];

    for (int i = 0; i < sysCount; i++)
        sysRem[i] = systemP[i].bt;

    for (int i = 0; i < userCount; i++)
        userRem[i] = userP[i].bt;

    int time = 0, completed = 0, total = sysCount + userCount;

    int ganttPID[100], ganttTime[100], g = 0;
    int lastPID = -1;

    float totalWT = 0, totalTAT = 0, totalCT = 0, totalRT = 0;

    while (completed < total) {
        int sysIdx = -1;

        for (int i = 0; i < sysCount; i++) {
            if (systemP[i].at <= time && sysRem[i] > 0) {
                sysIdx = i;
                break;
            }
        }
        if (sysIdx != -1) {
            if (lastPID != systemP[sysIdx].pid) {
                ganttPID[g] = systemP[sysIdx].pid;
                ganttTime[g] = time;
                g++;
                lastPID = systemP[sysIdx].pid;
            }
            if (systemP[sysIdx].rt == -1)
                systemP[sysIdx].rt = time - systemP[sysIdx].at;

            sysRem[sysIdx]--;
            time++;

            if (sysRem[sysIdx] == 0) {
                completed++;
                systemP[sysIdx].ct = time;
                systemP[sysIdx].tat = systemP[sysIdx].ct - systemP[sysIdx].at;
                systemP[sysIdx].wt = systemP[sysIdx].tat - systemP[sysIdx].bt;

                totalWT += systemP[sysIdx].wt;
                totalTAT += systemP[sysIdx].tat;
                totalCT += systemP[sysIdx].ct;
                totalRT += systemP[sysIdx].rt;
            }
        } 
        else {
            int userIdx = -1, minRT = 9999;

            for (int i = 0; i < userCount; i++) {
                if (userP[i].at <= time && userRem[i] > 0) {
                    if (userRem[i] < minRT) {
                        minRT = userRem[i];
                        userIdx = i;
                    }
                }
            }
            if (userIdx != -1) {
                if (lastPID != userP[userIdx].pid) {
                    ganttPID[g] = userP[userIdx].pid;
                    ganttTime[g] = time;
                    g++;
                    lastPID = userP[userIdx].pid;
                }
                if (userP[userIdx].rt == -1)
                    userP[userIdx].rt = time - userP[userIdx].at;

                userRem[userIdx]--;
                time++;

                if (userRem[userIdx] == 0) {
                    completed++;
                    userP[userIdx].ct = time;
                    userP[userIdx].tat = userP[userIdx].ct - userP[userIdx].at;
                    userP[userIdx].wt = userP[userIdx].tat - userP[userIdx].bt;

                    totalWT += userP[userIdx].wt;
                    totalTAT += userP[userIdx].tat;
                    totalCT += userP[userIdx].ct;
                    totalRT += userP[userIdx].rt;
                }
            } else {
                time++;
            }
        }
    }

    ganttTime[g] = time;
    printf("\nPID\tType\tAT\tBT\tCT\tTAT\tWT\tRT\n");

    for (int i = 0; i < sysCount; i++)
        printf("P%d\tSystem\t%d\t%d\t%d\t%d\t%d\t%d\n",
               systemP[i].pid, systemP[i].at, systemP[i].bt,
               systemP[i].ct, systemP[i].tat, systemP[i].wt, systemP[i].rt);

    for (int i = 0; i < userCount; i++)
        printf("P%d\tUser\t%d\t%d\t%d\t%d\t%d\t%d\n",
               userP[i].pid, userP[i].at, userP[i].bt,
               userP[i].ct, userP[i].tat, userP[i].wt, userP[i].rt);

    printf("\nAverage WT  = %.2f", totalWT / total);
    printf("\nAverage TAT = %.2f", totalTAT / total);
    printf("\nAverage CT  = %.2f", totalCT / total);
    printf("\nAverage RT  = %.2f\n", totalRT / total);

    printf("\nGantt Chart:\n");
    for (int i = 0; i < g; i++) printf("--------");
    printf("-\n|");

    for (int i = 0; i < g; i++)
        printf(" P%d\t|", ganttPID[i]);

    printf("\n");

    for (int i = 0; i < g; i++) printf("--------");
    printf("-\n");

    for (int i = 0; i <= g; i++)
        printf("%d\t", ganttTime[i]);

    printf("\n");
    return 0;
}