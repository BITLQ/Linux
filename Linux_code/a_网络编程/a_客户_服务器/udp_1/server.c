/*************************************************************************
	> File Name: server.c
	> Author:   刘强
	> Mail: 849886839@qq.com 
	> Created Time: Fri 10 Mar 2017 09:20:33 PM PST
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
    //udp不许要监听；

    int sock = socket(AF_INET,SOCK_DGRAM,0);
    if(sock < 0)
    {
        perror("socket");
        return 1;
    }

    struct sockaddr_in local;
   local.sin_family = AF_INET;
   local.sin_port = htons(atoi(argv[2]));
   local.sin_addr.s_addr = inet_addr(argv[1]);

    if(bind(sock,(struct sockaddr*)&local,sizeof(struct sockaddr_in)) < 0)
    {
        perror("bind");
        return 2;
    }

    //绑定成功
    //接收：
    char buf[SIZE];
    size_t buflen = SIZE;
    struct sockaddr_in peer;
    peer.sin_family = AF_INET;
    size_t len = sizeof(struct sockaddr_in);
    
    while(1)
    {
        int s = recvfrom(sock,buf,buflen,0,(struct sockaddr*)&peer,&len);
        if(s < 0)
        {
            perror("recvfrom");
            return 3;
        }
        else if(s > 0)
        {
            printf("client# %s\n",buf);           
        }
        else if(s == 0){
           printf("client is quit\n");
            break;
        }

        printf("%d\n",s);
    }
    close(sock);
    return 0;
}
