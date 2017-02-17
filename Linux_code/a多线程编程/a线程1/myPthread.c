/*************************************************************************
	> File Name: pthread.c
	> Author:   刘强
	> Mail: 849886839@qq.com 
	> Created Time: Thu 16 Feb 2017 07:10:54 PM PST
 ************************************************************************/

#include<pthread.h>
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/types.h>

void* thread_run(void* arg)
{
    int count = 5;
    while(count--)
    {
        sleep(1);
        printf("new thread pid: %d,ppid: %d,tid: %u\n",getpid(),getppid(),pthread_self());
    }
        //退出方式，三种 ,exit是终止进程的；
        printf("new thread is over...\n");
       // return (void*)23;
       // pthread_exit((void*)1);
}

int main()
{
    pthread_t tid;;
    int ret = pthread_create(&tid,NULL,thread_run,NULL);
    if(ret < 0)
    {
        perror("pthread_creat");
        return -1;
    }

    printf("main thread pid: %d,ppid: %d,tid: %lu\n",getpid(),getppid(),pthread_self());
    
    sleep(2);
    pthread_cancel(tid);

    int exitCode;
    pthread_join(tid,(void**)&exitCode);
    printf("join new thread done..., %d\n",exitCode);
    return 0;
}
