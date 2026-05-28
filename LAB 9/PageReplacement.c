#include <stdio.h>

#define MAX 50

void printTable(int pages[], int result[MAX][MAX], char status[],int n, int frames, int faults, char title[]) {
    int i, j;
    printf("\n\n===== %s =====\n", title);
    printf("\nPage    : ");
    for(i = 0; i < n; i++)
        printf("%3d ", pages[i]);
    for(i = 0; i < frames; i++) {
        printf("\nFrame %d : ", i + 1);
        for(j = 0; j < n; j++) {
            if(result[i][j] != -1)
                printf("%3d ", result[i][j]);
            else
                printf(" -  ");
        }
    }
    printf("\nStatus  : ");
    for(i = 0; i < n; i++)
        printf("%3c ", status[i]);

    printf("\n\nTotal Page Faults = %d\n", faults);
}
void fifo(int pages[], int n, int frames) {
    int frame[MAX], result[MAX][MAX];
    char status[MAX];
    int i, j, k, pos = 0, faults = 0, hit;
    for(i = 0; i < frames; i++)
        frame[i] = -1;

    for(i = 0; i < n; i++) {
        hit = 0;
        for(j = 0; j < frames; j++) {
            if(frame[j] == pages[i]) {
                hit = 1;
                break;
            }
        }
        if(!hit) {
            frame[pos] = pages[i];
            pos = (pos + 1) % frames;
            faults++;
            status[i] = 'F';
        }
        else {
            status[i] = 'H';
        }
        for(k = 0; k < frames; k++)
            result[k][i] = frame[k];
    }

    printTable(pages, result, status, n, frames, faults,
               "FIFO Page Replacement");
}
void lru(int pages[], int n, int frames) {
    int frame[MAX], time[MAX], result[MAX][MAX];
    char status[MAX];
    int i, j, k, count = 0, faults = 0, hit;
    for(i = 0; i < frames; i++) {
        frame[i] = -1;
        time[i] = 0;
    }
    for(i = 0; i < n; i++) {
        hit = 0;
        for(j = 0; j < frames; j++) {
            if(frame[j] == pages[i]) {
                hit = 1;
                count++;
                time[j] = count;
                break;
            }
        }
        if(!hit) {
            int pos = 0, min = time[0];
            for(j = 0; j < frames; j++) {
                if(frame[j] == -1) {
                    pos = j;
                    break;
                }
                if(time[j] < min) {
                    min = time[j];
                    pos = j;
                }
            }
            frame[pos] = pages[i];
            count++;
            time[pos] = count;
            faults++;
            status[i] = 'F';
        }
        else {
            status[i] = 'H';
        }
        for(k = 0; k < frames; k++)
            result[k][i] = frame[k];
    }
    printTable(pages, result, status, n, frames, faults,
               "LRU Page Replacement");
}
void optimal(int pages[], int n, int frames) {
    int frame[MAX], result[MAX][MAX];
    char status[MAX];
    int i, j, k, faults = 0, hit;
    for(i = 0; i < frames; i++)
        frame[i] = -1;

    for(i = 0; i < n; i++) {
        hit = 0;
        for(j = 0; j < frames; j++) {
            if(frame[j] == pages[i]) {
                hit = 1;
                break;
            }
        }
        if(!hit) {
            int pos = -1, farthest = -1;
            for(j = 0; j < frames; j++) {
                if(frame[j] == -1) {
                    pos = j;
                    break;
                }
            }
            if(pos == -1) {
                for(j = 0; j < frames; j++) {
                    int found = 0;
                    for(k = i + 1; k < n; k++) {
                        if(frame[j] == pages[k]) {
                            if(k > farthest) {
                                farthest = k;
                                pos = j;
                            }
                            found = 1;
                            break;
                        }
                    }
                    if(!found) {
                        pos = j;
                        break;
                    }
                }
            }
            frame[pos] = pages[i];
            faults++;
            status[i] = 'F';
        }
        else {
            status[i] = 'H';
        }
        for(k = 0; k < frames; k++)
            result[k][i] = frame[k];
    }
    printTable(pages, result, status, n, frames, faults,
               "Optimal Page Replacement");
}
int main() {
    int pages[MAX], n, frames, i;
    printf("Enter number of pages: ");
    scanf("%d", &n);
    printf("Enter page reference string:\n");
    for(i = 0; i < n; i++)
        scanf("%d", &pages[i]);

    printf("Enter number of frames: ");
    scanf("%d", &frames);
    fifo(pages, n, frames);
    lru(pages, n, frames);
    optimal(pages, n, frames);
    return 0;
}