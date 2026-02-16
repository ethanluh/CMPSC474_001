#include <unistd.h>

int main()
{
    char buff[15];
    read(0, buff, 15);
    write(1, buff, 15);
    return 0;
}