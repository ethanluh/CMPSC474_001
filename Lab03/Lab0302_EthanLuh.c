#include <unistd.h>
#include <stdio.h>

int main()
{
    int p = getpid();
    int rc_1 = fork();

    if (rc_1 == 0)
    {
        int rc_2 = fork();
        
        if (rc_2 == 0)
        {
            printf("I am son (pid: %d)\n\n", getpid());
        }
        else
        {
            printf("I am father (pid: %d) having son (pid: %d)\n\n", getpid(), rc_2);
        }
    }
    else
    {
        printf("I am grandpa (pid: %d) having son (pid: %d)\n\n", p, rc_1);
    }
    return 0;
}
