/*************************************************************************
	> File Name: client.c
	> Author:   刘强
	> Mail: 849886839@qq.com 
	> Created Time: Tue 07 Mar 2017 05:02:46 PM PST
 ************************************************************************/
#include<pthread.h>
#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<unistd.h>
#define SIZE 1024
#include<stdlib.h>

//改为多线程
//int sock;

int startup(int port,const char* ip)
{
    //创建套接字描述符
    int _sock = socket(AF_INET,SOCK_STREAM,0);
    if(_sock < 0){

        perror("socket");
        exit(1);
    }
    
    //设置套接字选项，设置地址可复用
    int opt = 1;
    setsockopt(_sock,SOL_SOCKET,SO_REUSEADDR,&opt,sizeof(opt));

    struct sockaddr_in local;
    local.sin_family = AF_INET;
    local.sin_port = htons(port);
    local.sin_addr.s_addr = inet_addr(ip);
    socklen_t len = sizeof(local);
    //绑定套接字
    if(bind(_sock,(struct sockaddr*)&local,len) < 0)
    {
        perror("bind");
        exit(1);
    }

    //开启监听
    if(listen(_sock,5) < 0){
        perror("listen");
        exit(1);
    }

    return _sock;
}


void* receive(void* psock)
{
    int sock = *((int*)psock);
    printf("%d\n",sock);
    while(1)
    {
        char buf[SIZE];
        ssize_t s = read(sock,buf,SIZE - 1);
        if(s < 0)
        {
            perror("read");
            break; 
        }
        else if(s > 0)
        {
            buf[s] = 0;
            printf("client#: %s\n",buf);
            write(sock,buf,sizeof(buf)-1);
        }
        else{
            printf("client is quit\n");
            break;
        }
    }
    close(sock);
 }


int main(int argc, char* argv[])
{

    if(argc != 3)
    {
        printf("[ip] [port]\n");
        return 0;
    }
    
    int lis_sock = startup(atoi(argv[2]),argv[1]);
    
    struct sockaddr_in remote;
    socklen_t len = sizeof(struct sockaddr_in);
    
    while(1)
    {
    
        //获得链接请求并建立链接
        int sock = accept(lis_sock,(struct sockaddr*)&remote,&len);
        if(sock < 0)
        {
            perror("accept");
            continue;
        }
        
        printf("sock = %d\n",sock);
        pthread_t tid;
        pthread_create(&tid,NULL,receive,&sock);
        pthread_detach(tid);
    }
    return 0;
}
