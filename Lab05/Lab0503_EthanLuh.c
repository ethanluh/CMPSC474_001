#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>

#define SHM_KEY 441
#define SHM_SIZE 2048

int main() {
    int shmid;
    void *shm_ptr;
    char buffer[100];
    
    pid_t pid = fork();

    if (pid == 0) {
        shmid = shmget((key_t)SHM_KEY, SHM_SIZE, 0666|IPC_CREAT);

        printf("child process with shmid: %d\n", shmid);

        shm_ptr = shmat(shmid, NULL, 0);

        read(0, buffer, 100);
        strcpy(shm_ptr, buffer);
        printf("shared memory in child: %s\n", (char *)shm_ptr);
    } 
    else {
        wait(NULL);
        shmid = shmget((key_t)SHM_KEY, SHM_SIZE, 0666);

        printf("parent process with shmid: %d\n", shmid);

        shm_ptr = shmat(shmid, NULL, 0);

        printf("shared memory in parent: %s\n", (char *)shm_ptr);
    }

    return 0;
}