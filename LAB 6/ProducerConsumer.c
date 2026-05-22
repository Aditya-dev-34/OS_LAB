#include <stdio.h>
#include <string.h>

#define MAX 100

int buffer[MAX];
int size;
int in = 0, out = 0;
int empty, full, mutex = 1;

void getBufferString(char *str) {
    int k = 0;
    str[k++] = '[';
    for (int i = 0; i < size; i++) {
        if (buffer[i] == -1)
            k += sprintf(&str[k], "_");
        else
            k += sprintf(&str[k], "%c", buffer[i]);

        if (i != size - 1)
            k += sprintf(&str[k], ", ");
    }
    str[k++] = ']';
    str[k] = '\0';
}

int main() {
    int steps;
    printf("Enter buffer size: ");
    scanf("%d", &size);

    for (int i = 0; i < size; i++)
        buffer[i] = -1;

    empty = size;
    full = 0;

    printf("Enter number of operations: ");
    scanf("%d", &steps);

    char ops[MAX];
    char items[MAX];

    for (int i = 0; i < steps; i++) {
        printf("Step %d - Enter operation (P/C): ", i + 1);
        scanf(" %c", &ops[i]);
        if (ops[i] == 'P' || ops[i] == 'p') {
            printf("Enter item: ");
            scanf(" %c", &items[i]);
        }
    }
    printf("\n%-5s %-25s %-20s %-5s %-5s %-7s %-5s %-5s\n",
           "Step", "Operation", "Buffer", "in", "out", "empty", "full", "mutex");

    for (int step = 0; step < steps; step++) {

        char operation[30];
        char bufferStr[100];
        if (ops[step] == 'P' || ops[step] == 'p') {
            if (empty == 0) {
                strcpy(operation, "Producer tries (blocked)");
            } 
            else {
                empty--;
                buffer[in] = items[step];
                in = (in + 1) % size;
                full++;
                strcpy(operation, "Producer inserts");
            }

        }
        else if (ops[step] == 'C' || ops[step] == 'c') {
            if (full == 0) {
                strcpy(operation, "Consumer tries (blocked)");
            } 
            else {
                buffer[out] = -1;
                out = (out + 1) % size;
                full--;
                empty++;

                strcpy(operation, "Consumer removes");
            }
        } 
        else {
            strcpy(operation, "Invalid");
        }
        getBufferString(bufferStr);

        printf("%-5d %-25s %-20s %-5d %-5d %-7d %-5d %-5d\n",
               step + 1, operation, bufferStr, in, out, empty, full, mutex);
 
    return 0;
}