#include <stdio.h>

int findmax(double fen[],int n){
    int maxpl=1;
    for(int i=1;i<=n;i++){
        if(fen[i]>fen[maxpl]){maxpl=i;}
    }
    return maxpl;
}

int main(){

    int n,k;
    scanf("%d %d",&n,&k);
    double tifen[100]={};
    int zhibiao;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=k;j++){
            scanf("%d",&zhibiao);
            tifen[i]+=zhibiao;
        }
        tifen[i]=tifen[i]/k;
    }

    // for(int i=1;i<=n;i++){printf("%f",tifen[i]);}

    int maxplace=findmax(tifen,n);
    tifen[maxplace]=0;
    int secondmaxplace=findmax(tifen,n);

    printf("%d\n%d",maxplace,secondmaxplace);

    return 0;
}