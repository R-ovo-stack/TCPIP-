#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>


/**
 * 获取socket的类型
*/
void error_handing(char* message);
int main(int argc, char const *argv[])
{
    int tcp_sock,udp_sock;
    int sock_type;
    socklen_t optlen;

    int state;

    optlen = sizeof(sock_type);
    tcp_sock =socket(PF_INET,SOCK_STREAM,0);
    udp_sock = socket(PF_INET,SOCK_DGRAM,0);
    printf("SOCK_STREAM: %d \n",SOCK_STREAM);
    printf("SOCK_DGRAM: %d \n",SOCK_DGRAM);

    state = getsockopt(tcp_sock,SOL_SOCKET,SO_TYPE,(void*)&sock_type,&optlen);
    if (state)
        error_handing("getsockopt() error !");
    printf("Socket type one: %d \n",sock_type);
    
    state = getsockopt(udp_sock,SOL_SOCKET,SO_TYPE,(void*)&sock_type,&optlen);
    if (state)
        error_handing("getsockopt() error !");
    printf("Socket type two: %d \n",sock_type);
    // “套接字类型只能在创建时决定，以后不能再更改。”

    return 0;
}

void error_handing(char* message){
    fputs(message,stderr);
    fputc("\n",stderr);
    exit(1);
}