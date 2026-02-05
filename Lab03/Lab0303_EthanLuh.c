#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>

int main()
{
    int p = getpid();
    int rc_1 = fork();

    if (rc_1 == 0)
    {
        printf("I am 1st child (pid: %d)\n\n", getpid());
    }
    else
    {
        int rc_2 = fork();
        if (rc_2 == 0)
        {
            printf("I am 2nd child (pid: %d)\n\n", getpid());
        }
        else
        {
            wait(NULL);
            printf("I am parent (pid: %d) having 1st child (pid: %d) and 2nd child (pid: %d)\n\n", p, rc_1, rc_2);
        }
    }
    return 0;
}
