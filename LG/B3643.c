#include <stdio.h>
#define MAXN 1002

int graph[MAXN][MAXN]={};

void readgraph(int edgecnt){// 适用于从控制台输入无向边
    for(int i=1;i<=edgecnt;i++){
        int from,to;scanf("%d %d",&from,&to);
        graph[from][to]=1;graph[to][from]=1;}
}

void printgraph(int nodecnt){
    for(int i=1;i<=nodecnt;i++){
        for(int j=1;j<=nodecnt;j++){printf("%d ",graph[i][j]);}
        printf("\n");}
}

int main(){
    int nodecnt,edgecnt;
    scanf("%d %d",&nodecnt,&edgecnt);
    readgraph(edgecnt);
    printgraph(nodecnt);

    for(int i=1;i<=nodecnt;i++){
        int nodedge=0;int nodedgetable[MAXN]={};
        for(int j=1;j<=nodecnt;j++){
            if(graph[i][j]==1){nodedge++;nodedgetable[nodedge]=j;}
        }
        printf("%d ",nodedge);
        for(int k=1;k<=nodedge;k++){printf("%d ",nodedgetable[k]);}
        printf("\n");
    }
}