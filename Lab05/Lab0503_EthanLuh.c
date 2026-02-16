#include <unistd.h>
#include <string.h>
#include <sys/shm.h>
#include <sys/wait.h>

int intToChar(char* out, int in); // Return: len of char array. Takes char array ptr, int to convert

int main()
{
    pid_t p, c;
    p = getpid();
    void * shared_memory;
    char buffer[100];
    int shmid, n, m;
    char shmid_char[20];

    c = fork();
    

    if (c == 0) {
        shmid = shmget((key_t)441, 2048, 0666|IPC_CREAT);
        shared_memory = shmat(shmid, NULL, 0);
        write(0, "child process with shmid: ", 27);

        m = intToChar(shmid_char, shmid);

        write(1, shmid_char, 2);
        write(0, "\n", 2);

        n = read(0, buffer, 100);
        write(1, "shared memory in child: ", 25);
        write(1, buffer, n);
        strcpy(shared_memory, buffer);
    }
    else {
        wait(NULL);

        shmid = shmget((key_t)441, 2048, 0666);
        write(0, "parent process with shmid: ", 28);

        m = intToChar(shmid_char, shmid);

        write(1, shmid_char, m);
        write(1, "\n", 2);

        shared_memory = shmat(shmid, NULL, 0);
        write(1, "shared memory in parent: ", 26);
        write(1, (char *)shared_memory, strlen((char *)shared_memory));
        write(0, "\n", 2);
    }

    return 0;
}

int intToChar(char* out, int in) {
    int i = 0, j;
    char temp;

    if (in == 0) {
        out[i++] = '0';
    } else {
        // Handle negative numbers if needed, for shmget ID it's non-negative on success
        while (in > 0) {
            out[i++] = (in % 10);
            in /= 10;
        }
    }
    out[i] = '\0';

    // Reverse the string
    for (j = 0; j < i / 2; j++) {
        temp = out[j];
        out[j] = out[i - j - 1];
        out[i - j - 1] = temp;
    }
}