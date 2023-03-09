#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <sched.h>
#include <sys/wait.h>

void read_childproc(int sig)
{
    int status; // 用户存储进程停止的状态标记
    pid_t id = waitpid(-1, &status, WNOHANG);
    if (WIFEXITED(status))
    {
        /* code */
        printf("Remove proc id: %d \n", id);
        printf("Child send: %d  \n", WEXITSTATUS(status));
    }else {
        printf("error ...");
    }
}

int main(int argc, char const *argv[])
{
    pid_t pid;
    struct sigaction act;
    act.sa_handler = read_childproc;
    sigemptyset(&act.sa_mask);
    act.sa_flags = 0;
    sigaction(SIGCHLD, &act, 0); // SIGCHILD定义了子进程终止的情况
    pid = fork();

    if (pid == 0)
    {
        /* code */
        puts("Hi I am child procss!");
        sleep(10);
        return 12;
    }
    else
    {
        printf("Child proc id: %d \n", pid);
        pid = fork();
        if (pid == 0)
        {
            /* code */
            puts("Hi I am child procss!");
            sleep(10);
            return 24;
        }
        else
        {
            int i;
            printf("Child proc id: %d \n", pid);
            for (i = 0; i < 6; i++)
            {
                /* code */
                puts("wait...");
                sleep(5);
            }
        }
    }

    return 0;
}
