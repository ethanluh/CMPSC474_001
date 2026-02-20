#include<stdio.h>
#include<unistd.h>
#include<pthread.h>
#include<fcntl.h>
 
// Inside Thread 1. 
// Inside main process
// Inside Thread 2.

// cat Thread.txt
// Hello it's T2

void *thread_func(void *arg) {
	int f;

	int *thread_id = (int *)arg;

	printf("Inside Thread %d.\n", *thread_id);

	if (*thread_id == 1) {
		f = open("Thread.txt", O_TRUNC | O_CREAT, 0644);
		close(f);
	}
	else {
		f = open("Thread.txt", O_RDWR);
		write(f, "Hello it's T2\n", 15);
		close(f);
	}
}
 
int main() {
	int thread_ids[2] = {1, 2};

        pthread_t a_thread;

        pthread_create(&a_thread, NULL, thread_func, &thread_ids[0]);
        pthread_join(a_thread, NULL);

        printf("Inside main process\n");

	pthread_create(&a_thread, NULL, thread_func, &thread_ids[1]);
	pthread_join(a_thread, NULL);

        return 0;
}
