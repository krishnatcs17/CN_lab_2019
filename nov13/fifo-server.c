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

    if(mkfifo(fifo1, PERMS) < 0)
        printf("Can't create FIFO1\n");
    if(mkfifo(fifo2, PERMS) < 0)
        printf("Can't create FIFO2\n");

    printf("Waiting for connection request from the client. . .\n");
    readfd = open(fifo1, O_RDONLY, 0);
    writefd = open(fifo2, O_WRONLY, 0);
    printf("Connection established\n");
    read(readfd, fname, 255);
    printf("Requested file name: %s\n", fname);
    if((fd = open(fname, O_RDWR, 0)) < 0) {
        strcpy(buff, "File doesn't exist\n");
        write(writefd, buff, strlen(buff));
    }
    else {
        while(( n = read(fd, buff, 512)) > 0)
            write(writefd, buff, n);
    }
    close(readfd);
    unlink(fifo1);
    close(writefd);
    unlink(fifo2);
}