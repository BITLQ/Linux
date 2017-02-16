/*************************************************************************
	> File Name: testSem.c
	> Author:  刘强
	> Mail: 849886839@qq.com
	> Created Time: Wed 15 Feb 2017 11:50:33 PM PST
 ************************************************************************/

#include"comm.h"

int main()
{
    int semid = creatSemSet(1);
    initSem(semid,0);

    pid_t id = fork();
    if(id == 0){
        printf("child is running\n");

        while(1){
            P(semid,0);
            printf("A");
            usleep(1000);
            fflush(stdout);
            printf("A");
            fflush(stdout);
            sleep(1);
            V(semid,0);
        }
    }
    else{
        printf("father is running\n");
        
        while(1){
            P(semid,0);
            printf("B");
            usleep(1000);
            fflush(stdout);
            printf("B");
            fflush(stdout);
            sleep(1);
            V(semid,0);
        }
    }
    destorySemSet(semid);
    return 0;
}
