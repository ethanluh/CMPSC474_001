#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>

#define BUFFER_SIZE 5

sem_t empty;
sem_t full;
sem_t mutex;

int BUFFER[BUFFER_SIZE];
int in = 0;
int out = 0;

void *producer(void *arg);
void *consumer(void *arg);
int put(int item);
int get();

int main() {
    sem_init(&empty, 0, BUFFER_SIZE);
    sem_init(&full, 0, 0);
    sem_init(&mutex, 0, 1);

    pthread_t prod_thread, cons_thread;
    pthread_create(&prod_thread, NULL, producer, NULL);
    pthread_create(&cons_thread, NULL, consumer, NULL);

    pthread_join(prod_thread, NULL);
    pthread_join(cons_thread, NULL);

    sem_destroy(&empty);
    sem_destroy(&full);
    sem_destroy(&mutex);

    return 0;
}

void *producer(void *arg) {
    int i;
    for (i = 0; i < BUFFER_SIZE; i++) {
        sem_wait(&mutex);
        if (in >= BUFFER_SIZE) {
            sem_wait(&empty);
        }
        put(i);
        sem_post(&full);
        sem_post(&mutex);
        printf("%d\n", i);
    }
    return NULL;
}

void *consumer(void *arg) {
    printf("Buffer output:\n");
    for (int i = 0; i < BUFFER_SIZE; i++) {
        sem_wait(&mutex);
        if (in <= 0) {
            sem_wait(&full);
        }
        int item = get();
        sem_post(&empty);
        sem_post(&mutex);
        printf("%d\n", item);
    }
    return NULL;
}

int put(int item) {
    if (in >= BUFFER_SIZE) {
        return 0; // Buffer is full
    }
    BUFFER[out + in] = item;
    in++;
    return item;
}

int get() {
    int item = BUFFER[out];
    out = (out + 1) % BUFFER_SIZE;
    in--;
    return item;
}
