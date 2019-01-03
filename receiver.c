#include <fcntl.h>
#include <sys/stat.h> 
#include <mqueue.h>
#include <stdio.h>
#include <string.h>

#define MSG_QUEUE_NAME "/msgq"

/* Receiver program to read all messages in the message queue sent by the sender */

int main() {
    int i;
    mqd_t mqd;
    unsigned int msg_prio;
    ssize_t bytes_read;
    char msg[512];

    /* Open the message queue for reading */
    mqd = mq_open(MSG_QUEUE_NAME, O_RDONLY | O_NONBLOCK);
    if (mqd == (mqd_t) -1) {
        printf("Unable to open message queue for reading");
        return -1; 
    }   

    while (bytes_read != -1) {
        memset(&msg, 0, sizeof(msg));
        bytes_read = mq_receive(mqd, msg, 512, &msg_prio);
        if (bytes_read >= 0) {
            printf("Read %s (bytes: %ld) from the sender\n", msg, bytes_read);
        }
    }
    /* Remove the message queue */
    if (mq_unlink(MSG_QUEUE_NAME) == -1) {
        printf("Unable to remove the message queue");
        return -1;
    }
    return 0;   
}