#include<stdio.h>
#include<unistd.h>
#include<pthread.h>

int shared = 5;

void *func1(void *arg) {
    int x = shared;
    x = x + 1;
    printf("Inside thread1.\n");
    sleep(1);
    shared = x;
    printf("The shared: %d\n", shared);
    return NULL;
}

void *func2(void *arg) {
    int y = shared;
    y = y - 1;
    printf("Inside thread2.\n");
    sleep(1);
    shared = y;
    printf("The shared: %d.\n", shared);
    return NULL;
}

int main() {
    pthread_t a_thread, b_thread;

    pthread_create(&a_thread, NULL, func1, NULL);
    pthread_create(&b_thread, NULL, func2, NULL);

    pthread_join(a_thread, NULL);
    pthread_join(b_thread, NULL);

    printf("Inside main process.\n");
    printf("The shared: %d\n", shared);
    return 0;
}