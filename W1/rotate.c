#include <stdio.h>

int main(){

    int dim;
    scanf("%d",&dim);
    getchar();

    char matrix[52][52]={};

    for(int i=1;i<=dim;i++){
        for(int j=1;j<=dim;j++){matrix[i][j]=getchar();}
        getchar();
    }
    
    // printf("%d",dim);
    // for(int i=1;i<=dim;i++){for(int j=1;j<=dim;j++){printf("%c",matrix[i][j]);}}

    int cnt1=0;int cnt2=0;int cnt3=0;
    for(int i=1;i<=dim;i++){
        for(int j=1;j<=dim;j++){
            if(matrix[i][j]==matrix[j][dim-i+1]){cnt1++;}
            if(matrix[i][j]==matrix[dim-j+1][i]){cnt2++;}
            if(matrix[i][j]==matrix[dim-i+1][dim-j+1]){cnt3++;}
        }
    }

    if(cnt1==dim*dim || cnt2==dim*dim || cnt3==dim*dim ){printf("Yes");}
    else {printf("No");}

    return 0;
}