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
void keycontrol(int sig){
    if (sig == SIGINT)
    {
        /* code */
        puts("CTRL + C  Pressed");
    }
}
int main(int argc, char const *argv[])
{
    /* code */
    int i;
    signal(SIGALRM,timeout);
    signal(SIGINT,keycontrol);
    alarm(2);
    
    for ( i = 0; i < 3; i++)
    {
        /* code */
        puts("wait ...");
        sleep(100);
    }
    
    return 0;
}
