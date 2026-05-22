#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define N 5

sem_t forks[N];
pthread_t philosophers[N];

void* dine(void* num) {
    int id = *(int*)num;
    int left = id;
    int right = (id + 1) % N;

    while (1) {
        printf("Philosopher %d is thinking.\n", id);
        sleep(1);

        if (id % 2 == 0) {
            sem_wait(&forks[left]);
            printf("Philosopher %d picked up left fork %d.\n", id, left);

            sem_wait(&forks[right]);
            printf("Philosopher %d picked up right fork %d.\n", id, right);
        } else {
            sem_wait(&forks[right]);
            printf("Philosopher %d picked up right fork %d.\n", id, right);

            sem_wait(&forks[left]);
            printf("Philosopher %d picked up left fork %d.\n", id, left);
        }

        printf("Philosopher %d is eating.\n", id);
        sleep(1);

        sem_post(&forks[left]);
        sem_post(&forks[right]);

        printf("Philosopher %d put down forks %d and %d.\n", id, left, right);
    }
}

int main() {
    int ids[N];

    for (int i = 0; i < N; i++)
        sem_init(&forks[i], 0, 1);

    for (int i = 0; i < N; i++) {
        ids[i] = i;
        pthread_create(&philosophers[i], NULL, dine, &ids[i]);
    }

    for (int i = 0; i < N; i++)
        pthread_join(philosophers[i], NULL);

    return 0;
}