#include <sys/socket.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <netdb.h>
void error_handing(char *message);
int main(int argc, char const *argv[])
{
    int i = 0;
    struct hostent * host;
    if (argc != 2)
    {
        /* code */https://www.google.com/search?q=132&oq=132&aqs=chrome..69i57j0i512l5j69i65l2.858j0j7&sourceid=chrome&ie=UTF-8
        printf("Usage : %s <port>\n", argv[0]);
        exit(1);
    }
    // /*
    //  偷懒做法
        in_addr_t addr = inet_addr(argv[1]);
        host = gethostbyaddr((void*)&addr,4,AF_INET);
    // */
    // struct sockaddr_in addr;
    // memset(&addr,0,sizeof(addr));
    // addr.sin_addr.s_addr = inet_addr(argv[1]);
    // host = gethostbyaddr((char*)&addr.sin_addr,4,AF_INET);

    if (!host)
    {
        /* code */
        error_handing("getHost... error");
        
    }
    printf("Official name: %s \n",host->h_name);
    for (i = 0;host -> h_aliases[i]; i++)
    {
        /* code */
        printf("Aliases %d: %s  \n",i+1,host->h_aliases[i]);
    }
    
    printf("AddrType: %s  \n",(host -> h_addrtype == AF_INET) ? "AF_INET":"AF_INET6");

    for ( i = 0; host -> h_addr_list[i]; i++)
    {
        printf("IP addr %d : %s  \n",i+1, inet_ntoa(*(struct in_addr*)host -> h_addr_list[i]));
    }
    
    return 0;
}

void error_handing(char *message)
{
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}
