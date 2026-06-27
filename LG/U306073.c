#include <stdio.h>
#define MAXN 10009

typedef struct rabbit{
    int time;int car;
}info;

info queue[MAXN]={};
int head;int cnt;int tail;

int ifempty(){
    return (cnt==0 ? 1 : 0);
}

void initqueue(){
    head=0;tail=MAXN-1;cnt=0;
}

void intoqueue(info item){
    tail = (tail+1)%MAXN;
    queue[tail] = item;
    cnt++;
}

info outqueue(){
    info target = queue[head];
    head = (head+1)%MAXN;
    cnt--;
    return target;
}

int main(){
    int total;
    initqueue();
    info rabinfo[MAXN]={};
    scanf("%d",&total);
    for(int i=1;i<=total;i++){scanf("%d",&rabinfo[i].time);}
    for(int i=1;i<=total;i++){scanf("%d",&rabinfo[i].car);}
    int oksignal=0;int time=0;int readtmp=1;long long totaltime=0;
    while(oksignal<total){
        // 寻找合适的目标入队,第一部分是新来的.
        for(int i=readtmp;i<=total;i++){
            if(rabinfo[i].time == time){intoqueue(rabinfo[i]);}
            if(rabinfo[i].time > time){readtmp=i;break;}
        }

        // 累加等待时间
        totaltime+=cnt;
        // printf("time:%d %d %d %d\n",time,tail,head,cnt);
        time++;
        
        // 处理第一个目标,并将其出队
        queue[head].car--;
        if(!ifempty()){
            info e=outqueue();
            if(e.car>0){intoqueue(e);}
            else if(e.car==0){oksignal++;}
        }
        
    }

    printf("%lld",totaltime);
    
}