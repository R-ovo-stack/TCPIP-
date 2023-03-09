#include <stdio.h>
#include <unistd.h>
#include <sched.h>
/**
 * 僵尸进程实例
*/
int main(int argc, char const *argv[])
{
    pid_t pid = fork();  // fork一个子进程

    if (pid == 0)
    {   // 子进程执行逻辑
        /* code */
        puts("Hi , I am a child process");
    }
    else {
        // 父进程执行逻辑
        printf("Child process ID: %d  \n",pid);
        sleep(30);
    }
    if (pid == 0)
    {// 子进程执行逻辑
        /* code */
        puts("End child process");

    }else {
         // 父进程执行逻辑
        puts("End parent process");
        
    }
    

    return 0;
}
