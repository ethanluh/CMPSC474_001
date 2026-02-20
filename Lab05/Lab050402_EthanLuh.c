#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#define MSG_KEY 144
#define BUFFER_SIZE 1024

struct msg_buffer {
    long msg_type;
    char msg_text[BUFFER_SIZE];
};

int main() {
    int msgid;
    struct msg_buffer message;

    msgid = msgget(MSG_KEY, 0666 | IPC_CREAT);
    if (msgid < 0) {
        perror("msgget");
        exit(EXIT_FAILURE);
    }

    while (1) {
        msgrcv(msgid, &message, sizeof(message.msg_text), 1, 0);
        printf("data received: %s", message.msg_text);

        if (strncmp(message.msg_text, "quit", 4) == 0)
            break;
    }

    msgctl(msgid, IPC_RMID, NULL);
    return 0;
}