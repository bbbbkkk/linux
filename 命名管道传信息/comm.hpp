//开启关闭管道
#pragma once
#include <iostream>
#include <sys/stat.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
using namespace std;
#define FIFO_FILE "./myfifo"
#define MODE 0664

enum{
    FIFO_CREATE_ERR=1,
    FIFO_DELETE_ERR,
    FIFO_OPEN_ERR
};

class Init
{
    public:
    Init()
    {
        //创建管道
        int n=mkfifo(FIFO_FILE,MODE);
        if(n==-1)
        {
            perror("mkfifo fail");
            exit(FIFO_CREATE_ERR);
        }
    }
    ~Init()
    {
        //删除管道
        int m=unlink(FIFO_FILE);
        if(m==-1)
        {
            perror("unlink fail");
            exit(FIFO_DELETE_ERR);
        }
    }
    
};
