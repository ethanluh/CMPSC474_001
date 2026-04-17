#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

void *child_thread(void *arg);

sem_t s;

int main() {
    sem_init(&s, 0, 0);
    pthread_t child;
    pthread_create(&child, NULL, child_thread, NULL);
    sem_wait(&s);
    printf("Inside parent thread.\n");
    return 0;
}

void *child_thread(void *arg) {
    printf("Inside child thread.\n");
    sem_post(&s);
    return NULL;
}
