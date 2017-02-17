#ifndef _COMM_
#define _COMM_

#define CLIENT_TYPE 1
#define SERVER_TYPE 2

#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/msg.h>
#include<unistd.h>
#include<stdio.h>
#include<string.h>
#define PATHNAME "."
#define PROJID 6666
#define MYSIZE 128
struct msgbuf
{
    long mytype;
    char mtext[MYSIZE];
};

int creatMsgQueue();
int getMsgQueue();
int distoryMsgQueue(int msgid);
int sendMessage(int msgid,long type,const char* msg );
int messageReceive(int msgid,int type,char out[]);
#endif //comm.h
