#include <stdio.h>

#define MAX 10

int main() {
    int n, m;
    int alloc[MAX][MAX], req[MAX][MAX];
    int avail[MAX], finish[MAX];
    int i, j, k;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    printf("Enter number of resources: ");
    scanf("%d", &m);

    printf("Enter Allocation Matrix:\n");
    for(i = 0; i < n; i++)
        for(j = 0; j < m; j++)
            scanf("%d", &alloc[i][j]);

    printf("Enter Request Matrix:\n");
    for(i = 0; i < n; i++)
        for(j = 0; j < m; j++)
            scanf("%d", &req[i][j]);

    printf("Enter Available Resources:\n");
    for(i = 0; i < m; i++)
        scanf("%d", &avail[i]);

    for(i = 0; i < n; i++) {
        int flag = 0;
        for(j = 0; j < m; j++)
            if(alloc[i][j] != 0)
                flag = 1;
        finish[i] = (flag == 0) ? 1 : 0;
    }
    while(1) {
        int found = 0;
        for(i = 0; i < n; i++) {
            if(!finish[i]) {
                for(j = 0; j < m; j++)
                    if(req[i][j] > avail[j])
                        break;

                if(j == m) {
                    for(k = 0; k < m; k++)
                        avail[k] += alloc[i][k];

                    finish[i] = 1;
                    found = 1;
                }
            }
        }
        if(!found) break;
    }
    int deadlock = 0;
    for(i = 0; i < n; i++) {
        if(!finish[i]) {
            printf("Process P%d is deadlocked\n", i);
            deadlock = 1;
        }
    }
    if(!deadlock)
        printf("No deadlock detected\n");

    return 0;
}
