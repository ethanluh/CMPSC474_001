#include<stdio.h>
#include<unistd.h>
#include<pthread.h>
#include<fcntl.h>
#include<stdlib.h> 

// Inside Thread 1.
// fd: 3
// Inside main process.
// Inside Thread 2.
// fd: 3

// cat Thread.txt
// Hello, it's Task4

void *thread_func(void *arg) {
	int* temp = arg;
	
	printf("Inside Thread %d.\n", *temp);

	if (*temp == 1) {
		int f = open("Thread.txt", O_RDWR | O_TRUNC | O_CREAT, 0644);
		
		int *ret = malloc(sizeof(int));
		*ret = f;		

		pthread_exit(ret);
	}
	else {
		int f = *(temp + 1);
		write(f, "Hello, it's Task4\n", 19);
		close(f);
	}
}


int main() {
	int thread_data[2] = {1, 2};
	void *result;

	pthread_t a_thread;

	pthread_create(&a_thread, NULL, thread_func, thread_data);
        pthread_join(a_thread, &result);  
	
	int *f = (int *)result;

	printf("fd: %d\n", *f);

	thread_data[0] = thread_data[1];
	thread_data[1] = *f;

	printf("Inside main process.\n");

        pthread_create(&a_thread, NULL, thread_func, thread_data);
        pthread_join(a_thread, NULL);
  
        printf("fd: %d\n", *f);

	free(f);
	
	return 0;
}
