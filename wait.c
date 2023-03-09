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
        return 3;
    }

    else
    {
        printf("Child PID: %d \n", pid);
        pid = fork();
        if (pid == 0)
        {
            /* code */
            exit(7);
        }
        else
        {
            printf("Child PID: %d \n", pid);
            wait(&status);
            if (WIFEXITED(status))
            {
                printf("Child Send one: %d  \n", WEXITSTATUS(status));
                /* code */
            }
            wait(&status);
            if (WIFEXITED(status))
            {
                printf("Child Send two: %d  \n", WEXITSTATUS(status));
            }
            sleep(30);
        }
    }
    return 0;
}
