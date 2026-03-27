#include <sys/ipc.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/shm.h> //forgot shm.h
#include <string.h>
#include <sys/wait.h>

int main() {
    void *shmem;
    int shmid = shmget((key_t)1044, 2048, 0666|IPC_CREAT);
    shmem = shmat(shmid, NULL, 0);
    char buffer[100];

    pid_t p = fork(); //should be pid_t, not int

    if (p == 0) {
        printf("child with shmid: %d\n", shmid);
        read(0, buffer, 100);
        strcpy(shmem, buffer); //strcpy not strcopy
        printf("shared memory in child: %s\n", (char*)shmem);
    }
    if (p > 0) {
        wait(NULL);
        printf("parent with shmid: %d\n", shmid);
        printf("shared memory in parent: %s\n", (char*)shmem);
    }
    return 0;
}