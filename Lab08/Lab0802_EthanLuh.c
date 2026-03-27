#include <stdio.h>
#include <unistd.h>
// #include <stdlib.h>
// #include <sys/shm.h>
// #include <string.h>

int main() {
    pid_t pid = fork();

    if (pid == 0) {
        int v = 80;
        printf("In child process.\n");
        printf("The unshared v: %d\n\n", v);
    } 
    else {
        int v = 5;
        printf("In parent process.\n");
        printf("The unshared v: %d\n\n", v);
    }
    return 0;
}