#include <stdio.h>
#include <stdlib.h>
#define MAXN 1000

typedef struct edger{int to;int weight;struct edger* next;}* edge;// 边是指针
typedef struct noder{int data;struct edger* link;}node;// 点的性质是结构体
node graph[MAXN]={};

edge insertedge(int from,int to,int weight){
    edge head = graph[from].link;edge p;
    edge e = (edge) malloc(sizeof(struct edger));
    e->to =to; e-> weight = weight; e->next = NULL;// 链表三步走 
    if(head==NULL){head = e;return head;}
    for(p=head;p->next!=NULL;p = p->next);// 找到链表末尾
    p->next =e; return head;
}

void printgraph(int nodecnt){
    for(int i=1;i<=nodecnt;i++){
        printf("node%d: ",i);
        for(edge p = graph[i].link;p!=NULL;p = p->next){
            printf("%d ",p->to);
        }
        printf("\n");
    }
}
int max=1;
short visit[MAXN]={};
void DFS(int start){
    edge p;visit[start]=1;
    if(start>max){max=start;}// 可自行更改处理逻辑
    for(p = graph[start].link;p!=NULL;p=p->next){
        if(visit[p->to]==0){DFS(p->to);}}}

void travelDFS(int nodecnt){
    for(int i=1;i<=nodecnt;i++){visit[i]=0;}// 保险起见最好初始化
    for(int i=1;i<=nodecnt;i++){if(visit[i]==0){DFS(i);}}// DFS每个联通区间
}



int main(){
    int nodecnt,edgecnt;
    scanf("%d %d",&nodecnt,&edgecnt);
    for(int i=1;i<=edgecnt;i++){
        int from,to;
        scanf("%d %d",&from,&to);
        graph[from].link = insertedge(from,to,1);
    }
    // printgraph(nodecnt);
    for(int i=1;i<=nodecnt;i++){
        max=1;
        DFS(i);
        printf("%d ",max);
        for(int j=1;j<=nodecnt;j++){visit[j]=0;}
    }
    
}