#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/stat.h>

int main() {
    int f = open("alphabet.txt", O_RDWR | O_CREAT | O_TRUNC, 0644);
    ftruncate(f, 53);
    char *map = mmap(NULL, 53, PROT_READ | PROT_WRITE, MAP_SHARED, f, 0);
    for (int i = 0; i < 26; i++) {
        map[2 * i] = 'A' + i;
        map[2 * i + 1] = ' ';
    }
    map[52] = '\n';
    munmap(map, 53);
    
    close(f);

    return 0;
}