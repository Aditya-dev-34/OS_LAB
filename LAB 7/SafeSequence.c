#include <stdio.h>
#include <stdbool.h>

int main() {
    int n, m;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    printf("Enter number of resource types: ");
    scanf("%d", &m);

    int Allocation[n][m], Max[n][m], Need[n][m];
    int Available[m];

    printf("\nEnter Allocation Matrix:\n");
    for (int i = 0; i < n; i++) {
        printf("Process P%d:\n", i);
        for (int j = 0; j < m; j++) {
            scanf("%d", &Allocation[i][j]);
        }
    }
    printf("\nEnter Max Matrix:\n");
    for (int i = 0; i < n; i++) {
        printf("Process P%d:\n", i);
        for (int j = 0; j < m; j++) {
            scanf("%d", &Max[i][j]);
        }
    }
    printf("\nEnter Available Resources:\n");
    for (int j = 0; j < m; j++) {
        scanf("%d", &Available[j]);
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            Need[i][j] = Max[i][j] - Allocation[i][j];
        }
    }
    bool Finish[n];
    int SafeSequence[n];
    int Work[m];

    for (int i = 0; i < n; i++)
        Finish[i] = false;

    for (int j = 0; j < m; j++)
        Work[j] = Available[j];

    int count = 0;

    while (count < n) {
        bool found = false;

        for (int i = 0; i < n; i++) {
            if (!Finish[i]) {
                bool canExecute = true;
                for (int j = 0; j < m; j++) {
                    if (Need[i][j] > Work[j]) {
                        canExecute = false;
                        break;
                    }
                }
                if (canExecute) {
                    for (int j = 0; j < m; j++)
                        Work[j] += Allocation[i][j];

                    SafeSequence[count++] = i;
                    Finish[i] = true;
                    found = true;
                }
            }
        }
        if (!found) {
            printf("\nSystem is in UNSAFE state!\n");
            return 0;
        }
    }
    printf("\nSystem is in SAFE state.\nSafe Sequence: ");
    for (int i = 0; i < n; i++) {
        printf("P%d", SafeSequence[i]);
        if (i != n - 1) printf(" -> ");
    }
    printf("\n");
    int process;
    printf("\nEnter process number making request: ");
    scanf("%d", &process);

    int Request[m];
    printf("Enter request for process P%d:\n", process);
    for (int j = 0; j < m; j++) {
        scanf("%d", &Request[j]);
    }
    for (int j = 0; j < m; j++) {
        if (Request[j] > Need[process][j]) {
            printf("\nError: Request exceeds maximum Need!\n");
            return 0;
        }
    }
    for (int j = 0; j < m; j++) {
        if (Request[j] > Available[j]) {
            printf("\nResources not available. Process must wait.\n");
            return 0;
        }
    }
    for (int j = 0; j < m; j++) {
        Available[j] -= Request[j];
        Allocation[process][j] += Request[j];
        Need[process][j] -= Request[j];
    }
    for (int i = 0; i < n; i++)
        Finish[i] = false;

    for (int j = 0; j < m; j++)
        Work[j] = Available[j];

    count = 0;

    while (count < n) {
        bool found = false;

        for (int i = 0; i < n; i++) {
            if (!Finish[i]) {
                bool canExecute = true;

                for (int j = 0; j < m; j++) {
                    if (Need[i][j] > Work[j]) {
                        canExecute = false;
                        break;
                    }
                }
                if (canExecute) {
                    for (int j = 0; j < m; j++)
                        Work[j] += Allocation[i][j];

                    SafeSequence[count++] = i;
                    Finish[i] = true;
                    found = true;
                }
            }
        }
        if (!found) {
            for (int j = 0; j < m; j++) {
                Available[j] += Request[j];
                Allocation[process][j] -= Request[j];
                Need[process][j] += Request[j];
            }
            printf("\nRequest leads to UNSAFE state. Request denied.\n");
            return 0;
        }
    }
    printf("\nRequest granted. System remains in SAFE state.\nNew Safe Sequence: ");
    for (int i = 0; i < n; i++) {
        printf("P%d", SafeSequence[i]);
        if (i != n - 1) printf(" -> ");
    }
    printf("\n");
    return 0;
}