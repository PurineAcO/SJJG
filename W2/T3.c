#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    int item;
    struct node * next;
} * list;

list createlist(int n){
    list head=NULL;list tail=NULL;list now=NULL;

    for(int i=1;i<=n;i++){
        now = (list) malloc(sizeof(struct node));
        now->item = i;
        now->next = head;

        if (head== NULL){head=now;}
        else {tail->next = now;}
        tail = now;
    }

    return head;
}

void printlist(list head){
    list realhead=head;
    int ifprinthead=0;
    while(head !=realhead || ifprinthead == 0 ){
        printf("%d ",head->item);
        head = head->next;
        ifprinthead =1;
    }
}

list cyclinglist(int totalnum,int n,list head){
    list nowlist=head;
    n = n%totalnum;
    if(n==0){return nowlist;}
    for(int i=1;i<=n;i++){nowlist = nowlist->next;}
    return nowlist;
}

list deletenowlist(list nowlist,int totalnum){
    list now = nowlist;
    list before = cyclinglist(totalnum,totalnum-1,now);
    before->next = now->next;
    free(now);
    return before->next;
}


char coursename[1002][25]={};
int klist[1002]={};


int main(){

    int coursenum;scanf("%d",&coursenum);getchar();
    
    for (int i=1;i<=coursenum;i++){
        char c=getchar();
        int wordcnt=0;
        while(c!=' ' && c!='\n'){coursename[i][wordcnt]=c;wordcnt++;c=getchar();}
        coursename[i][wordcnt]='\0';
    }

    for (int i=1;i<=coursenum;i++){scanf("%d",&klist[i]);}

    list nowplace = createlist(coursenum);
    // printlist(nowplace);
    
    for(int i=1;i<=coursenum;i++){
        nowplace = cyclinglist(coursenum-i+1,klist[i],nowplace);
        printf("%s ",coursename[nowplace->item]);
        nowplace = deletenowlist(nowplace, coursenum-i+1);
    }


    return 0;
}