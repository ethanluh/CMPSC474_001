#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

void *child_thread(void *arg);
void thr_exit();
void thr_join();

int done = 0;
pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t c = PTHREAD_COND_INITIALIZER;

int main() {
    printf("Parent begins.\n");
    pthread_t child;
    pthread_create(&child, NULL, child_thread, NULL);
    thr_join();
    printf("Parent ends.\n");
    return 0;
}

void *child_thread(void *arg) {
    printf("Inside child.\n");
    thr_exit();
    return NULL;
}

void thr_exit() {
    pthread_mutex_lock(&m);
    done = 1;
    pthread_cond_signal(&c);
    pthread_mutex_unlock(&m);
}

void thr_join() {
    pthread_mutex_lock(&m);
    while (!done) {
        pthread_cond_wait(&c, &m);
    }
    pthread_mutex_unlock(&m);
}
