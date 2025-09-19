#include "comm.hpp"
#include "log.hpp"

int main()
{
    Init init;
    Log log;
    log.Enable(Onefile);
    //打开管道
    int fd=open(FIFO_FILE,O_RDONLY);
    if(fd<0)
    {
        log(Fatal,"error string:%s,error code:%d",strerror(errno),errno);
        exit(FIFO_OPEN_ERR);
    }
    log(Info,"error string:%s,error code:%d",strerror(errno),errno);
    log(Warning,"error string:%s,error code:%d",strerror(errno),errno);
    log(Fatal,"error string:%s,error code:%d",strerror(errno),errno);
    log(Debug,"error string:%s,error code:%d",strerror(errno),errno);

    //开始通信
    while(1)
    {
        char buffer[SIZE]={0};
        int x=read(fd,buffer,sizeof(buffer));
        if(x>0)
        {
            buffer[x]=0;
            cout<<"client say#"<<buffer<<endl;
        }
        else if(x==0)
        {
            log(Debug,"client quit,me too,error string:%s,error code:%d",strerror(errno),errno);
            break;
        }
        else 
        {
            break;
        }
    }  
    //关闭通信
    close(fd);
    return 0;
}
