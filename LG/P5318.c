#include <stdio.h>
#include <stdlib.h>
#define MAXN 100005

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
short visit[MAXN]={};
void DFS(int start){
    edge p;visit[start]=1;
    printf("%d ",start);// 可自行更改处理逻辑
    for(p = graph[start].link;p!=NULL;p=p->next){
        if(visit[p->to]==0){DFS(p->to);}}}

void travelDFS(int nodecnt){
    for(int i=1;i<=nodecnt;i++){visit[i]=0;}// 保险起见最好初始化
    for(int i=1;i<=nodecnt;i++){if(visit[i]==0){DFS(i);}}// DFS每个联通区间
}

int queue[MAXN]={};
int head;int cnt;int tail;
void initqueue(){head=0;tail=MAXN-1;cnt=0;}
int ifempty(){return (cnt==0 ? 1 : 0);}
void intoqueue(int item){
    tail = (tail+1)%MAXN;
    queue[tail] = item;
    cnt++;}

int outqueue(){
  int target = queue[head];
  head = (head+1)%MAXN;
  cnt--;return target;
}

void BFS(int start){
    edge p;
    printf("%d ",start);// 可自行修改处理逻辑
    visit[start]=1;
    intoqueue(start);
    while(!ifempty()){
        start = outqueue();
        for(p = graph[start].link;p!=NULL;p=p->next){
            if(visit[p->to]==0){
                printf("%d ",p->to);// 可自行修改处理逻辑
                visit[p->to]=1;
                intoqueue(p->to);
            }
        }
    }
}

void travelBFS(int nodecnt){
    initqueue();
    for(int i=1;i<=nodecnt;i++){visit[i]=0;}// 保险起见最好初始化
    for(int i=1;i<=nodecnt;i++){if(visit[i]==0){BFS(i);}}// BFS每个联通区间
}

struct fromto{int fromraw;int toraw};
struct fromto ft[1000005]={};

int cmp(const void *a, const void *b) {
    struct fromto *pa = (struct fromto *)a;
    struct fromto *pb = (struct fromto *)b;
    if (pa->fromraw != pb->fromraw)
        return pa->fromraw - pb->fromraw;
    return pa->toraw - pb->toraw;
}


int main(){
    int nodecnt,edgecnt;
    scanf("%d %d",&nodecnt,&edgecnt);
    for(int i=1;i<=edgecnt;i++){
        int from,to;
        scanf("%d %d",&ft[i].fromraw,&ft[i].toraw);
    }
    // 在 main 中调用：
    qsort(&ft[1], edgecnt, sizeof(struct fromto), cmp);
    for(int i=1;i<=edgecnt;i++){
        graph[ft[i].fromraw].link=insertedge(ft[i].fromraw,ft[i].toraw,1);
    }
    // printgraph(nodecnt);
    DFS(1);
    printf("\n");
    for(int i=1;i<=nodecnt;i++){visit[i]=0;}// 保险起见最好初始化
    initqueue();
    BFS(1);
    
}