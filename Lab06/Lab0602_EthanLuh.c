#include<stdio.h>
#include<unistd.h>
#include<pthread.h>
#include<fcntl.h>
#include<stdlib.h> 

// Inside Thread 1. 
// Inside main process
// Inside Thread 2.

// cat Thread.txt
// Hello it's T2

void *thread_func1(void *arg) {
	int f;

	printf("Inside Thread 1.\n");

	f = open("Thread.txt", O_RDWR | O_TRUNC | O_CREAT, 0644);
		
	int *ret = malloc(sizeof(int));
	*ret = f;

	pthread_exit(ret);
}

void *thread_func2(void *arg) {
	int *f = (int *)arg;
	
	printf("Inside Thread 2.\n");
	
        write(*f, "Hello it's T2\n", 15);
        close(*f);
}
 
int main() {
	void *result;
        pthread_t a_thread;

        pthread_create(&a_thread, NULL, thread_func1, NULL);
        pthread_join(a_thread, &result);

        printf("Inside main process\n");	

	pthread_create(&a_thread, NULL, thread_func2, (int *)result);
	pthread_join(a_thread, NULL);
	
	free(result);

        return 0;
}
