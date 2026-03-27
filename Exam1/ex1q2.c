#include <sys/ipc.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <string.h>
#include <sys/wait.h>

int main() {
    int fd[2];
    pipe(fd);
    char buffer[100];

    pid_t p = fork(); //should be pid_t not int

    if (p == 0) {
        printf("In Child_1\n"); //forgot \n
        int l = read(0, buffer, 100);
        write(fd[1], buffer, l);
    }
    if (p > 0) {
        wait(NULL);
        pid_t p2 = fork(); //should be pid_t not int
        if (p2 == 0) {
            printf("In Child_2\n"); //forgot \n
            int l = read(fd[0], buffer, 100);
            printf("%s\n", buffer); //printf not write
        }
    }
    return 0;
}