#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>

/**
 * 设置socket I/O缓冲值大小
*/
void error_handing(char *message);
int main(int argc, char const *argv[])
{
    int sock;
    int snd_buf = 1024*3, rcv_buff = 1024*3, state;
    socklen_t len;

    sock = socket(PF_INET, SOCK_STREAM, 0);
    len = sizeof(snd_buf);

    state = setsockopt(sock, SOL_SOCKET, SO_RCVBUF, (void *)&rcv_buff, sizeof(rcv_buff));
    if (state)
        error_handing("setsockopt() error !");

    state = setsockopt(sock, SOL_SOCKET, SO_SNDBUF, (void *)&snd_buf, sizeof(snd_buf));
    if (state)
        error_handing("getsockopt() error !");


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

    /**
     * 输出结果跟我们预想的完全不同，但也算合理。缓冲大小的设置需谨慎处理，
     * 因此不会完全按照我们的要求进行，只是通过调用setsockopt函数向系统传递我们的要求。
     * 如果把输出缓冲设置为0并如实反映这种设置，TCP协议将如何进行?
     * 如果要实现流控制和错误发生时的重传机制，至少要有一些缓冲空间吧?
     * 上述示例虽没有100%按照我们的请求设置缓冲大小，但也大致反映出了通过setsockopt函数设置的缓冲大小。
    */

    return 0;
}

void error_handing(char *message)
{
    fputs(message, stderr);
    fputc("\n", stderr);
    exit(1);
}