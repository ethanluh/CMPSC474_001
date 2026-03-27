#include <stdio.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/wait.h>
// #include <stdlib.h>
// #include <sys/shm.h>
#include <string.h>

int main() {
    char *shared_text = mmap(NULL, 100, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);;
    char buffer[100];

    pid_t pid = fork();

    if (pid == 0) {
        int v = 80;
        printf("In child process.\n");

        read(0, buffer, 100);
        
        strcpy(shared_text, buffer);
        shared_text[strlen(shared_text)] = '\n';

        printf("Not shared v: %d\n", v);
        printf("Shared text: %s", shared_text);
    } 
    else {
        wait(NULL);
        int v = 5;
        printf("In parent process.\n");
        printf("Not shared v: %d\n", v);
        printf("Shared text: %s", shared_text);
        munmap(shared_text, strlen(shared_text));
    }
    return 0;
}