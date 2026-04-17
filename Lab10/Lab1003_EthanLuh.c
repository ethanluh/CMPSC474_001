#include<stdio.h>
#include<pthread.h>

int counter = 0;
pthread_mutex_t lock;

// Adjust this value based on the required sample output (1000, 10000, 100000, 1000000)
#define LOOP_COUNT 100000 

void *threadA(void *arg) {
    printf("Inside thread A.\n");
    for (int i = 0; i < LOOP_COUNT; i++) {
        pthread_mutex_lock(&lock);
        counter = counter + 1;
        pthread_mutex_unlock(&lock);
    }
    printf("The counter: %d\n", counter);
    return NULL;
}

void *threadB(void *arg) {
    printf("Inside thread B.\n");
    for (int i = 0; i < LOOP_COUNT; i++) {
        pthread_mutex_lock(&lock);
        counter = counter + 1;
        pthread_mutex_unlock(&lock);
    }
    printf("The counter: %d\n", counter);
    return NULL;
}

int main() {
    pthread_t t1, t2;

    // Initialize the mutex
    pthread_mutex_init(&lock, NULL);

    pthread_create(&t1, NULL, threadA, NULL);
    pthread_create(&t2, NULL, threadB, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    printf("Inside main process.\n");
    printf("The counter: %d\n", counter);
    
    // Destroy the mutex
    pthread_mutex_destroy(&lock);
    return 0;
}