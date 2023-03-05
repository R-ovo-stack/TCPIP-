#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>


/**
 * 获取socket的I/O缓冲区大小
*/
void error_handing(char *message);
int main(int argc, char const *argv[])
{
    int sock;
    int snd_buf, rcv_buff, state;
    socklen_t len;

    sock = socket(PF_INET, SOCK_STREAM, 0);
    len = sizeof(snd_buf);

    state = getsockopt(sock, SOL_SOCKET, SO_SNDBUF, (void *)&snd_buf, &len);
    if (state)
        error_handing("getsockopt() error !");

    len = sizeof(rcv_buff);
    state = getsockopt(sock, SOL_SOCKET, SO_RCVBUF, (void *)&rcv_buff, &len);
    if (state)
        error_handing("getsockopt() error !");
    printf("Input buffer size:  %d \n", rcv_buff);
    printf("Output buffer size:  %d \n", snd_buf);

    // “套接字类型只能在创建时决定，以后不能再更改。”

    return 0;
}

void error_handing(char *message)
{
    fputs(message, stderr);
    fputc("\n", stderr);
    exit(1);
}