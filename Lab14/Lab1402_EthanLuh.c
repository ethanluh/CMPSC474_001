#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

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
    int ordered[MAX_REQUESTS];
    for (int i = 0; i < MAX_REQUESTS; i++) {
        int min_distance = INT_MAX;
        int min_index = -1;
        for (int j = 0; j < MAX_REQUESTS; j++) {
            int distance = abs(current - requests[j]);
            if (distance < min_distance) {
                min_distance = distance;
                min_index = j;
            }
        }
        ordered[i] = requests[min_index];
        total_distance += min_distance;
        current = requests[min_index];
        requests[min_index] = INT_MAX; // Mark as visited
    }
    
    printf("%d", start);
    for (int i = 0; i < MAX_REQUESTS; i++) {
        printf("->%d", ordered[i]);
    }
    printf("\nTotal head movement: %d\n", total_distance);
    return 0;
}
