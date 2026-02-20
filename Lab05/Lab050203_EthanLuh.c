#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

#define BUFFER_SIZE 1024

int main() {
    int fd;
    char buffer[BUFFER_SIZE];

    fd = open("fifo2", O_RDONLY);
    read(fd, buffer, BUFFER_SIZE);
    printf("Received: %s\n", buffer);

    close(fd);
    return 0;
}