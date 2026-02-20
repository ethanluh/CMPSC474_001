#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main() {
    int fd;
    char *message = "This is named pipe.";

    fd = open("fifo2", O_WRONLY);
    write(fd, message, strlen(message) + 1);

    printf("Message sent.\n");
    return 0;
}