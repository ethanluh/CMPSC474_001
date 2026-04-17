#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define BUFFER_SIZE 5

int BUFFER[BUFFER_SIZE];
int count = 0;
int in = 0;
int out = 0;

int done = 0;
pthread_mutex_t m;
pthread_cond_t empty, fill;

void *producer(void *arg);
void *consumer(void *arg);
int put(int item);
int get();

int main() {
    pthread_t prod_thread, cons_thread;
    pthread_create(&prod_thread, NULL, producer, (void *) BUFFER_SIZE);
    pthread_create(&cons_thread, NULL, consumer, NULL);
    pthread_join(prod_thread, NULL);
    pthread_join(cons_thread, NULL);

    return 0;
}

void *producer(void *arg) {
    int i;
    for (i = 0; i < BUFFER_SIZE; i++) {
        pthread_mutex_lock(&m);
        while (count == BUFFER_SIZE) {
            pthread_cond_wait(&empty, &m);
        }
        put(i);
        printf("%d\n", i);
        pthread_cond_signal(&fill);
        pthread_mutex_unlock(&m);
    }
}

void *consumer(void *arg) {
    printf("Buffer output:\n");
    int i;
    for (i = 0; i < BUFFER_SIZE; i++) {
        pthread_mutex_lock(&m);
        while (count == 0) {
            pthread_cond_wait(&fill, &m);
        }
        int item = get();
        printf("%d\n", item);
        pthread_cond_signal(&empty);
        pthread_mutex_unlock(&m);
    }
    return NULL;
}

int put(int item) {
    BUFFER[in] = item;
    in = (in + 1) % BUFFER_SIZE;
    count++;
    return item;
}

int get() {
    int item = BUFFER[out];
    out = (out + 1) % BUFFER_SIZE;
    count--;
    return item;
}
