#include <stdio.h>
#include <stdlib.h>
#define MAXN 100005
// 本题需要反向建立graph

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
// int max=1;
int ans[MAXN]={};
short visit[MAXN]={};
void DFS(int start,int val){
    edge p;visit[start]=1;
    ans[start]=val; // 可自行更改处理逻辑
    for(p = graph[start].link;p!=NULL;p=p->next){
        if(visit[p->to]==0){DFS(p->to,val);}}}

// void travelDFS(int nodecnt){
//     for(int i=1;i<=nodecnt;i++){visit[i]=0;}// 保险起见最好初始化
//     for(int i=1;i<=nodecnt;i++){if(visit[i]==0){DFS(i);}}// DFS每个联通区间
// }

int main(){
    int nodecnt,edgecnt;
    scanf("%d %d",&nodecnt,&edgecnt);
    for(int i=1;i<=edgecnt;i++){
        int from,to;
        scanf("%d %d",&from,&to);
        graph[to].link = insertedge(to,from,1);
    }
    // printgraph(nodecnt);
    for(int i=nodecnt;i>=1;i--){
        // max=1;
        if(visit[i]==0){DFS(i,i);}
        // 不再需要重置visited,相反需要一个高分栈.
    }
    for(int i=1;i<=nodecnt;i++)printf("%d ",ans[i]);
    
}