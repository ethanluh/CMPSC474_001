#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

#define O_RDONLY 00
#define O_WRONLY 01

int main()
{
    int f, n; // File descriptor, number of bytes read from F1.txt
    char buff[100];
    f = open("F1.txt", O_RDONLY);
    n = read(f, buff, 100);
    f = open("F3.txt", O_WRONLY);
    write(f, buff, n);
    return 0;
}