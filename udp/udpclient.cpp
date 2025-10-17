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
using namespace std;
Log lg;
enum{
    SOCKET_ERR_C=1
};
void usage(string proc)
{
    cout<<"usage: "<<proc<<" serverip serverport\n"<<endl;

}
// ./udpclient serverip serverport
int main(int argc,char*argv[])
{

    if(argc!=3)
    {
        usage(argv[0]);
        exit(0);
    }
    string serverip=argv[1];
    uint16_t serverport=stoi(argv[2]);
     struct sockaddr_in server;
    bzero(&server, sizeof(server));
    server.sin_family = AF_INET;
    server.sin_port = htons(serverport); 
    server.sin_addr.s_addr = inet_addr(serverip.c_str());
    socklen_t server_len = sizeof(server);

    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0)
    {
        lg(Info,"socket_client create error, errno: %d, error string: %s",errno,strerror(errno));
        exit(SOCKET_ERR_C);
    }
    string message;
    char buffer[1024];
    while (true)
    {
        cout << "Please Enter@ ";
        getline(cin, message);
        sendto(sockfd, message.c_str(), message.size(), 0, (struct sockaddr *)&server, server_len);
        
        struct sockaddr_in temp;
        socklen_t len = sizeof(temp);
        memset(buffer, 0, sizeof(buffer));

        ssize_t s = recvfrom(sockfd, buffer, 1024, 0, (struct sockaddr*)&temp, &len);
        if(s > 0)
        {
            buffer[s]='\0';
            cout << "Server echo: " << buffer << endl;
        }
    }
    close(sockfd);
    return 0;
}
