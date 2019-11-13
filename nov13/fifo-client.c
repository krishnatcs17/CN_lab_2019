#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<string.h>

#define fifo1 "fifo1"
#define fifo2 "fifo2"
#define PERMS 0666 // 0usergroupothers

char fname[256];

int main()
{
    int readfd, writefd, fd;
    char buff[512];
    ssize_t n;
    printf("Connecting to server..\n");
    writefd = open(fifo1, O_WRONLY, 0);
    readfd = open(fifo2, O_RDONLY, 0);
    printf("Connection established.\n");
    
    printf("Enter the file name: ");
    scanf("%s", fname);
    write(writefd, fname, strlen(fname));
    printf("waiting for the reply..\n");

    while((n = read(readfd, buff, 512)) > 0) {
        write(1, buff, n);
    }
    close(readfd);
    close(writefd);
}