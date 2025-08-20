#include "processbar.h"
#include <unistd.h>
int main()
{
    int cnt= 10;
    while(cnt>=0)
    {
        printf("%-2d\r",cnt);
        fflush(stdout);//立即刷新到屏幕上
        cnt--;
        sleep(1);//睡眠一秒
    }
    printf("\n");
    return 0;

}
