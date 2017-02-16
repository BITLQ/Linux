#include"comm.h"

int initSem(int semid,int which)
{
    union semun un;
    un.val = 1;
    int ret = semctl(semid,which,SETVAL,un);
    if(ret < 0){
        perror("semctl");
        return -1;
    }
    return 0;
}

static int commSemSet(int nums,int flags) //创建
{
    //获取key
    key_t _k = ftok(PATHNAME,PROJID);

    //创建信号量集
    int semid = semget(_k,nums,flags);
    if(semid < 0){
        perror("semget");
        return -1;
    }
    return semid;
}

int creatSemSet(int nums)
{
    int flags = IPC_CREAT|IPC_EXCL|666;
    return commSemSet(nums,flags);
}

int getSemSet()  //获取
{
    //因为已经创建好，所以获取不关心个数
    return commSemSet(0,0);
}

int semOp(int semid, int which,int op)
{
    struct sembuf s;
    s.sem_num = which;
    s.sem_op = op;
    s.sem_flg = 0;

    int ret = semop(semid,&s,1);
    if(ret < 0){
        perror("semop");
        return -1;
    }
    return 1;
} 

int P(int semid,int which)
{
   return  semOp(semid,which,-1);
}

int V(int semid,int which)
{
   return  semOp(semid,which,1);
}

int destorySemSet(int semid) //销毁
{
    if(semctl(semid,0,IPC_RMID) < 0){
        perror("semctl");
        return -1;
    }
    return 0;
}
