#include <sys/socket.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <stdio.h>

#define BUFSIZE 30
void error_handing(char *message);
int main(int argc, char const *argv[])
{
    int sock;
    struct sockaddr_in serv_addr;
    char message[BUFSIZE];
    char filename[30];
    int str_len;
    FILE *fp;
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
    printf("输入另存为文件名: ");
    scanf("%s", filename);
    fp = fopen(filename, "wb");
    int rec_cnt;
    while ((rec_cnt = read(sock, message, BUFSIZE)) != 0)
    {
        fwrite((void *)message, 1, rec_cnt, fp);
    }
    puts("Recived file data...");
    write(sock,"Thank you",BUFSIZE);
    printf("Message from server : %s \n", message);
    fclose(fp);
    close(sock);
    return 0;
}

void error_handing(char *message)
{
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}
