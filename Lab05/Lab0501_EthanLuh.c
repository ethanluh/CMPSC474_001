#include <unistd.h>
#include <sys/wait.h>

int main()
{
    int fd[2], n;
    char buffer[100];
    pid_t p;
    pipe(fd);
    p = fork();
    char msg[49] = "I am child process, how are you, parent process?\n";
    
    if (p == 0) {
        write(1, "Passing value to parent\n", 25);
        write(1, msg, 49);
        write(fd[1], msg, 49);
    }
    else {
        wait(NULL);
        write(1, "Parent receives data\n", 22);
        n = read(fd[0], buffer, 100);
        buffer[n] = '\n';
        write(1, buffer, n+1);
    }
    return 0;
}