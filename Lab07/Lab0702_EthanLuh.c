#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>

int main() {
    int f = open("hello.txt", O_RDWR | O_CREAT | O_TRUNC, 0644);
    ftruncate(f, 7);

    char *map = mmap(NULL, 7, PROT_READ | PROT_WRITE, MAP_SHARED, f, 0);
    memcpy(map, "Hello!\n", 7);
    munmap(map, 7);

    close(f);

    return 0;
}