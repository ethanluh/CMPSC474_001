#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

#define BUFFER_SIZE 1024

int main() {
    int fd[2];
    pid_t pid;
    char buffer[BUFFER_SIZE];

    if (pid == 0) {
        printf("Enter a message: ");
        fgets(buffer, BUFFER_SIZE, stdin);

        write(fd[1], buffer, strlen(buffer) + 1);
    } 
    else {
        read(fd[0], buffer, BUFFER_SIZE);
        printf("Parent received: %s", buffer);

        wait(NULL);
    }

    return 0;
}