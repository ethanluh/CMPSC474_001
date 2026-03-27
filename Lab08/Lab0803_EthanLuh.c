#include <stdio.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/wait.h>
// #include <stdlib.h>
// #include <sys/shm.h>
// #include <string.h>

int main() {
    int *x = mmap(NULL, sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    pid_t pid = fork();

    if (pid == 0) {
        int v = 80;
        *x = 15;
        printf("In child process.\n");
        printf("The unshared v: %d\n", v);
        printf("The shared x: %d\n\n", *x);
    } 
    else {
        wait(NULL);
        int v = 5;
        printf("In parent process.\n");
        printf("The unshared v: %d\n", v);
        printf("The shared x: %d\n\n", *x);
        munmap(x, sizeof(int));
    }
    return 0;
}