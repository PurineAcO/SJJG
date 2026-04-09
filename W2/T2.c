#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    int value;
    struct node * next;
} * list ;

list openlist(int headval){
    list listhead;

    listhead = (list) malloc(sizeof(struct node));
    listhead->value =headval;
    listhead->next = NULL;

    return listhead;
}

list searchlist(list totalhead,int key){
    list L = totalhead;
    while(L != NULL){
        if(L->value == key){return L;}
        L = L->next;
    }
    return NULL;
}

void addtolist(list L,int val){
    list nextlist;
    nextlist = (list)malloc(sizeof(struct node));
    nextlist->next = L->next;
    L->next = nextlist;
    nextlist->value=val;
}

int deletelist(list L){
    if(L->next==NULL){return -1;}
    list nextlist  = L->next;
    L->next =nextlist->next;
    free(nextlist);
    return 0;
}

void printlist(list head){
    while(head !=NULL){
        printf("%d ",head->value);
        head = head->next;
    }
}


int main(){

    list mylisthead = openlist(1);
    int processnum;scanf("%d",&processnum);

    for(int i=1;i<=processnum;i++){

        int processcode;
        scanf("%d",&processcode);

        if(processcode==1){
            int x,y;scanf("%d%d",&x,&y);
            addtolist(searchlist(mylisthead, x), y);
        }

        else if(processcode==2){
            int x;
            scanf("%d",&x);
            list p=searchlist(mylisthead, x);
            printf("%d\n",(p && p->next) ? p->next->value :0);
        }

        else if (processcode==3) {
            int x;
            scanf("%d",&x);
            deletelist(searchlist(mylisthead, x));      
        }
    }

    // printf("\n");
    // printlist(mylisthead);

    return 0;
}
