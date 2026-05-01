#include <stdio.h>
#include <stdlib.h>

#define MAX_REQUESTS 5

int main() {
    printf("Enter the current position: ");
    int start;
    scanf("%d", &start);

    printf("Enter the request order: \n");
    int requests[MAX_REQUESTS];
    for (int i = 0; i < MAX_REQUESTS; i++) {
        scanf("%d", &requests[i]);
    }
    int current = start;
    int total_distance = 0;
    printf("%d", current);
    for (int i = 0; i < MAX_REQUESTS; i++) {
        printf("->%d", requests[i]);
        total_distance += abs(current - requests[i]);
        current = requests[i];
    }
    printf("\nTotal head movement: %d\n", total_distance);
    return 0;
}