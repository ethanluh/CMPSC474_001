#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define N 5

sem_t forks[N];
sem_t atomic_execution;  // Semaphore for atomic execution

int left(int p) { return p; }
int right(int p) { return (p + 1) % N; }

void *philosopher(void *num);
void think() { sleep(1); }
void eat() { sleep(1); }
void get_forks(int p);
void put_forks(int p);

int main() {
    pthread_t philosophers[N];
    int phil_num[N];

    sem_init(&atomic_execution, 0, 1);  // Initialize atomic execution semaphore
    for (int i = 0; i < N; i++) {
        sem_init(&forks[i], 0, 1);
        phil_num[i] = i;
        pthread_create(&philosophers[i], NULL, philosopher, (phil_num + i));
    }

    for (int i = 0; i < N; i++) {
        pthread_join(philosophers[i], NULL);
    }

    return 0;
}

void *philosopher(void *num) {
    int p = *(int *)num;
    
    sem_wait(&atomic_execution);  // Acquire atomic execution lock
    
    think();
    get_forks(p);
    printf("Philosopher %d start eating.\n", p);
    eat();
    put_forks(p);
    printf("Philosopher %d finish eating.\n", p);
    
    sem_post(&atomic_execution);  // Release atomic execution lock
}

void get_forks(int p) {
    if (p%2 == 0) {
        sem_wait(&forks[right(p)]);
        printf("Philosopher %d picks right fork.\n", p);
        sem_wait(&forks[left(p)]);
        printf("Philosopher %d picks left fork.\n", p);
    } else {
        sem_wait(&forks[left(p)]);
        printf("Philosopher %d picks left fork.\n", p);
        sem_wait(&forks[right(p)]);
        printf("Philosopher %d picks right fork.\n", p);
    }
}

void put_forks(int p) {
    sem_post(&forks[left(p)]);
    printf("Philosopher %d returns left fork.\n", p);
    sem_post(&forks[right(p)]);
    printf("Philosopher %d returns right fork.\n", p);
}

