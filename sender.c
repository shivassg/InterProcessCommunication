#include <fcntl.h>
#include <sys/stat.h> 
#include <mqueue.h>
#include <stdio.h>
#include <string.h>

#define MSG_QUEUE_NAME "/msgq"

/* Sender program to create a message queue and send messages */

int main() {
    int i;
    mqd_t mqd;
    struct mq_attr attr;
    const char *msgs[3];
    msgs[0] = "Hi!";
    msgs[1] = "Hello";
    msgs[2] = "How are you";

    /* Set the maximum number of messages in the queue to 6 */
    attr.mq_maxmsg = 6;
    /* Set the maximum size of each message to 512 */
    attr.mq_msgsize = 512;

    /* Open the message queue for creation and writing */
    mqd = mq_open(MSG_QUEUE_NAME, O_CREAT | O_WRONLY, S_IRUSR | S_IWUSR, &attr);
    if (mqd == (mqd_t) -1) {
        printf("Unable to open message queue for creation and writing");
        return -1; 
    }   

    for (i=0; i<3; i++) {
        if (mq_send(mqd, msgs[i], strlen(msgs[i]), 0) == -1) {
            printf("Unable to send message %s", msgs[i]);
            return -1; 
        }   
    }   
}