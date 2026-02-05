#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main(){
    int p = getpid();
    int rc = fork();
    if (rc == 0){
        sleep(12);
        printf("orphan (pid: %d) parent (pid: %d)\n\n", getpid(), getppid());
    }
    else {
        sleep(3);
        printf("parent (pid: %d) child (%d)\n\n", getpid(), rc);
    }
    return 0;
}
