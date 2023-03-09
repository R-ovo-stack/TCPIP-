#include <stdio.h>
#include <unistd.h>
#include <sched.h>
#include <stdlib.h>
#include <sys/wait.h>

/**
 * 销毁僵尸进程
*/
int main(int argc, char const *argv[])
{
    int status;
    pid_t pid = fork();

    if (pid == 0)
    {
        /* code */
        sleep(15);
        return 24;
    }
    else
    {
        while (!waitpid(-1, &status, WNOHANG))
        {
            /* code */
            sleep(3);
            printf("sleep 3 sec  \n");
        }
        if (WIFEXITED(status))
        {
            /* code */
            printf("Child send %d  \n", WEXITSTATUS(status));
        }
    }

    return 0;
}
