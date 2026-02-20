#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>

int main() {
    if (mkfifo("fifo2", 0666) == 0)
        printf("Named pipe 'fifo2' created successfully.\n");
    else
        perror("mkfifo");

    return 0;
}