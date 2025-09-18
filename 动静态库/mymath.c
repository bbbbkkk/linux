#include "mymath.h"
int errornum=0;
int add(int x,int y)
{
    return x+y;
}
int sub(int x,int y)
{
    return x-y;
}
int mul(int x,int y)
{
    return x*y;
}
int div(int x,int y)
{
    if(y==0)
    {
        errornum=-1;
        return -1;
    }
    return x/y;
}
