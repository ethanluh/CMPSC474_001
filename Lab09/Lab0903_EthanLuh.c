#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    int size;

    printf("Enter the memory size that you request: ");
    scanf("%d", &size);
    void *malloc_attempt = malloc(size);

    if (malloc_attempt == NULL) {
        printf("The allocation failed, the value of malloc_attemt is: (nil)\n");
    }
    else {
        printf("Allocation successful!\n");
    }
    // malloc limit around 800000000000
    return 0;
}