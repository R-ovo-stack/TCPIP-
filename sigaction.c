#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <sched.h>

/**
 * 信号处理
*/
void timeout(int sig){
    if (sig == SIGALRM)
    {
        /* code */
        puts("Time out!");
    }
    alarm(2);
}
int main(int argc, char const *argv[])
{
    int i;
    struct sigaction act;
    act.sa_handler = timeout;
    sigemptyset(&act.sa_mask); // 给act的sa_mask传0
    act.sa_flags = 0;  
    sigaction(SIGALRM,&act,0); // 定义信号,当倒计时2秒后,执行timeout函数
    alarm(2);

    for (i = 0; i < 3; i++)
    {
        /* code */
        puts("wait...");
        sleep(100);
        
    }
    
    
    return 0;
}
