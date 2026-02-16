#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

#define O_RDONLY 00
#define O_WRONLY 01
#define O_APPEND 02000
#define O_TRUNC 01000

void resetF2();

int main()
{
    int f, n; // File descriptor, number of bytes read from F1.txt
    char buff[100];

    // Reset F2.txt
    resetF2();

    f = open("F1.txt", O_RDONLY);
    n = read(f, buff, 100);

    for (int i = n; i > 0; i--)
    {
        buff[i] = buff[i - 1];
    }
    buff[0] = '\n';

    f = open("F2.txt", O_WRONLY | O_APPEND);
    write(f, buff, n);
    return 0;
}

void resetF2()
{
    int f;
    const char* reset_text = "OS is";
    f = open("F2.txt", O_WRONLY | O_TRUNC); // Resets file to 0 bytes, then writes new text
    write(f, reset_text, 5);
}