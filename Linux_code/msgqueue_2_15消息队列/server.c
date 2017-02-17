#include"comm.h"

int main()
{
    int msgid = creatMsgQueue();
    char buf[2*MYSIZE];

    while(1)
    {
        sleep(5);
        if(messageReceive(msgid,CLIENT_TYPE,buf) < 0)
        {
            break;
        }
        printf("client# %s\n",buf);
        if(sendMessage(msgid,SERVER_TYPE,buf) < 0)
        {
            break;
        }
    }

    distoryMsgQueue(msgid);
    return 0;
}
