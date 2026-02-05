#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>

int main()
{
    int p = getpid();
    int rc = fork();
    if (rc == 0)
    {
        printf("I am child (pid: %d)\n\n", getpid());
        execl("/bin/ps", "ps", (char*)NULL);
    }
    else
    {
        wait(NULL);
        printf("\nI am parent (pid: %d) having child (pid: %d)\n\n", p, rc);
    }
    return 0;
}
