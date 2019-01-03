# InterProcessCommunication

Sender.c

Sender.c contains the program for the sender process that is used to send the message to the receiver process. It is implemented using message queue.  

mq_open function in the POSIX message queue API is used to create a new message queue or open an existing queue. In sender.c mq_open is used to create a new message queue. 

mq_open(MSG_QUEUE_NAME, O_CREAT | O_WRONLY, S_IRUSR | S_IWUSR, &attr);

MSG_QUEUE_NAME is the name of the queue. In this program it is called as ‘msgq’

O_CREAT | O_WRONLY -Flags to open this message queue for create and write only.

S_IRUSR | S_IWUSR - Specifies the permission for the file created for the message queue. 

&attr - message queue attribute. It contains the following fields.

	1) mq_maxmsg: It is used to determine the maximum number of messages to the queue. In this program, I gave the maximum number of messages as 6. 

	2) mq_msgsize: It is determines the maximum message size in bytes. I gave the maximum message size as 512 bytes.

If mq_open API return value is -1, it means that the creation is failed. Otherwise it succeeded.

mq_send() function writes the message to the queue. 

mq_send(mqd, msgs[i], strlen(msgs[i]), 0)

 1) mqd is the message queue descriptor ( return value of mq_open)
 2) msgs[i] is the message. In this program, there is three message. We are iterating this mq_send in a for loop for three time, to add all the three message to the queue. 

 3)strlen(msgs[i]) is the size

 4) 0 is the priority. All the message is given equal priority.

Receiver.c 

Receiver.c message contains the receiver process that is used to receive the message from the sender process through the message queue. 

mq_open(MSG_QUEUE_NAME, O_RDONLY | O_NONBLOCK); 

mq_open in the receiver.c is used to open the message queue for reading

mq_receive is used to read the message. 

O_NONBLOCK: mq_receive api will won’t block when there is no message queue and will return immediately. 

mq_receive(mqd, msg, 512, &msg_prio);

mqd is the message queue descriptor [return value of mq_open]
msg is the local variable to store the message
512 is the maximum size of the variable
&msg_prio Pointer to hold the priority

mq_receive returns the size of the message

mq_unlink: Removes the message queue.


Reference: http://man7.org/linux/man-pages/man3/mq_open.3.html
http://man7.org/linux/man-pages/man3/mq_receive.3.html
http://man7.org/linux/man-pages/man3/mq_send.3.html
Book: The linux programming interface by Michal Kerrisk
