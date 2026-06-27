#include <stdio.h>
#define MAXN 1000009

struct BTnode{
    int left;
    int data;
    int right;
};// 这是一种用数组代替链表式二叉树的方法.

struct BTnode node[MAXN]={};

void preorder(int root){
    if(root==0){return;}
    printf("%d ",node[root].data);
    preorder(node[root].left);
    preorder(node[root].right);
}

void afterorder(int root){
    if(root==0){return;}
    afterorder(node[root].left);
    afterorder(node[root].right);
    printf("%d ",node[root].data);
}

void midorder(int root){
    if(root==0){return;}
    midorder(node[root].left);
    printf("%d ",node[root].data);
    midorder(node[root].right);
}

int main(){
    int total;
    scanf("%d",&total);
    for(int i=1;i<=total;i++){
        node[i].data=i;
        scanf("%d %d",&node[i].left,&node[i].right);}
    preorder(1);
    printf("\n");
    midorder(1);
    printf("\n");
    afterorder(1);
}