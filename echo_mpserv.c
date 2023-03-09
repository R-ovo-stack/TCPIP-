#include <sys/socket.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <sched.h>
#include <sys/wait.h>

/**
 * 回声服务器的并发实现
 * 多进程
*/
const int BUFSIZE = 1024;
void read_childproc(int sig);
void error_handing(char *message);
int main(int argc, char *argv[])
{
    int serv_sock;
    int clnt_sock;

    pid_t pid;
    struct sockaddr_in serv_addr; // 服务器地址
    struct sockaddr_in clnt_addr; // 客户端地址

    struct sigaction act;
    act.sa_handler = read_childproc;
    sigemptyset(&act.sa_mask);
    act.sa_flags = 0;
    sigaction(SIGCHLD, &act, 0); // SIGCHILD定义了子进程终止的情况

    socklen_t clnt_addr_size; //
    int size_len;
    char message[BUFSIZE];
    if (argc != 2)
    {
        /* code */
        printf("Usage : %s <port>\n", argv[0]);
        exit(1);
    }

    // 调用socket函数创建套接字。
    serv_sock = socket(PF_INET, SOCK_STREAM, 0);
    if (serv_sock == -1)
    {
        /* code */
        error_handing("socket() error");
    }

    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(atoi(argv[1]));
    // 调用bind函数分配IP地址和端口号。
    if (bind(serv_sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) == -1)
    {
        /* code */
        error_handing("bind() error");
    }
    // 调用listen函数将套接字转为可接收连接状态。
    if (listen(serv_sock, 5) == -1)
    {
        /* code */
        error_handing("listen() error");
    }

    while (1)
    {
        clnt_addr_size = sizeof(clnt_addr);

        // 调用accept函数受理连接请求。如果在没有连接请求的情况下调用该函数，则不会返回，直到有连接请求为止。
        clnt_sock = accept(serv_sock, (struct sockaddr *)&clnt_addr, &clnt_addr_size);

        if (clnt_sock == -1)
        {
            /* code */
            continue;
        }
        else
        {
            printf("Connected client connected...\n");
        }
        // 多进程处理
        // 接收到Accept时
        pid = fork();
        if (pid == -1)
        {
            /* code */
            close(clnt_sock);
            continue;
        }

        if (pid == 0)
        { // 子进程运行区
            /* code */
            close(serv_sock); // 关闭子进程的 服务端Socket
            // 只需要 clnt_sock 进行读写
            while ((size_len = read(clnt_sock, message, sizeof(message) - 1)) != 0)
            {
                /* code */
                write(clnt_sock, message, size_len);
            }
            close(clnt_sock);
            puts("client disconnected .....");
            return 0;
        }
        else
        {
            close(clnt_sock);
        }
    }

    close(serv_sock);

    return 0;
}

void error_handing(char *message)
{
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}
void read_childproc(int sig)
{
    int status; // 用户存储进程停止的状态标记
    pid_t id = waitpid(-1, &status, WNOHANG);
    if (WIFEXITED(status))
    {
        /* code */
        printf("Remove proc id: %d \n", id);
        printf("Child send: %d  \n", WEXITSTATUS(status));
    }
    else
    {
        printf("error ...");
    }
}