#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#define BUFFER_SIZE 512

struct msg {
    long int msg_type;
    char text[BUFFER_SIZE];
};

int main() {
    int rmid;
    int running = 1;
    int msgid;
    struct msg data;
    long int  msg_type;

    msgid = msgget((key_t)144, 0666|IPC_CREAT);

    while (running) {
        if (rmid == 0) {
            msgrcv(msgid, (void*)&data, BUFFER_SIZE, msg_type, 0);

            write(1, "Data received: ", 16);
            write(1, data.text, strlen(data.text));

            if(strncmp(data.text, "quit", 4) == 0)
                running = 0;
        }

        rmid = msgctl(msgid, IPC_RMID, 0);
    }
}