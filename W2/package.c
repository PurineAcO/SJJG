#include <stdio.h>
#include <math.h>
#define ll long long

struct infomation{
    int danhao[9];
    ll danhaonum;
    ll telephone;
    char name[24];
};

void bubblesort(struct infomation info[],int num){
    for(int i=1;i<=num-1;i++){
        short ifswap = 0;
        for(int j=1;j<=num-i;j++){
            if(info[j].telephone<info[j+1].telephone){
                struct infomation temp = info[j];
                info[j]=info[j+1];
                info[j+1]=temp;
                ifswap=1;
            }
            else if (info[j].telephone==info[j+1].telephone){
                if(info[j].danhaonum>info[j+1].danhaonum){
                    struct infomation temp = info[j];
                    info[j]=info[j+1];
                    info[j+1]=temp;
                    ifswap=1;
                }
            }
        }
        if(!ifswap){break;}
    }
}

int main(){
    struct infomation info[1000]={};
    int num;
    scanf("%d",&num);
    getchar();
    for(int i=1;i<=num;i++){
        for(int j=1;j<=8;j++){info[i].danhao[j]=getchar()-'0';}
        getchar();
        char c=getchar();int namezishu=0;
        while(c!=' '){info[i].name[namezishu]=c;namezishu++;c=getchar();}
        info[i].name[namezishu]='\0';
        scanf("%lld",&info[i].telephone);
        getchar();
        for(int k=1;k<=8;k++){info[i].danhaonum+=info[i].danhao[k]*pow(10,8-k);}
    }

    bubblesort(info,num);

    for(int i=1;i<=num;i++){
        printf("  ");
        for (int j=1;j<=8;j++){printf("%d",info[i].danhao[j]);}
        // printf(" ");
        printf("%22s",info[i].name);
        printf("%12lld\n",info[i].telephone);
    }

    return 0;
}