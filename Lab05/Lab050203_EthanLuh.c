#include <unistd.h>
#include <fcntl.h>

int main()
{
    int f, n;
    char buffer[100];

    f = open("fifo1", O_RDONLY);

    n = read(f, buffer, 100);

    if (n >= 0)
    {
        write(1, "Received data: ", 15);
        write(1, buffer, n);
    }
    
    return 0;
}