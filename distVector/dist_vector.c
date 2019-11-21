#include<stdio.h>
#include<stdlib.h>
struct Node {
    unsigned int dist[20];
    unsigned int from[20];
} route[10];

int main()
{
    int costmat[20][20];
    int nodes, i, j, k, flag;
    printf("\nNumber of nodes : ");
    scanf("%d", &nodes);
    printf("\nEnter the cost matrix :\n");

    for(i=0; i<nodes; i++) {
        for(j=0; j<nodes; j++) {
            scanf("%d", &costmat[i][j]);
            route[i].dist[j] = costmat[i][j];
            route[i].from[j] = j;
        }
    }

    do {
        flag = 0;
        for(i=0; i<nodes; i++)
            for(j=0; j<nodes; j++)
                for(k=0; k<nodes; k++)
                    if(route[i].dist[j] > costmat[i][k] + route[k].dist[j]) 
                    {
                        route[i].dist[j]  = route[i].dist[k] + route[k].dist[j];
                        route[i].from[j] = k;
                        flag = 1;
                    }
    } while(flag);

    for(i=0; i < nodes; i++) {
        printf("\n\nFor router %d:",i+1);
        for(j=0; j < nodes; j++) {
            if(i == j)
                continue;
            if(j == route[i].from[j]) {
                printf("\t\nDirect path to node %d, distance=%d", j+1, route[i].dist[j]);
                continue;
            }
            printf("\t\nTo node %d via %d, Distance=%d ", j+1, route[i].from[j]+1, route[i].dist[j]);
        }
    }
    printf("\n\n");
    return 0;
}

/*
OUTPUT

Number of nodes : 3

Enter the cost matrix :
0 3 2
3 0 6
2 6 0


For router 1:
Direct path to node 2, distance=3
Direct path to node 3, distance=2

For router 2:
Direct path to node 1, distance=3
To node 3 via 1, Distance=5

For router 3:
Direct path to node 1, distance=2
To node 2 via 1, Distance=5

*/