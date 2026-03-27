#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    int size;
    int *scores;
    int sum;
    int avg;

    printf("Please enter the size of score: ");
    scanf("%d", &size);
    scores = malloc(size * sizeof(int));

    printf("Enter the score here. Your last enter is as the end of input.\n");
    for (int i = 0; i < size; i++) {
        scanf("%d", &scores[i]);
        sum += scores[i];
    }
    avg = sum/size;

    printf("sum: %d\n", sum);
    printf("average: %d\n", avg);

    free(scores);

    return 0;
}