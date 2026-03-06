#include <stdio.h>

struct Process {
    int pid;
    int at;
    int bt;
    int ct;
    int tat;
    int wt;
    int rt;
};

int main() {
    int n, i, j;
    struct Process p[20], temp;
    float total_ct = 0, total_tat = 0, total_wt = 0, total_rt = 0;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    for(i = 0; i < n; i++) {
        p[i].pid = i + 1;
        printf("Enter Arrival Time and Burst Time for Process %d: ", p[i].pid);
        scanf("%d %d", &p[i].at, &p[i].bt);
    }
    for(i = 0; i < n - 1; i++) {
        for(j = i + 1; j < n; j++) {
            if(p[i].at > p[j].at) {
                temp = p[i];
                p[i] = p[j];
                p[j] = temp;
            }
        }
    }
    int currentTime = 0;

    for(i = 0; i < n; i++) {

        if(currentTime < p[i].at)
            currentTime = p[i].at;
        p[i].rt = currentTime - p[i].at;
        p[i].ct = currentTime + p[i].bt;
        p[i].tat = p[i].ct - p[i].at;
        p[i].wt = p[i].tat - p[i].bt;
        currentTime = p[i].ct;
        total_ct += p[i].ct;
        total_tat += p[i].tat;
        total_wt += p[i].wt;
        total_rt += p[i].rt;
    }
    printf("\nPID\tAT\tBT\tCT\tTAT\tWT\tRT\n");
    for(i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
               p[i].pid, p[i].at, p[i].bt,
               p[i].ct, p[i].tat, p[i].wt, p[i].rt);
    }
    printf("\nAverage Completion Time = %.2f", total_ct / n);
    printf("\nAverage Turnaround Time = %.2f", total_tat / n);
    printf("\nAverage Waiting Time = %.2f", total_wt / n);
    printf("\nAverage Response Time = %.2f\n", total_rt / n);

    return 0;
}