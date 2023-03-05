#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#define BUF_SIZE 100

void error_handing(char *message);
int main(int argc, char const *argv[])
{
    int fd;
    char buf[BUF_SIZE];

    fd = open("data.txt", O_RDONLY);
    if (fd == -1)
    {
        error_handing("open() error!");
    }

    printf("file descriptor: %d \n", fd);

    if (read(fd, buf, sizeof(fd)) == -1)
    {
        error_handing("read() error!");
    }

    printf("file data: %s   \n",buf);
    close(fd);
    return 0;
}

void error_handing(char *message)
{
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}
