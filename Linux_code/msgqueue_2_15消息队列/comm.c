#include"comm.h"

int commMsgQueue(int flags)
{
    key_t _k = ftok(PATHNAME,PROJID);
    if(_k < 0)
    {
        perror("ftok");
        return -1;
    }

    int msgid = msgget(_k,flags); 
    if(msgid < 0)
    {
        perror("msgget");
        return -1;
    }

    return msgid;
}

int creatMsgQueue()
{
    return commMsgQueue(IPC_CREAT|IPC_EXCL|0666);
}
int getMsgQueue()
{
    return commMsgQueue(0);
}

int sendMessage(int msgid, long type,const char* msg)
{
    struct msgbuf buf;
    buf.mytype = type;

    strcpy(buf.mtext,msg);
    int ret = msgsnd(msgid,&buf,sizeof(buf.mtext),0);
    if(ret < 0)
    {
        perror("msgsnd");
        return -1;
    }
    return 0;
}

int messageReceive(int msgid,int type,char out[])
{
    struct msgbuf buf;
    int size = msgrcv(msgid,&buf,sizeof(buf.mtext),type,0);
    if(size > 0)
    {
        //buf.mtext[size] = '\0';
        strncpy(out,buf.mtext,size);
        return 0;
    }
    perror("msgrcv");
    return -1;
}

int distoryMsgQueue(int msgid)
{
    int ret = msgctl(msgid,IPC_RMID,NULL);
    if(ret < 0)
    {
        perror("msgctl");
        return -1;
    }
    return 0;
}
