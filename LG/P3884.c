#include <stdio.h>
#define min(a,b) a < b? a:b
#define MAXN 103

struct BTnode {int data;int left;int right}node[MAXN]={};

int depth(int root){
    int left_depth,right_depth;
    if(root==0){return 0;}
    left_depth=depth(node[root].left);
    right_depth=depth(node[root].right);
    return (left_depth > right_depth) ? left_depth+1: right_depth+1;
}

int maxwidth=0;int widthtable[MAXN]={};
void width(int root,int level){
    if(root==0){return;}
    widthtable[level]++;
    if(widthtable[level]>maxwidth){maxwidth=widthtable[level];}
    width(node[root].right,level+1);
    width(node[root].left,level+1);
}

short findflag=1;// 表示未找到
int stack[MAXN]={};int top=-1;
int ifempty(){return top==-1;}
void push(int item){stack[++top]=item;}
int pop(){return stack[top--];}
void finder(int root,int target){
    if(root==0){return;}// 到了空节点,自动退出
    if(findflag==1){// 核验当前节点
        push(node[root].data);// 序号进栈
        if(node[root].data==target){// 找到了
            findflag=0;return;
        }
    }
    finder(node[root].right,target);
    finder(node[root].left,target);
    if(findflag==1){// 说明当前节点以下无target
        int rubbish = pop();// 我们板子里pop()有返回值需要东西承接否则无法编译
    }
}
int path_1[MAXN]={};int path_2[MAXN]={};
int way(int root,int target,int index){
    findflag=1;top=-1;
    finder(root,target);
    int pathcnt=0;
    while(!ifempty()){
        if(index==1){path_1[pathcnt] = pop();}
        if(index==2){path_2[pathcnt] = pop();}
        pathcnt++;
    }
    // while(pathcnt>=0){printf("%d->",path[pathcnt]);pathcnt--;}
    return pathcnt-1;
}

int main(){
    int total; // total既是节点个数,也决定了到底有多少个边+1.
    scanf("%d",&total);
    for(int i=1;i<=total;i++){node[i].data=i;}
    for(int i=1;i<=total-1;i++){
        int a,b;
        scanf("%d%d",&a,&b);
        if(node[a].left==0){node[a].left=b;}
        else{node[a].right=b;}
    }
    int from,to;
    scanf("%d %d",&from,&to);

    // for(int i=1;i<=total;i++){
    //     printf("name:%d,left:%d,right:%d\n",i,node[i].left,node[i].right);
    // }
    
    printf("%d\n",depth(1));
    width(1,1);
    printf("%d\n",maxwidth);
    int waylen_1 = way(1,from,1);int tmp_1=waylen_1;
    int waylen_2 = way(1,to,2);int tmp_2=waylen_2;
    int commoncnt=0;
    while(waylen_1>=0 && waylen_2 >=0){
        if(path_1[waylen_1] == path_2[waylen_2]){commoncnt++;}
        else{break;}
        waylen_1--;waylen_2--;
    }
    int res = 2*(tmp_1-commoncnt+1)+(tmp_2-commoncnt+1);
    printf("%d",res);
    

    return 0;
}