#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

void error_handing(char * message);
int main(int argc, char const *argv[])
{
    int fd;
    char buf[] = "Let'sgo !\n";

    fd = open("data.txt",O_CREAT | O_WRONLY | O_TRUNC);
    if (fd == -1)
    {
        /* code */
        error_handing("open() error !");
    }
    printf("file descriptor: %d \n",fd);

    if (write(fd,buf,sizeof(buf)) == -1)
    {
        /* code */
        error_handing("write() error !");
    }
    close(fd);
    return 0;
    
    return 0;
}

void error_handing(char* message){
    fputs(message,stderr);
    fputc('\n',stderr);
    exit(1);
}

