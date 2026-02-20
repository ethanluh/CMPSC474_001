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

void *thread_func1(void *arg) {
	printf("Inside Thread 1.\n");

	int f = open("Thread.txt", O_RDWR | O_TRUNC | O_CREAT, 0644);
		
	int *ret = malloc(sizeof(int));
	*ret = f;		

	pthread_exit(ret);
}

void *thread_func2(void *arg) {
	printf("Inside Thread 2.\n");

        int *f = (int *)arg;
        write(*f, "Hello, it's Task4\n", 19);
        close(*f);

}

int main() {
	void *result;

	pthread_t a_thread;

	pthread_create(&a_thread, NULL, thread_func1, NULL);
        pthread_join(a_thread, &result);  
	
	int *f = (int *)result;

	printf("fd: %d\n", *f);

	printf("Inside main process.\n");

        pthread_create(&a_thread, NULL, thread_func2, f);
        pthread_join(a_thread, NULL);
  
        printf("fd: %d\n", *f);

	free(f);
	
	return 0;
}
