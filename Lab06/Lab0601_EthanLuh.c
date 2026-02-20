#include<stdio.h>
#include<unistd.h>
#include<pthread.h>
#include<fcntl.h>

// Inside Thread 1.
// Inside main process

// cat Thread.txt
// Hello

void *thread_func(void *arg) {
	int f;

	int *thread_id = (int *)arg;

	printf("Inside Thread %d.\n", *thread_id);

	f = open("Thread.txt", O_RDWR | O_CREAT | O_TRUNC, 0644);
	write(f, "Hello\n", 7);
	close(f);

	return NULL;
}

int main() {
	int thread_id = 1;

	pthread_t a_thread;
	pthread_create(&a_thread, NULL, thread_func, &thread_id);
	pthread_join(a_thread, NULL);
	
	printf("Inside main process\n");

	return 0;
}
