#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>

int main() {
    int f = open("hello.txt", O_RDONLY, 0644);

    off_t file_size = lseek(f, 0, SEEK_END);

    char *map = mmap(NULL, file_size, PROT_READ, MAP_SHARED, f, 0);

    printf(map);

    munmap(map, file_size);
    
    return 0;
}