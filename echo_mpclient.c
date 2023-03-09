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
 * 回声客户端分割Tcp的I/O示例
 * 通过父子进程进行分离读写
*/
const int BUFSIZE = 30;

void read_routine(int sock, char *buf);
void write_routine(int sock, char *buf);
void error_handing(char *message);
int main(int argc, char const *argv[])
{
    int sock;
    struct sockaddr_in serv_addr;
    char message[BUFSIZE];
    int str_len, rec_len = 0, rec_cnt = 0;
    char message_server[BUFSIZE];
    if (argc != 3)
    {
        /* code */
        printf("Usage : %s <port>\n", argv[0]);
        exit(1);
    }

    pid_t pid;

    // 创建套接字，但此时套接字并不马上分为服务器端和客户端。
    // 如果紧接着调用bind、listen函数，将成为服务器端套接字;
    // 如果调用connect函数，将成为客户端套接字。
    sock = socket(PF_INET, SOCK_STREAM, 0);
    if (sock == -1)
    {
        /* code */
        error_handing("socket() error");
    }
    memset(&serv_addr, 0, sizeof(serv_addr));

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr(argv[1]);
    serv_addr.sin_port = htons(atoi(argv[2]));

    // 调用connect函数向服务器端发送连接请求。
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) == -1)
    {
        error_handing("connect() error");
    }
    else
    {
        puts("Connected.........");
    }

    pid = fork();
    if (pid == 0)
    {
        /* code */
        // 子进程进行写
        write_routine(sock, message);
    }
    else
        read_routine(sock, message);  // 父进程进行读
    close(sock);
    return 0;
}

void error_handing(char *message)
{
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}

void read_routine(int sock, char *buf)
{
    while (1)
    {
        int str_len = read(sock, buf, BUFSIZE);
        if (str_len == 0)
        {
            /* code */
            return;
        }
        buf[str_len] = 0;
        printf("Message from server : %s \n", buf);
    }
}
void write_routine(int sock, char *buf)
{
    while (1)
    {
        fgets(buf, BUFSIZE, stdin);
        if (!strcmp(buf, "q\n") || !strcmp(buf, "Q\n"))
        {
            shutdown(sock, SHUT_WR); // 关闭写
            break;
        }

        write(sock, buf, strlen(buf)); // 写
    }
}