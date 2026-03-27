#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main() {
    const int ALPH_LEN = 26;
    const char* filename = "alphabetLowercase.txt";

    int fd = open(filename, O_RDWR | O_CREAT, 0644);

    char *buffer = malloc((ALPH_LEN * 2) * sizeof(char));
    for (int i = 0; i < ALPH_LEN; i++) {
        buffer[2 * i] = 'a' + i;
        buffer[2 * i + 1] = ' ';
    }
    buffer[51] = '\n';

    write(fd, buffer, 52);

    free(buffer);

    return 0;
}