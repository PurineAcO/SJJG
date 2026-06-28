#include <stdio.h>
#include <stdlib.h>
#define MAXN 105
#define ll long long

int queue[MAXN]={};
int head;int cnt;int tail;
void initqueue(int mem){
  head=0;tail=mem-1;cnt=0;
for(int i=0;i<MAXN;i++){queue[i]=-114514;}
}
void intoqueue(int item,int mem){
    tail = (tail+1)%mem;
    queue[tail] = item;
    cnt++;}

int ifin(int word,int mem){
    for(int i=0;i<mem;i++){if(queue[i]==word){return 1;}}
    return 0;
}

int main(){

    int mem,word;ll otcnt=0;
    scanf("%d %d",&mem,&word);
    initqueue(mem);
    for(int i=1;i<=word;i++){
        int thisword;
        scanf("%d",&thisword);
        if(ifin(thisword,mem)){continue;}
        else{intoqueue(thisword,mem);otcnt++;}
    }
    printf("%lld",otcnt);
    
    return 0;
}