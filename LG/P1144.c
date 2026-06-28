#include <stdio.h>
#include <stdlib.h>
#define MAXN 1000009
#define INF 0x3F3F3F3F

typedef struct edger{
  int to;
  int weight;// 权重
  struct edger* next;}* edge;
  // 边的性质是指针

typedef struct noder{
  int data;
  struct edger* link;}node;
// 点的性质是结构体

node graph[MAXN]={};

edge insertedge(int from,int to,int weight){
  // 在使用时,应该由graph[from].link来承接返回值否则无法插入边
    edge head = graph[from].link;edge p;
    edge e = (edge) malloc(sizeof(struct edger));
    e->to =to; e-> weight = weight; e->next = NULL;// 链表三步走 
    if(head==NULL){head = e;return head;}
    for(p=head;p->next!=NULL;p = p->next);// 找到链表末尾
    p->next =e; return head;}

void printgraph(int nodecnt){// 检查图的内容
  for(int i=1;i<=nodecnt;i++){
      printf("node%d: ",i);
      for(edge p = graph[i].link;p!=NULL;p = p->next){
          printf("%d ",p->to);}
      printf("\n");}}

int cnt[MAXN]={};
void dijkstra(int src, int n) {
    int dist[MAXN];int visited[MAXN] = {};
    for (int i = 1; i <= n; i++) {dist[i] = INF;}
    dist[src] = 0;// src离自己的距离是0
    cnt[src]=1;// src自己到自己就只有1种走法

    for (int i = 1; i <= n; i++) {
        // 第一步:选出未访问且dist最小的点u(最开始显然是src)
        int u = -1;int min_dist = INF;
        for (int j = 1; j <= n; j++) {
            if (!visited[j] && dist[j] < min_dist) {
                min_dist = dist[j];
                u = j;}}
        if (u == -1) {break;}   // 剩余点不可达（图不连通）
        // 第二步:标记u已访问
        visited[u] = 1;
        // 第三步:用u的邻接边更新其邻接点v的dist
        for (edge p = graph[u].link; p != NULL; p = p->next) {
            int v = p->to;
            int w = p->weight;
            if (!visited[v] && dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;cnt[v]=cnt[u];}
            else if(!visited[v] && dist[u] + w == dist[v]){cnt[v]+=cnt[u];}
        }
    }
}

int main(){
    int nodecnt,edgecnt;
    scanf("%d %d",&nodecnt,&edgecnt);
    for(int i=1;i<=edgecnt;i++){
        int from,to;
        scanf("%d %d",&from,&to);
        graph[from].link = insertedge(from,to,1);
        graph[to].link = insertedge(to,from,1);
    }
    // printgraph(nodecnt);
    dijkstra(1,nodecnt);
    for(int i=1;i<=nodecnt;i++){
        printf("%d\n",cnt[i]);
    }

    return 0;
}