#include<stdio.h>
#include<unistd.h>
#include<pthread.h>
#include<fcntl.h>
#include<stdlib.h> 

// Inside thread.
// Inside main process.
// num1: 3
// num2: 5
// Thread return: 8

void *thread_func(void *arg) {
	printf("Inside thread.\n");

	int* nums = arg;
	int sum = nums[0] + nums[1];

	int *ret = malloc(sizeof(int));
	*ret = sum;

	pthread_exit(ret);
}

int main() {
	void *result;
	int nums[2] = {3, 5};

	pthread_t a_thread;
	
	pthread_create(&a_thread, NULL, thread_func, nums);
	pthread_join(a_thread, &result);

	printf("Inside main process.\n");

	printf("num1: %d\nnum2: %d\nThread return: %d\n", nums[0], nums[1], *(int *)result);

	free(result);

	return 0;
}
