#pragma one
#include <iostream>
#include "log.hpp"
#include <cstdint>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>   
#include <arpa/inet.h>
#include <strings.h>
#include <string.h>
#include <errno.h>
#include <functional>
using namespace std;
Log lg;
uint16_t defaultport=8080;
string defaultip="0.0.0.0";
#define SIZE 1024
// typedef function<string(const string&)> func_t;
enum{
    SOCKET_ERR_S=1,
    BIND_ERR_S
};

class udpserver
{
    public:
    udpserver(const string &ip=defaultip,const uint16_t &port=defaultport)
    :socketfd_(0),ip_(ip),port_(port),isrunning_(false)
    {}
    void init()
    {
        socketfd_=socket(PF_INET,SOCK_DGRAM,0);
        if(socketfd_<0)
        {
            lg(Fatal,"socket create error,socketfd: %d",socketfd_);
            exit(SOCKET_ERR_S);
        }
        lg(Info,"socket create success,socketfd: %d",socketfd_);
        struct sockaddr_in local;
        bzero(&local,sizeof(local));
        local.sin_family=AF_INET;
        local.sin_port=htons(port_);
        local.sin_addr.s_addr=inet_addr(ip_.c_str());
        if(bind(socketfd_,(struct sockaddr*)&local,sizeof(local)))
        {
            lg(Fatal,"bind create, errno: %d, error string: %s",errno,strerror(errno));
            exit(BIND_ERR_S);
        }
        lg(Info,"bind create successful, errno: %d, error string: %s",errno,strerror(errno));
    }
    void run()
    {
        isrunning_=true;
        char inbuffer[SIZE];
        while(isrunning_)
        {
            struct sockaddr_in client;
            socklen_t len= sizeof(client);
            //接收client
            ssize_t n=recvfrom(socketfd_,inbuffer,sizeof(inbuffer)-1,0,(sockaddr*)&client,&len);
            if(n<0)
            {
                lg(Warning,"recvfrom error, errno: %d, error string: %s",errno,strerror(errno));
                continue;
            }
            lg(Info,"recvfrom create successful, errno: %d, error string: %s",errno,strerror(errno));
            inbuffer[n]='\0';
            // string info = inbuffer;
            // string echo_string = func(info);
            string echo_string(inbuffer, n);;
            //发回client
            ssize_t m=sendto(socketfd_,echo_string.c_str(),echo_string.size(),0,(struct sockaddr*)&client,len);
              if(m<0)
            {
                lg(Warning,"sendto error, errno: %d, error string: %s",errno,strerror(errno));
                continue;
            }
            lg(Info,"sendto create successful, errno: %d, error string: %s",errno,strerror(errno));
        }
    }
     ~udpserver()
    {}
    private:
    int socketfd_;
    string ip_;
    uint16_t port_;
    bool isrunning_;
};
