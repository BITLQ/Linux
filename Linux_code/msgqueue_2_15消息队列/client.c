#include"comm.h"

int main()
{
    int msgid = getMsgQueue();
    char buf[MYSIZE];
    char out[2*MYSIZE];

    while(1)
    {
        printf("please enter: ");
        fflush(stdout);

        ssize_t _s = read(0,buf,sizeof(buf)-1);
        if(_s > 0)
        {
            buf[_s] ='\0';
            sendMessage(msgid,CLIENT_TYPE,buf);
        }

        if(messageReceive(msgid,SERVER_TYPE,buf) < 0)
        {
            break;
        }
        printf("server echo# %s\n",buf);
    }
    return 0;
}
