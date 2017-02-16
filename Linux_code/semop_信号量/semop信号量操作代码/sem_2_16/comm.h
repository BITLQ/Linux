#ifndef _COMM
#define _COMM_

#include<unistd.h>
#include<stdio.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/sem.h>
#define PATHNAME "."
#define PROJID 0x6666

union semun{
    int val;
    struct semid_ds *buf;
    unsigned short *array;
    struct seminfo *__buf;
};

int initSem(int semid,int which);
int P(int semid,int which);
int V(int semid, int which);
int creatSemSet(int nums); //创建信号量集
int getSemSet();//获取
int destorySemSet(int semid); //销毁

#endif  //comm.h
