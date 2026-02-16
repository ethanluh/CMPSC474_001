#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/stat.h>

#define MAX_TEXT 512

struct msg {
    long int msg_type;
    char text[MAX_TEXT];
};

int main() {
    int running = 1;
    int msgid;
    struct msg data;
    char buffer[50];
    
    msgid = msgget((key_t)144, 0666|IPC_CREAT);

    if (msgid == -1) {
        write(1, "Error in creating queue.\n", 26);
        exit(0);
    }

    while (running) {
        write(1, "Enter message: ", 16);
        read(0, buffer, 50);
        data.msg_type = 1;
        strcpy(data.text, buffer);
        if(msgsnd(msgid, (void*)&data, MAX_TEXT, 0) == -1)
            write(0, "Message not sent.\n", 19);

        if(strncmp(buffer, "quit", 4) == 0)
            running = 0;
    }

    return 0;
}