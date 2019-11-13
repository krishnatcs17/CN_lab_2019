#include<cstdlib>
#include<iostream>
#include <unistd.h>
#include<stdlib.h>
#include<stdio.h>

#define bktSize 512

void bktInput(int pSize, int opRate)
{
    if(pSize > bktSize) {
        printf("Bucket overflow\n");
    }
    else {
        usleep(500000);
        while(pSize > opRate) {
            printf("\n\t%d bytes ouputted.", opRate);
            pSize -= opRate;
            usleep(500000);
        }
        if(pSize > 0) {
            printf("\n\tLast %d bytes outputted", pSize);
        }
        printf("\nBucket ouput successful\n");
    }
}

int main() 
{
    int opRate, pSize;
    printf("Enter output rate: ");
    std::cin>>opRate;
    for(int i=0; i<5; i++) {
        usleep(1000 * (rand()%1000));
        pSize = rand() % 1000;
        std::cout<<"\nPacket no: "<< i+1 <<", Packet size: "<< pSize<<std::endl;
        bktInput(pSize, opRate);
    }
    return 0;
}