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
#define SIZE 1024
#include<stdlib.h>

int startup(int port,const char* ip)
{
    //创建套接字描述符
    int sock = socket(AF_INET,SOCK_STREAM,0);
    if(sock < 0){

        perror("socket");
        exit(1);
    }
    
    //设置套接字选项，设置地址可复用
    int opt = 1;
    setsockopt(sock,SOL_SOCKET,SO_REUSEADDR,&opt,sizeof(opt));

    struct sockaddr_in local;
    local.sin_family = AF_INET;
    local.sin_port = htons(port);
    local.sin_addr.s_addr = inet_addr(ip);
    socklen_t len = sizeof(local);
    //绑定套接字
    if(bind(sock,(struct sockaddr*)&local,len) < 0)
    {
        perror("bind");
        exit(1);
    }

    //开启监听
    if(listen(sock,5) < 0){
        perror("listen");
        exit(1);
    }

    return sock;
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

        pid_t pid = fork(); 
        if(pid < 0)
        {
            close(sock);
            //进程创建失败
            perror("fork");
            continue;
        }
        else if(pid == 0)
        {
            //child
            //创建链接成功
           close(lis_sock);
            
            //子进程继续创建子进程
//           if(fork() > 0)
//            {
//                exit(1);
//            }
            
           //交给孤儿进程
           while(1)
           {
               char buf[SIZE];
               ssize_t s = read(sock,buf,SIZE - 1);
               if(s > 0)
               {
                   buf[s] = 0;
                   printf("client#: %s\n",buf);
               }
               else{
                   printf("client is quit\n");
                   break;
               }
           }
            close(sock);
            exit(1);
        }
        while(waitpid(-1,NULL,WNOHANG) > 0);

        close(sock);
    }
    return 0;
}
