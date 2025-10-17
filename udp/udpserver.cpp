#include "udpserver.hpp"
#include <iostream>
#include <memory>
using namespace std;
void usage(string proc)
{
    cout<<"usage: "<<proc<<" port\n"<<endl;

}
// ./udpserver port
int main(int argc,char*argv[])
{
    if(argc != 2)
    {
        usage(argv[0]);
        exit(0);
    }
    uint16_t port = std::stoi(argv[1]);
    auto svr = make_unique<udpserver> ("0.0.0.0",port);
    svr->init();
    svr->run();
    return 0;
}
