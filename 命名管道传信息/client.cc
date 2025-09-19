#include "comm.hpp"
#include "log.hpp"

int main()
{
    int fd =open(FIFO_FILE,O_WRONLY);
    if(fd<0)
    {
        perror("open fail");
        exit(FIFO_OPEN_ERR);
    }
    cout<<"client open file done"<<endl;
    string line;
    while(1)
    {
        cout<<"Please Enter@ ";
        getline(cin,line);
        write(fd,line.c_str(),line.size());
    }
    close(fd);
    return 0;
}
