#include <stdio.h>
#include <stdlib.h>
#define MAXN 5005
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

int prim(int n) {
    int dist[MAXN];       // 各节点到当前生成树的最小边权
    int visited[MAXN] = {};
    int sum = 0;

    for (int i = 1; i <= n; i++) dist[i] = INF;// 所有点先保持未联通INF
    dist[1] = 0; // 起点已经在生成树里了,所以是0(默认起点为1号位)

    for (int i = 1; i <= n; i++) {
        // 第一步:找出未访问且dist最小的节点u(u的序号也尽可能小了)
        int u = -1, min = INF;
        for (int j = 1; j <= n; j++) {
            if (!visited[j] && dist[j] < min) {
                min = dist[j];
                u = j;
            }
        }
        if (u == -1) return -1;   // 图不连通

        // 第二步:将u加入生成树
        visited[u] = 1;
        sum += dist[u];

        // 第三步:用u的邻接边更新其他节点的 dist
        for (edge p = graph[u].link; p != NULL; p = p->next) {
            int v = p->to;
            if (!visited[v] && p->weight < dist[v]) {
                dist[v] = p->weight;
            }
        }
    }
    return sum;
}

int main(){
    int nodecnt,edgecnt;
    scanf("%d %d",&nodecnt,&edgecnt);
    for(int i=1;i<=edgecnt;i++){
        int from,to,weight;
        scanf("%d %d %d",&from,&to,&weight);
        graph[from].link = insertedge(from,to,weight);
        graph[to].link = insertedge(to,from,weight);
    }
    // printgraph(nodecnt);

    int sum = prim(nodecnt);
    if(sum>=0){printf("%d",sum);}
    else if(sum==-1){printf("orz");}
    
}