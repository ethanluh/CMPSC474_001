#include <unistd.h>
#include <fcntl.h>

int main()
{
    int f;

    f = open("fifo1", O_WRONLY);
    write(f, "This is named pipe.\n", 21);
    write(1, "\nData is sent\n", 15);

    return 0;
}