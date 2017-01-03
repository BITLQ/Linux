/*************************************************************************
	> File Name: test.h
	> Author:   刘强
	> Mail: 849886839@qq.com 
	> Created Time: Sun 01 Jan 2017 08:05:52 PM PST
 ************************************************************************/

#ifndef _TEST_H
#define _TEST_H

#include<stdio.h>
#include<unistd.h>
void func()
{
    //进度条
    int i = 0;
    char arr[101] = {0};
    const  char* str = "-\\|/";

    while(i <= 100)
    {
        printf("[%-100s]%d%%[%c]\r",arr,i,str[i%4]);
        arr[i] = '=';
        ++i;
        fflush(stdout);
        usleep(100000);
    }

    printf("\n");
}
#endif
