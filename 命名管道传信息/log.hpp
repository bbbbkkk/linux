//设计打印格式和去向
#pragma once
#include <iostream>
#include <sys/stat.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdarg.h>
#include <time.h>
using namespace std;
#define SIZE 1024

#define Screen  1
#define Info    0
#define Debug   1
#define Warning 2
#define Error   3
#define Fatal   4

#define Screen  1
#define Onefile 2
#define Classfile 3

#define LogFile "log.txt"

 class Log
 {
    public:
        Log()
        :printfmethod(Screen),
        path("./log/")
        {}
        void Enable(int method)
        {
            printfmethod=method;
        }
        string levelToString(int level)
        {
            switch(level)
            {
                case Info:
                return "Info";
                case Debug:
                return "Debug";
                case Warning:
                return "Warning";
                case Error:
                return "Error";
                case Fatal:
                return "Fatal";
                default:
                return "None";
            }
        }
        void printflog(int level,const string &logtxt)
        {

            switch(printfmethod)
            {
                case Screen:
                cout<<logtxt<<endl;
                break;
                case Onefile:
                printfOnefile(LogFile,logtxt);
                break;
                case Classfile:
                printfClassfile(level,logtxt);
                break;
                default:  
                break;
            }
        }

        void printfOnefile(const string &logname,const string &logtxt)
        {
            string _logname=path+logname;
            int fd=open(_logname.c_str(),O_WRONLY|O_CREAT|O_APPEND,0666);
            if(fd<0)
            {
                return;
            }
            write(fd,logtxt.c_str(),logtxt.size());
            close(fd);
        }

        void printfClassfile(int level,const string &logtxt)
        {
            string _filename=LogFile;
            _filename+='.';
            _filename+=levelToString(level);
            printfOnefile(_filename,logtxt);
        }
        void operator()(int level,const char*format,...)
        {
            time_t t=time(nullptr);
            struct tm*ctime=localtime(&t);
            char leftbuffer[SIZE];
            snprintf(leftbuffer,sizeof(leftbuffer),"[%s][%d-%d-%d %d:%d:%d]",
            levelToString(level).c_str(),
            ctime->tm_year+1900,
            ctime->tm_mon+1,
            ctime->tm_mday,
            ctime->tm_hour,ctime->tm_min,
            ctime->tm_sec);
            va_list s;
            va_start(s,format);
            char rightbuffer[SIZE];
            vsnprintf(rightbuffer,sizeof(rightbuffer),format,s);
            va_end(s);
            char logtxt[SIZE*2];
            //左右信息整合
            snprintf(logtxt,sizeof(logtxt),"%s %s\n",leftbuffer,rightbuffer);
            //输出去向
            printflog(level,logtxt);
        }
        ~Log()
        {}

    private:
        int printfmethod;
        string path;

    
 };
