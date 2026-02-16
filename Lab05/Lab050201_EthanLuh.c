#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

int main()
{
    int res;
    res = mkfifo("fifo1", 0777);
    write(1, "Named pipe created\n", 20);
    return 0;
}