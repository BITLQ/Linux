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
    if(argc != 3)
    {
        printf("[ip][port]\n");
    }

    int sock = socket(AF_INET,SOCK_DGRAM,0);
    if(sock < 0)
    {
        perror("socket");
        return 1;
    }


    //发送：
    char buf[SIZE];
    size_t buflen = SIZE;
    struct sockaddr_in peer;
    peer.sin_family = AF_INET;
    peer.sin_port = htons(atoi(argv[2]));
    peer.sin_addr.s_addr = inet_addr(argv[1]);
    size_t len = sizeof(struct sockaddr_in);
    
    while(1)
    {
        int s = read(0,buf,sizeof(buf)-1);
        buf[s - 1] = 0;
        sendto(sock,buf,s,0,(struct sockaddr*)&peer,sizeof(struct sockaddr_in));
    }
    close(sock);
    return 0;
}
