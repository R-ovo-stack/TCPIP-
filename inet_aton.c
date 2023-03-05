#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>

void error_handing(char* message){
    fputs(message,stderr);
    fputc('\n',stderr);
    exit(1);
}


int main(int argc, char const *argv[])
{
    char *addr = "192.168.132.10";
    struct sockaddr_in addr_inet;
    if (!inet_aton(addr,&addr_inet.sin_addr))
    {
        /* code */
        error_handing("Conversion error !");
    }
    else printf("Network ordered integer addr: %#x \n",addr_inet.sin_addr.s_addr);
    
    return 0;
}
