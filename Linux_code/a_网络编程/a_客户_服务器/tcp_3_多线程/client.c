/*************************************************************************
	> File Name: client.c
	> Author:   刘强
	> Mail: 849886839@qq.com 
	> Created Time: Tue 07 Mar 2017 05:02:46 PM PST
 ************************************************************************/

#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<unistd.h>
#define SIZE 1024*1
#include<stdlib.h>

int main(int argc,char* argv[])
{
   //客户端不许要监听和绑定
   //客户端需要做的是链接和发送消息
    if(argc != 3)
    {
        printf("[ip] [port]");
        exit(1);
    }

    int sock = socket(AF_INET,SOCK_STREAM,0);
    if(sock < 0)
    {
        perror("socket");
        exit(1);
    }

    struct sockaddr_in s;
    s.sin_family = AF_INET;
    s.sin_port = htons(atoi(argv[2]));
    s.sin_addr.s_addr = inet_addr(argv[1]);
    
    socklen_t len = sizeof(struct sockaddr_in);

    if(connect(sock,(struct sockaddr*)&s,len) < 0)
    {
        perror("connect");
        //链接失败暂时处理为退出
        exit(1);
    }

    //链接成功
    //发送
    char buf[SIZE];
    while(1)
    {
        printf("send# ");
        fflush(stdout);

        ssize_t s = read(0,buf,SIZE-1);

        buf[s - 1] = 0;

        int ret = write(sock,buf,s);
        if(ret < 0)
        {
            perror("write");
             exit(1);
        }

        ssize_t b = read(sock,buf,sizeof(buf)-1);
        if(b == 0)
        {
            break;
        }
        else if(b < 0)
        {
            perror("read");
            return 3;
        }
        else{
            buf[b] = 0;
            printf("echo#%s\n",buf);
        }
    }
    close(sock);
    return 0;
}
