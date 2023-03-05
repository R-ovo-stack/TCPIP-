#include <sys/socket.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <stdio.h>

const int BUFSIZE = 1024;

void error_handing(char *message);
int main(int argc, char const *argv[])
{
    int sock;
    struct sockaddr_in serv_addr;
    char message[30];
    int str_len,rec_len = 0,rec_cnt = 0;
    char message_server[BUFSIZE];
    if (argc != 3)
    {
        /* code */
        printf("Usage : %s <port>\n", argv[0]);
        exit(1);
    }

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
    while (1)
    {
        rec_len = 0;
        fputs("Input message(Q to quit): ", stdout);
        fgets(message, BUFSIZE, stdin);
        if (!strcmp(message,"q\n") || !strcmp(message,"Q\n"))
        {
            break;
        }
        
        str_len = write(sock,message,strlen(message));
        while (rec_len < str_len)
        {
            /* code */
            rec_cnt = read(sock, message_server, BUFSIZE- 1);
            // rec_cnt = read(sock, &message_server[rec_len], BUFSIZE- 1);  // 可用
            if (rec_cnt == -1)
            {
                /* code */
                error_handing("reads() error");
            }
            rec_len += rec_cnt;
        }

        message_server[rec_len] = 0;
        printf("Message from server : %s \n", message_server);
        memset(message_server,0,sizeof(message_server));
    }

    close(sock);
    return 0;
}

void error_handing(char *message)
{
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}
