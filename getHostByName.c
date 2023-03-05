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
        /* code */
        printf("Usage : %s <port>\n", argv[0]);
        exit(1);
    }

    host = gethostbyname(argv[1]);
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
