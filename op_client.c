#include <sys/socket.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <stdio.h>

const int RLT_SIZE = 4;// 返回值空间大小
const int BUFSIZE = 1024;
const int OPSIZE = 4; // 发送整形数字
void error_handing(char *message);
int main(int argc, char const *argv[])
{
    int sock;
    struct sockaddr_in serv_addr;
    char opInfo[BUFSIZE];
    int str_len,rec_len = 0,rec_cnt = 0;
    int opra_count = 0;
    if (argc != 3)
    {
        /* code */
        printf("Usage : %s <port>\n", argv[0]);
        exit(1);
    }
    int result;
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
 
    // 发送操作数
    fputs("Operation Count : ",stdout);
    scanf("%d",&opra_count);
    opInfo[0] = (char)opra_count;
    for (size_t i = 1; i <= opra_count; i++)
    {
        /* code */
        printf("opNum %d :",i);
        scanf("%d",(int *)&opInfo[(i-1)*OPSIZE + 1]);  //  + 1是因为已经保存了一位操作数
    }
    fgetc(stdin);
    fputs("Operator fun: ",stdout);
    scanf("%c",&opInfo[opra_count * OPSIZE + 1]);

    write(sock,opInfo,opra_count * OPSIZE + 2);
    read(sock,&result,RLT_SIZE);
    
    printf("Result :　%d \n",result);

    close(sock);
    return 0;
}

void error_handing(char *message)
{
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}
