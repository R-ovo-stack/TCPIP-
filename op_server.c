#include <sys/socket.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <stdio.h>

const int OPSIZE = 4; // 发送整形数字
const int BUFSIZE = 1024;
int calculte(int cnt, int opinfo[], char op);
void error_handing(char *message);
int main(int argc, char *argv[])
{
    int serv_sock;
    int clnt_sock;

    struct sockaddr_in serv_addr; // 服务器地址
    struct sockaddr_in clnt_addr; // 客户端地址

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

    clnt_addr_size = sizeof(clnt_addr);
    for (size_t i = 0; i < 5; i++)
    {
        // 调用accept函数受理连接请求。如果在没有连接请求的情况下调用该函数，则不会返回，直到有连接请求为止。
        clnt_sock = accept(serv_sock, (struct sockaddr *)&clnt_addr, &clnt_addr_size);
        int cnt = 0;
        int result = 0;
        if (clnt_sock == -1)
        {
            /* code */
            error_handing("accept() error");
        }
        else
        {
            printf("Connected client %d \n", i++);
        }

        printf("等待计算请求...\n");

        read(clnt_sock, &cnt, 1);
        int recv_cnt = 0;
        int rec_len = 0;
        while ((cnt * OPSIZE + 1) > rec_len)
        {
            recv_cnt = read(clnt_sock, &message[rec_len], OPSIZE);
            rec_len += recv_cnt;
        }
        printf("message info : %s \n",message);
        result = calculte(cnt, (int *)message, message[rec_len - 1]);
        write(clnt_sock,&result,sizeof(result));
        close(clnt_sock);
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

int calculte(int cnt, int opinfo[], char op)
{
    int result = opinfo[0], i;
    switch (op)
    {
    case '+':
        for (i = 1; i < cnt; i++)
        {
            /* code */
            result += opinfo[i];
        }
        return result;
    case '-':
        for (i = 1; i < cnt; i++)
        {
            /* code */
            result -= opinfo[i];
        }
    case '*':
        for (i = 1; i < cnt; i++)
        {
            /* code */
            result *= opinfo[i];
        }
        return result;
    case '/':
        for (i = 1; i < cnt; i++)
        {
            /* code */
            result /= opinfo[i];
        }
        return result;
    default:
        break;
    }
}